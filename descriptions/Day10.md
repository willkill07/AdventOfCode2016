--- Day 10: Balance Bots ---
----------------------------

You come upon a factory in which many robots are [zooming around](https://www.youtube.com/watch?v=JnkMyfQ5YfY&t=40) handing small microchips to each other.

Upon closer examination, you notice that each bot only proceeds when it has *two* microchips, and once it does, it gives each one to a different bot or puts it in a marked "output" bin. Sometimes, bots take microchips from "input" bins, too.

Inspecting one of the microchips, it seems like they each contain a single number; the bots must use some logic to decide what to do with each chip. You access the local control computer and download the bots' instructions (your puzzle input).

Some of the instructions specify that a specific-valued microchip should be given to a specific bot; the rest of the instructions indicate what a given bot should do with its *lower-value* or *higher-value* chip.

For example, consider the following instructions:

    value 5 goes to bot 2
    bot 2 gives low to bot 1 and high to bot 0
    value 3 goes to bot 1
    bot 1 gives low to output 1 and high to bot 0
    bot 0 gives low to output 2 and high to output 0
    value 2 goes to bot 2

-   Initially, bot `1` starts with a value-`3` chip, and bot `2` starts with a value-`2` chip and a value-`5` chip.
-   Because bot `2` has two microchips, it gives its lower one (`2`) to bot `1` and its higher one (`5`) to bot `0`.
-   Then, bot `1` has two microchips; it puts the value-`2` chip in output `1` and gives the value-`3` chip to bot `0`.
-   Finally, bot `0` has two microchips; it puts the `3` in output `2` and the `5` in output `0`.

In the end, output bin `0` contains a value-`5` microchip, output bin `1` contains a value-`2` microchip, and output bin `2` contains a value-`3` microchip. In this configuration, bot number *`2`* is responsible for comparing value-`5` microchips with value-`2` microchips.

Based on your instructions, *what is the number of the bot* that is responsible for comparing value-`61` microchips with value-`17` microchips?

Your puzzle answer was `141`.

--- Part Two ---
----------------

<span title="What do you get if you multiply six by nine?">What do you get</span> if you *multiply together the values* of one chip in each of outputs `0`, `1`, and `2`?

Your puzzle answer was `1209`.

Both parts of this puzzle are complete! They provide two gold stars: \*\*

At this point, you should [return to your advent calendar](/2016) and try another puzzle.

If you still want to see it, you can [get your puzzle input](10/input).

You can also <span class="share">\[Share<span class="share-content">on [Twitter](https://twitter.com/intent/tweet?text=I%27ve+completed+%22Balance+Bots%22+%2D+Day+10+%2D+Advent+of+Code+2016&url=http%3A%2F%2Fadventofcode%2Ecom%2F2016%2Fday%2F10&related=ericwastl&hashtags=AdventOfCode) [Google+](https://plus.google.com/share?url=http%3A%2F%2Fadventofcode%2Ecom%2F2016%2Fday%2F10) [Reddit](http://www.reddit.com/submit?url=http%3A%2F%2Fadventofcode%2Ecom%2F2016%2Fday%2F10&title=I%27ve+completed+%22Balance+Bots%22+%2D+Day+10+%2D+Advent+of+Code+2016)</span>\]</span> this puzzle.
