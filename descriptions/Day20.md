--- Day 20: Firewall Rules ---
------------------------------

You'd like to set up a small hidden computer here so you can use it to <span title="I'll create a GUI interface using Visual Basic... see if I can track an IP address.">get back into the network</span> later. However, the corporate firewall only allows communication with certain external [IP addresses](https://en.wikipedia.org/wiki/IPv4#Addressing).

You've retrieved the list of blocked IPs from the firewall, but the list seems to be messy and poorly maintained, and it's not clear which IPs are allowed. Also, rather than being written in [dot-decimal](https://en.wikipedia.org/wiki/Dot-decimal_notation) notation, they are written as plain [32-bit integers](https://en.wikipedia.org/wiki/32-bit), which can have any value from `0` through `4294967295`, inclusive.

For example, suppose only the values `0` through `9` were valid, and that you retrieved the following blacklist:

    5-8
    0-2
    4-7

The blacklist specifies ranges of IPs (inclusive of both the start and end value) that are *not* allowed. Then, the only IPs that this firewall allows are `3` and `9`, since those are the only numbers not in any range.

Given the list of blocked IPs you retrieved from the firewall (your puzzle input), *what is the lowest-valued IP* that is not blocked?

Your puzzle answer was `23923783`.

--- Part Two ---
----------------

*How many IPs* are allowed by the blacklist?

Your puzzle answer was `125`.

Both parts of this puzzle are complete! They provide two gold stars: \*\*

At this point, you should [return to your advent calendar](/2016) and try another puzzle.

If you still want to see it, you can [get your puzzle input](20/input).

You can also <span class="share">\[Share<span class="share-content">on [Twitter](https://twitter.com/intent/tweet?text=I%27ve+completed+%22Firewall+Rules%22+%2D+Day+20+%2D+Advent+of+Code+2016&url=http%3A%2F%2Fadventofcode%2Ecom%2F2016%2Fday%2F20&related=ericwastl&hashtags=AdventOfCode) [Google+](https://plus.google.com/share?url=http%3A%2F%2Fadventofcode%2Ecom%2F2016%2Fday%2F20) [Reddit](http://www.reddit.com/submit?url=http%3A%2F%2Fadventofcode%2Ecom%2F2016%2Fday%2F20&title=I%27ve+completed+%22Firewall+Rules%22+%2D+Day+20+%2D+Advent+of+Code+2016)</span>\]</span> this puzzle.
