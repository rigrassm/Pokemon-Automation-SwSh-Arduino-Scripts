# EggSuperCombined2

Run [MassRelease](MassRelease.md), then run [EggCombined2](EggCombined2.md).

***Do not** use this program until you are familiar with EggCombined since this is literally the same thing, but with an extra mass-release step. Therefore it is even more tricky to use correctly and safely.*

EggSuperCombined2 is the most optimized of the egg programs in this package. When used properly, it can allow 24/7 hatching while requiring the user to only touch the Switch twice a day. Thus this program is most suitable for mass production of hatched shinies - especially multiple Switches where you want to minimize the amount of interaction required for each Switch.

As with EggCombined2, this program will sustain upwards ***1700 eggs/day*** (5120 step) when used properly.

The idea of EggSuperCombined is to automate away the mass-release that's needed between EggCombined runs. So between runs after removing the shinies, you no longer need to run and wait for MassRelease to finish through before starting the next batch of eggs. Thus, the "interrupt" time between runs is now on the order of a few minutes instead of an hour to release 20+ boxes.

So you hatch eggs overnight. When you wake up in the morning, spend only a few minutes to remove shinies and fix boxes. Then start EggSuperCombined before heading to work. This allows you to hatch eggs 24/7 while touching the Switch only 2 or 3 times a day.

Experienced users will be able to sustain 24/7 hatching using only this program. The size of the egg reservoir can be kept in check by modifying the `FETCHES_PER_BATCH` parameter.

## Instructions:

These instructions are identical to that of EggCombined2.

- Casual mode is off.
- Your text speed must be set to fast. 
- The “Send to Boxes” option must be set to “Automatic”.
- Nicknaming needs to be off.
- Your bike must be fully upgraded.
- The parents are already deposited at the Route 5 daycare center.
- Your party must have exactly 1 Pokémon.
- The one Pokémon in your party MUST be a flame body (or similar) Pokémon.
- The menu icons are in their default locations:
  - The Town Map must be in the 2nd row on the far left.
  - The Pokémon option must be in the 1st row, 2nd from the left.
- The cursor in the menu is over the "Pokémon" option.
- You must be on Route 5.
- You must be on your bike.
- You must be in the overworld. (not in the menu)
- There is nothing in front of you that can be interacted with.
-	Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

*If you are playing in Japanese or Italian, you need to [set a flag](../Appendix/GlobalSettings.md#japanese-egg-fetching) or this program will not work.*

## Box Setup:

This is similar to, but not identical to that of EggCombined.

- Place entire boxes filled with Pokémon to be released consecutively. 
- The next N boxes can contain anything. They will be skipped.
- Place entire boxes filled with eggs consecutively*.
- You must be on the first box of Pokémon to be released.
- All the eggs that you are hatching MUST hatch at the same time and at the specified # of steps. Eggs are not allowed to hatch early**.

*It is okay to have non-eggs mixed in with eggs. But all boxes that you intend to hatch must be completely filled.

***Do not use this program on partially hatched eggs. Even a single early hatching egg can break the program.*

## Required Parameters:
- `BOXES_TO_RELEASE`: You MUST set this parameter correctly or you may release Pokémon you didn't intend to release!
- `BOXES_TO_SKIP`: You MUST set this parameter correctly or you may not hatch the correct boxes.
- `BOXES_TO_HATCH`: You MUST set this to the # of boxes you wish to hatch. Otherwise, you either won't hatch all the eggs you want, or the program goes crazy if you run out of eggs.
- `STEPS_TO_HATCH`: You MUST set this to the correct step-count for the Pokémon you are hatching. If this is set too small or too large, the program will fail and may unintentionally start a trade. (see Precautions)

All recommendations, precautions, and usage tips for EggCombined apply to this program as well.

## Additional Recommendations:
- See [Maximizing Switch Stability](../Appendix/MaximizingSwitchStability.md). The MassRelease portion of this program is sensitive to jitter.
- Don't leave any Pokémon you care about in the game. It goes without saying that mass-release is inherently dangerous to run unattended.
- Use a dedicated game with 32 empty boxes. If you're at the point where you're considering this program for optimized egg hatching, you might as well just speedrun a new game and shiny charm it with a living dex that you probably already have sitting in Pokémon Home.

## Example Box Layout:
The box setup is pretty confusing. So here is an example.
```
Box  1: empty
Box  2: empty
Box  3: 30 breedjects 
Box  4: 30 breedjects
Box  5: 30 breedjects
Box  6: 15 breedjects
Box  7: your regular Pokémon
Box  8: 30 eggs
Box  9: 30 eggs
Box 10: 30 eggs
Box 11: 25 eggs
Box 12: empty
Box 13: empty
......
Box 32: empty
```
Configure EggSuperCombined with these settings:
```
BOXES_TO_RELEASE    =   3
BOXES_TO_SKIP       =   2
BOXES_TO_HATCH      =   30
```
Starting with Box 3 as the current box, the program will:
1. Release 3 boxes: 3, 4, 5
2. Skip 2 boxes: 6, 7
3. Run EggCombined for 30 boxes: 8-32 (wrap-around) 1-5

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

In addition to the main options below, there are more [global options](../Appendix/GlobalSettings.md) that can be configured if you encounter problems.

### # of Boxes to Release:
```
const uint8_t   BOXES_TO_RELEASE    =   2;
```
This is the number of boxes to release.

### # of Boxes to Skip:
```
const uint8_t   BOXES_TO_SKIP       =   1;
```
This is the number of boxes to release.

### Boxes of Eggs to Hatch:
```
const uint8_t   BOXES_TO_HATCH      =   3;
```
Hatch this many boxes of eggs.

### Egg Step-Count:
```
const uint16_t  STEPS_TO_HATCH      =   5120;
```
The number of steps needed to hatch the eggs. Look up the value on Serebii.

### Fetches per Batch:
```
const float FETCHES_PER_BATCH       =   6.0;
```
For each batch of eggs, attempt this many egg fetches. If this is a non-integer, the program will vary the # of fetches across batches so that they average out to the specified number.

By changing this number you can adjust the fetch rate of eggs. Thus with careful tuning, you can make egg fetching nearly the same speed as hatching.

Since there are 5 eggs per batch, you will need to set this value to more than 5.0 to match the hatch rate since some fetches will fail. The optimal value will depend on the step count and the compatibility of the parents.
Since this program is new, the exact fetch rates that lead to fetch/hatch equilibriums are not yet known. But they are believed to all be between 5.1 and 6.5.

## Advanced Settings:
These are advanced settings. You shouldn’t need to touch these unless something isn’t working and you’re trying to debug it yourself.

### Safety Time:
```
const uint16_t SAFETY_TIME      =   8 * TICKS_PER_SECOND;
```
Additional time added to the spinning. If any shinies are hatched, they will eat into this safety buffer along with any other unexpected slowdowns. Hatching a shiny takes 2 seconds longer than a non-shiny.

If you see that the program is going into Y-COMM or there is less than 5 seconds of extra spinning after the last egg in the batch, please report this as a bug. As a temporary work-around, you can increase this number.

### Early Hatch Safety:
```
const uint16_t EARLY_HATCH_SAFETY   =   5 * TICKS_PER_SECOND;
```
Eggs will not hatch early by more than this period.

### Hatch Delay:
```
const uint16_t HATCH_DELAY      =   88 * TICKS_PER_SECOND;
```
Total animation time for hatching 5 eggs when there are no shinies.




