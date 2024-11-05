#include "AppHdr.h"

#include "jobs.h"

#include "enum.h"
#include "errors.h"
#include "item-name.h"
#include "item-prop.h"
#include "item-status-flag-type.h"
#include "items.h"
#include "libutil.h"
#include "mapdef.h"
#include "ng-setup.h"
#include "player.h"
#include "stringutil.h"

#include "job-data.h"

bool human_wanderer_needs_stat_reroll();
void add_manual(skill_type sk, int slot, float factor = 1.0f);
int get_first_free_slot();

static const job_def& _job_def(job_type job)
{
    ASSERT_RANGE(job, 0, NUM_JOBS);
    return job_data.at(job);
}

const char *get_job_abbrev(job_type which_job)
{
    if (which_job == JOB_UNKNOWN)
        return "Un";
    return _job_def(which_job).abbrev;
}

job_type get_job_by_abbrev(const char *abbrev)
{
    for (auto& entry : job_data)
        if (lowercase_string(abbrev) == lowercase_string(entry.second.abbrev))
            return entry.first;

    return JOB_UNKNOWN;
}

const char *get_job_name(job_type which_job)
{
    if (which_job == JOB_UNKNOWN)
        return "Unemployed";

    return _job_def(which_job).name;
}

job_type get_job_by_name(const char *name)
{
    job_type job = JOB_UNKNOWN;

    const string low_name = lowercase_string(name);

    for (auto& entry : job_data)
    {
        string low_job = lowercase_string(entry.second.name);

        const size_t pos = low_job.find(low_name);
        if (pos != string::npos)
        {
            job = entry.first;
            if (!pos)  // prefix takes preference
                break;
        }
    }

    return job;
}

bool human_wanderer_needs_stat_reroll()
{
    if (you.species != SP_HUMAN)
    {
        return false;
    }
    
    if (Options.human_wanderer_type == 1)
    {
        return you.base_stats[STAT_STR] > 9 || you.base_stats[STAT_INT] < 14;
    }
    
    return false;
}

// Must be called after species_stat_init for the wanderer formula to work.
void job_stat_init(job_type job)
{
    you.hp_max_adj_perm = 0;

    you.base_stats[STAT_STR] += _job_def(job).s;
    you.base_stats[STAT_INT] += _job_def(job).i;
    you.base_stats[STAT_DEX] += _job_def(job).d;

    if (job == JOB_WANDERER)
    {
        auto stats = you.base_stats;
        
        do
        {
            you.base_stats = stats;
            
            for (int i = 0; i < 12; i++)
            {
                const auto stat = random_choose_weighted(
                        you.base_stats[STAT_STR] > 17 ? 1 : 2, STAT_STR,
                        you.base_stats[STAT_INT] > 17 ? 1 : 2, STAT_INT,
                        you.base_stats[STAT_DEX] > 17 ? 1 : 2, STAT_DEX);
                you.base_stats[stat]++;
            }
        } while (human_wanderer_needs_stat_reroll());
    }
}

bool job_has_weapon_choice(job_type job)
{
    return _job_def(job).wchoice != WCHOICE_NONE;
}

bool job_gets_good_weapons(job_type job)
{
    return _job_def(job).wchoice == WCHOICE_GOOD;
}

bool job_gets_ranged_weapons(job_type job)
{
    return _job_def(job).wchoice == WCHOICE_RANGED;
}

int get_first_free_slot()
{
    for (int slot = 0; slot < ENDOFPACK; ++slot)
    {
        if (!you.inv[slot].defined())
            return slot;
    }
    return -1;
}

void add_manual(skill_type sk, int slot, float factor)
{
    item_def &manual(you.inv[slot]);
    manual.base_type = OBJ_BOOKS;
    manual.sub_type = BOOK_MANUAL;
    manual.quantity = 1;
    manual.skill = sk;
    manual.skill_points = 5000 * factor;
    set_ident_type(manual, true);
    set_ident_flags(manual, ISFLAG_IDENT_MASK);
    origin_set_startequip(manual);
}

void give_job_equipment(job_type job)
{
    item_list items;
    const bool is_auric = you.your_name.compare(string("Auric Ulvin")) == 0;
    for (const string& it : _job_def(job).equipment)
    {
        string item = it;
        if (is_auric && (
                it.compare(string("robe")) == 0 ||
                it.compare(string("leather armour")) == 0
            ))
        {
            item = string("scale mail");
        }
        items.add_item(item);
    }
    
    if (is_auric && job == JOB_ICE_ELEMENTALIST)
    {
        items.add_item("mace");
        you.skills[SK_FIGHTING] += 2;
        you.skills[SK_MACES_FLAILS] += 2;
    }
    
    for (size_t i = 0; i < items.size(); i++)
    {
        const item_spec spec = items.get_item(i);
        int plus = 0;
        if (spec.props.exists("charges"))
            plus = spec.props["charges"];
        if (spec.props.exists("plus"))
            plus = spec.props["plus"];
        newgame_make_item(spec.base_type, spec.sub_type, max(spec.qty, 1),
                          plus, spec.ego);
    }
    
    if (you.species == SP_HUMAN)
    {
        if (Options.human_booster)
        {
            int slot = get_first_free_slot();
            switch(job)
            {
                case JOB_FIGHTER:
                case JOB_BERSERKER:
                    add_manual(SK_FIGHTING, slot++, 2.0f);
                    break;
                case JOB_WIZARD:
                    add_manual(SK_SPELLCASTING, slot++, 2.0f);
                    break;
                case JOB_NECROMANCER:
                    add_manual(SK_SPELLCASTING, slot++);
                    add_manual(SK_NECROMANCY, slot++);
                    break;
                case JOB_CONJURER:
                    add_manual(SK_SPELLCASTING, slot++);
                    add_manual(SK_CONJURATIONS, slot++);
                    break;
                case JOB_ENCHANTER:
                    add_manual(SK_STEALTH, slot++);
                    add_manual(SK_HEXES, slot++);
                    add_manual(SK_DODGING, slot++);
                    add_manual(SK_SHORT_BLADES, slot++);
                    break;
                case JOB_FIRE_ELEMENTALIST:
                    add_manual(SK_CONJURATIONS, slot++);
                    add_manual(SK_FIRE_MAGIC, slot++);
                    break;
                case JOB_ICE_ELEMENTALIST:
                    add_manual(SK_CONJURATIONS, slot++);
                    add_manual(SK_ICE_MAGIC, slot++);
                    break;
                case JOB_SUMMONER:
                    add_manual(SK_SPELLCASTING, slot++);
                    add_manual(SK_SUMMONINGS, slot++);
                    break;
                case JOB_AIR_ELEMENTALIST:
                    add_manual(SK_CONJURATIONS, slot++);
                    add_manual(SK_AIR_MAGIC, slot++);
                    break;
                case JOB_EARTH_ELEMENTALIST:
                    add_manual(SK_CONJURATIONS, slot++);
                    add_manual(SK_EARTH_MAGIC, slot++);
                    break;
                case JOB_SKALD:
                    add_manual(SK_FIGHTING, slot++);
                    add_manual(SK_CHARMS, slot++);
                    break;
                case JOB_VENOM_MAGE:
                    add_manual(SK_CONJURATIONS, slot++);
                    add_manual(SK_POISON_MAGIC, slot++);
                    break;
                case JOB_TRANSMUTER:
                    add_manual(SK_FIGHTING, slot++);
                    add_manual(SK_UNARMED_COMBAT, slot++);
                    add_manual(SK_TRANSMUTATIONS, slot++, 0.5f);
                    break;
                case JOB_WARPER:
                    add_manual(SK_FIGHTING, slot++, 1.5f);
                    add_manual(SK_TRANSLOCATIONS, slot++);
                    break;
                case JOB_CHAOS_KNIGHT:
                case JOB_MONK:
                case JOB_ABYSSAL_KNIGHT:
                    add_manual(SK_FIGHTING, slot++);
                    add_manual(SK_INVOCATIONS, slot++);
                    break;
                default:
                    break;
            }
        }
    }
}

// Must be called after equipment is given for weapon skill to be given.
void give_job_skills(job_type job)
{
    for (const pair<skill_type, int>& entry : _job_def(job).skills)
    {
        skill_type skill = entry.first;
        int amount = entry.second;
        if (skill == SK_WEAPON)
        {
            const item_def *weap = you.weapon();
            skill = weap ? item_attack_skill(*weap) : SK_UNARMED_COMBAT;
            //XXX: WTF?
            if (you.species == SP_FELID && job == JOB_FIGHTER)
                amount += 2;
            // Don't give throwing hunters Thrusting Blades skill.
            if (job_gets_ranged_weapons(job) && !(weap && is_range_weapon(*weap)))
                skill = SK_THROWING;
        }
        you.skills[skill] += amount;
    }
}

void debug_jobdata()
{
    string fails;

    for (int i = 0; i < NUM_JOBS; i++)
        if (!job_data.count(static_cast<job_type>(i)))
            fails += "job number " + to_string(i) + "is not present\n";

    item_list dummy;
    for (auto& entry : job_data)
        for (const string& it : entry.second.equipment)
        {
            const string error = dummy.add_item(it, false);
            if (!error.empty())
                fails += error + "\n";
        }

    dump_test_fails(fails, "job-data");
}

bool job_recommends_species(job_type job, species_type species)
{
    return find(_job_def(job).recommended_species.begin(),
                _job_def(job).recommended_species.end(),
                species) != _job_def(job).recommended_species.end();
}

// A random valid (selectable on the new game screen) job.
job_type random_starting_job()
{
    job_type job;
    do {
        job = static_cast<job_type>(random_range(0, NUM_JOBS - 1));
    } while (!is_starting_job(job));
    return job;
}

// Ensure the job isn't JOB_RANDOM/JOB_VIABLE and it has recommended species
// (old disabled jobs have none).
bool is_starting_job(job_type job)
{
    return job < NUM_JOBS
        && !_job_def(job).recommended_species.empty();
}
