# Natural Order String Comparison

Martin Pool <http://sourcefrog.net>

Computer string sorting algorithms generally don't order strings
containing numbers in the same way that a human would do.  Consider:

        rfc1.txt
        rfc2086.txt
        rfc822.txt

It would be more friendly if the program listed the files as

        rfc1.txt
        rfc822.txt
        rfc2086.txt

Filenames sort properly if people insert leading zeros, but they
don't always do that.

I've written a subroutine that compares strings according to this
natural ordering.  You can use this routine in your own software, or
download a patch to add it to your favourite Unix program.


## Sorting

Strings are sorted as usual, except that decimal integer substrings
are compared on their numeric value.  For example,


    a < a0 < a1 < a1a < a1b < a2 < a10 < a20


Strings can contain several number parts:

    x2-g8 < x2-y7 < x2-y08 < x8-y8

in which case numeric fields are separated by nonnumeric characters.
Leading spaces are ignored.  This works very well for IP addresses
from log files, for example.


Leading zeros are *not* ignored, which tends to give more
reasonable results on decimal fractions.

      1.001 < 1.002 < 1.010 < 1.02 < 1.1 < 1.3

Some applications may wish to change this by modifying the test that calls `isspace`.

Performance is linear: each character of the string is scanned
at most once, and only as many characters as necessary to decide
are considered.


## Licensing

This software is copyright by Martin Pool, and made available under
the same licence as zlib:


>  This software is provided 'as-is', without any express or implied
>  warranty.  In no event will the authors be held liable for any damages
>  arising from the use of this software.
>
>  Permission is granted to anyone to use this software for any purpose,
>  including commercial applications, and to alter it and redistribute it
>  freely, subject to the following restrictions:
>
>  1. The origin of this software must not be misrepresented; you must not
>     claim that you wrote the original software. If you use this software
>     in a product, an acknowledgment in the product documentation would be
>     appreciated but is not required.
>
>  2. Altered source versions must be plainly marked as such, and must not be
>     misrepresented as being the original software.
>
>  3. This notice may not be removed or altered from any source distribution.


This licence applies only to the C implementation.  You are free to
reimplement the idea fom scratch in any language.

## Get It!

`strnatcmp.c`, `strnatcmp.h` - the algorithm itself

`natsort.c` - example driver program.

`natcompare.js` - Kristof Coomans wrote a natural sort comparison in Javascript.

`natcmp.rb` -- An implementation by Alan Davies in Ruby.

## Related Work



POSIX sort(1) has the -n option to sort numbers, but this doesn't
work if there is a non-numeric prefix.


GNU ls(1) has the `--sort=version` option, which works
the same way.



The PHP scripting language now has a
[strnatcmp](http://us3.php.net/manual/en/function.strnatcmp.php)
function based on this code.
The PHP wrapper was done by Andrei Zimievsky.



[Stuart Cheshire has a Macintosh system extension](http://www.naturalordersort.org/)
to do natural ordering.
I indepdendently reinvented the algorithm, but Stuart had it
first.  I borrowed the term natural sort from him.




[`Sort::Versions`](http://search.cpan.org/src/EDAVIS/Sort-Versions-1.4/README)
in Perl.  "The code has some special magic to deal with common conventions in program version numbers, like the difference between 'decimal' versions (eg perl 5.005) and the Unix kind (eg perl 5.6.1)."

[Sort::Naturally](http://www.cpan.org/modules/by-module/Sort/Sort-Naturally-1.01.readme)
is also in Perl, by  Sean M. Burke.  It uses locale-sensitive character classes to sort words and numeric substrings
in a way similar to natsort.


Ed Avis wrote [something similar in Haskell](http://membled.com/work/apps/todo/numsort).



Pierre-Luc Paour wrote a
[`NaturalOrderComparator`](http://pierre-luc.paour.9online.fr/NaturalOrderComparator.java)
in Java.

[Numacomp](http://sourceforge.net/projects/numacomp) - similar thing in Python.

[as3natcompare](http://code.google.com/p/as3natcompare/) implementation in Flash ActionScript 3.

## To Do

Comparison of characters is purely numeric, without taking
character set or locale into account.  So it is only correct for
ASCII.  This should probably be a separate function because doing
the comparisons will probably introduce a dependency on the OS
mechanism for finding the locale and comparing characters.

It might be good to support multibyte character sets too.

If you fix either of these, please mail me.  They should not be
very hard.
