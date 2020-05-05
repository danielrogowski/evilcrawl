# Evilcrawl

I like dcss very much. (I won't go into depth here concerning the reasons.) It's a great game. One of the best imho. I'm very grateful a lot of people put a whole lot of work into this project and still do. That said, there are also some aspects of the game and of vanilla team decisions I'm not fond of. Most of which concerning the Vampire race. Especially since 0.24. The "new Vampire" is an interesting race, but to me, it doesn't feel a even a tiny bit like playing a Vampire at all. Fair enough I guess. This fork is about implementing the Vampire race so that it really feels like being a bloodsucker and being dependent on blood.

## How to play this

As there's no server running this fork, you can only download and play it offline. Grab the zip at https://www.dropbox.com/s/a97igtwqtxh9xho/evilcrawl-stone_soup-0.23.2-59-g7911479-tiles-win32.zip?dl=1 unpack it to a folder of your choice and execute the exe. Have fun!

If you want to build it yourself: Please use the branch evilcrawl-0.23.2! On how to build crawl, please refer to the file crawl-ref/INSTALL.txt. It details how to get the thing to run on your particular system.

## What's changed

### Vampire and related

Most changes to the race are evident if you take a look at the abilities screen: shift+a and then hitting '!'.

* the relevant hunger levels (which change something) are: bloodless, thirsty, satiated, full, very full and engorged
* Vampires get a blood related strength and hp regeneration bonus at full and above, the more blood the more strength and regeneration. The boni scale with XL!
* at bloodless Vampires not only don't naturally regenerate, they degenerate at a slow rate, eventually killing them: Vampires depend on blood for survival! Then again even bloodless Vampires can heal and therefore sustain themselves by wearing a source of magical healing, like a troll armor or an amulet of healing. Those healing effects are halved.
* Vampires always have at least rN+, even if engorged
* Vampires may use Sublimation of Blood if not bloodless
* I put the spells Haste and Mass Confusion back in: I know Haste is overpowered. I don't care. To me, crawl is and will be an unbalanced game. So what. Haste is fun and Mass Confusion is too.
* Invisibility is changed, so that even with SeeInvis a malus to to-hit occurs. This applies to monsters and players. ;-)
* Darkness incurs a slight malus to to-hit for monsters
* bats can wear rings in addition to amulets
* reduced min weapon delay to 2 (fast chars are at a disadvantage in mid and late, because they can't do as much damage per attack to high AC monsters)

### other stuff

* higher unique spawn rate to offset some branch changes which make the game easier
* short blades and long blades are renamed to thrusting blades and slashing blades. (I couldn't stand the rapier being a short blade.)
* blade hands is cleaving despite it being strong enough already, because it is also inflexible (no ranged combat and harder to cast as long as transformed) and completely offensive minded
* put claws in place of horns regarding beastly appendage
* Bolt of Draining is in the necro starting book
* when hurl hellfire is used to kill monsters, count it towards song of slaying
* powered by death regenerates mp at a 1/5 rate when hp is full
* strengthened repulsion field mutation a bit, because EV is generally weaker than AC
* changed ozos armor behavior back to 0.21 (you may move with ice armor, albeit with a speed like ponderous)
* set max player speed to 4 (before haste)
* set max attack speed to 2
* changes based on options configurable in the rc (defaults to vanilla)
  * spicy edition features (ported from spicy, credits go to jeremygurr)
    * all_spicy_features = true|false
    * no_exp_cap = true|false
    * wide_spell_list = true|false
    * unlimited_summons = true|false
  * evilcrawl options
    * ds_hurl_hellfire = 0 -> off | 1 -> random (vanilla) | 2 -> guaranteed
    * ds_guaranteed_powered_by_death = true|false
    * ds_undesired_facets = true|false (I deem some facets undesirable)
    * ds_always_monstrous = true|false
    * rune_identifies_items = true|false (ported from bcrawl, credits go this way; but made optional)
    * infusion_enhancement = true|false (ported from bcrawl, credits go this way)
    * human_wanderer_type = 0 -> random (vanilla) | 1 -> caster
    * pain_enhancement = true|false
<br />
<br />
<br />
What follows is the official README of vanilla crawl:

# Dungeon Crawl Stone Soup

Dungeon Crawl Stone Soup is a game of dungeon exploration, combat and magic, involving characters of diverse skills, worshipping deities of great power and caprice. To win, you'll need to be a master of tactics and strategy, and prevail against overwhelming odds.

## Contents

1. [How to Play](#how-to-play)
3. [Community](#community)
5. [How you can help](#how-you-can-help)
4. [License and history information](#license-and-history-information)

## How to Play

If you'd like to dive in immediately, we suggest one of:

* Start a game and pick a tutorial (select tutorial in the game menu),
* Read [quickstart.txt](crawl-ref/docs/quickstart.txt) (in the [docs/](crawl-ref/docs/) directory), or
* For the studious, [read Crawl's full manual](crawl-ref/docs/crawl_manual.rst).

There is also an ingame list of frequently asked questions which you can access by typing
`?Q`.

#### Internet Play

You can play Crawl online, competing with other players or watching them. Click "Play Online Now!" on [the Crawl homepage](https://crawl.develz.org/) to find your closest server. You can play in your browser or over SSH.

#### Offline Play

Both classical ASCII and tiles (GUI) versions of Crawl are available to [download for Linux, Windows and OS X](https://crawl.develz.org/download.htm).

## Community

* Our official homepage: [crawl.develz.org](https://crawl.develz.org/)
  * Online webtiles play
  * Offline downloads
  * A community forum
* The official [/r/dcss subreddit](https://www.reddit.com/r/dcss/)
* [/r/roguelikes Discord](https://discord.gg/S5F2H32)
* IRC: ##crawl on Freenode (or ##crawl-dev to chat development)

## How you can help

If you like the game and you want to help make it better, there are a number
of ways to do so. For a detailed guide to the crawl workflow, look at
the [contributor's guide](crawl-ref/docs/develop/contribution-process.md).

### Reporting bugs

At any time, there will be bugs -- finding and reporting them is a great help.
Many of the online servers host the regularly updated development version. Bugs
should be reported to [our bug tracker](https://crawl.develz.org/mantis/). Besides pointing out bugs, new ideas on how to improve interface or gameplay are welcome. These can be added to [the development wiki](https://crawl.develz.org/wiki/).

### Map making
Crawl creates levels by combining many hand-made (but often randomised) maps, known as *vaults*. Making them is fun and
easy. It's best to start with simple entry vaults: see [simple.des](crawl-ref/source/dat/des/arrival/simple.des) for examples. You can also read [the level-design manual](crawl-ref/docs/develop/levels/introduction.txt) for more help.

If you're ambitious, you can create new vaults for anywhere in the game. If you've
made some vaults, you can test them on your own system (no compiling needed) and
submit them to [our bug tracker](https://crawl.develz.org/mantis/).

### Monster Speech & Item Descriptions
Monster speech provides a lot of flavour. Just like vaults, varied speech depends
upon a large set of entries. Speech syntax is effective but unusual, so you may want to read [the formatting guide](crawl-ref/docs/develop/monster_speech.txt).

Current item descriptions can be read in-game with `?/` or out-of-game
them in [dat/descript/](crawl-ref/source/dat/descript/). The following conventions should be more or less obeyed:
* Descriptions ought to contain flavour text, ideally pointing out major weaknesses/strengths.
* No numbers, please.
* Citations are okay, but try to stay away from the most generic ones.

### Tiles
We're always open to improvements to existing tiles or variants of often-used tiles (eg floor tiles). If you want to give this a shot, please [contact us](#community) via forums or IRC. In case you drew some tiles of your own, you can submit them to [our bug tracker](https://crawl.develz.org/mantis/).

### Patches
For developers (both existing & aspiring!), you can download/fork the source code and write patches. Bug fixes as well as new features are very much welcome.

For large changes, it's always a good idea to [talk with the dev team](#community) first, to see if any plans already exist and if your suggestion is likely to be accepted.

Please be sure to read [docs/develop/coding_conventions.txt](crawl-ref/docs/develop/coding_conventions.txt) too.

## License and history information

Crawl is licensed as GPLv2+. See [LICENSE](LICENSE) for the full text.

Crawl is a descendant of Linley's Dungeon Crawl. The final alpha of Linley's Dungeon Crawl (v4.1) was released by Brent Ross in 2005. Since 2006, the Dungeon Crawl Stone Soup team has continued development. [CREDITS.txt](crawl-ref/CREDITS.txt) contains a full list of contributors.

Crawl uses the following open source packages; thanks to their developers:

* The Lua scripting language, for in-game functionality and user macros ([license](crawl-ref/docs/license/lualicense.txt)).
* The PCRE library, for regular expressions ([license](crawl-ref/docs/license/pcre_license.txt)).
* The SQLite library, as a database engine ([license](https://www.sqlite.org/copyright.html)).
* The SDL and SDL_image libraries, for tiles display ([license](crawl-ref/docs/license/lgpl.txt)).
* The libpng library, for tiles image loading ([license](crawl-ref/docs/license/libpng-LICENSE.txt)).

Thank you, and have fun crawling!
