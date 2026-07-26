

# Generate ULID

[**Source code**](https://github.com/eddelbuettel/ulid/tree/master/R/#L)

## Description

<code>generate()</code> generates a new
<a href="https://github.com/ulid/spec">Universally Unique
Lexicographically Sortable Identifier</a>. Several aliases are available
for convience and backwards-compatibility.

This function generates a new
<a href="https://github.com/ulid/spec">Universally Unique
Lexicographically Sortable Identifier</a> from a vector of
<code>POSIXct</code> timestamps.

Note that this validation leaves open other possible venues for being
invalid: a future date for the time component, or a nonsensical date are
two examples

As described in the <a href="https://github.com/ulid/spec">ulid
specification repo</a>, and slightly edited here, UUID use can be
suboptimal for many uses-cases because:(grifted from
<a href="https://github.com/ulid/spec">https://github.com/ulid/spec</a>)

UUID can be suboptimal for many uses-cases because:

<ul>
<li>

It isn’t the most character efficient way of encoding 128 bits of
randomness

</li>
<li>

UUID v1/v2 is impractical in many environments, as it requires access to
a unique, stable MAC address

</li>
<li>

UUID v3/v5 requires a unique seed and produces randomly distributed IDs,
which can cause fragmentation in many data structures

</li>
<li>

UUID v4 provides no other information than randomness which can cause
fragmentation in many data structures

</li>
</ul>

Instead, an alternative is proposed in ULID:

<pre>ulid() // 01ARZ3NDEKTSV4RRFFQ69G5FAV
</pre>

with the following properties:

<ul>
<li>

128-bit compatibility with UUID

</li>
<li>

1.21e+24 unique ULIDs per millisecond

</li>
<li>

Lexicographically sortable!

</li>
<li>

Canonically encoded as a 26 character string, as opposed to the 36
character UUID

</li>
<li>

Uses Crockford’s base32 for better efficiency and readability (5 bits
per character)

</li>
<li>

Case insensitive

</li>
<li>

No special characters (URL safe)

</li>
<li>

Monotonic sort order (correctly detects and handles the same
millisecond)

</li>
</ul>

<pre>01AN4Z07BY      79KA1307SR9X4MV3

|----------|    |----------------|
  Timestamp          Randomness
   48bits              80bits
</pre>

<strong>Components</strong>

<em>Timestamp</em>

<ul>
<li>

48 bit integer

</li>
<li>

UNIX-time in milliseconds

</li>
<li>

Will not run out of space until the year 10889 AD.

</li>
</ul>

<em>Randomness</em>

<ul>
<li>

80 bits

</li>
<li>

Cryptographically secure source of randomness, if possible

</li>
</ul>

<strong>Sorting</strong>

The left-most character must be sorted first, and the right-most
character sorted last (lexical order). The default ASCII character set
must be used. Within the same millisecond, sort order is not guaranteed.

## Usage

<pre><code class='language-R'>generate(n = 1L)

unmarshal(ulids)

ts_generate(tsv)

is_ulid(s)

ulid(n = 1L)

ulid_generate(n = 1L)

ULIDgenerate(n = 1L)
</code></pre>

## Arguments

<table role="presentation">
<tr>
<td style="white-space: nowrap; font-family: monospace; vertical-align: top">
<code id="n">n</code>
</td>
<td>
number of id’s to generate (default = <code>1</code>)
</td>
</tr>
<tr>
<td style="white-space: nowrap; font-family: monospace; vertical-align: top">
<code id="ulids">ulids</code>
</td>
<td>
character ULIDs (e.g. created with <code>generate()</code>)
</td>
</tr>
<tr>
<td style="white-space: nowrap; font-family: monospace; vertical-align: top">
<code id="tsv">tsv</code>
</td>
<td>
vector of <code>POSIXct</code> values
</td>
</tr>
<tr>
<td style="white-space: nowrap; font-family: monospace; vertical-align: top">
<code id="s">s</code>
</td>
<td>
string with a ulid symbol
</td>
</tr>
</table>

## Details

Note that up until release 0.3.1, the implementations had limitations
that resulted in second rather than millisecond resolution. This has
been addressed for release 0.4.0 and is now supported as expected.

## Value

A vector with <code>n</code> character strings (for
<code>generate()</code> and <code>ts_generate()</code>)

A <code>data.frame</code> with two columns <code>ts</code> and
<code>rnd</code> (for <code>unmarshal()</code>)

A boolean result (for <code>is_ulid</code>)

## Author(s)

Bob Rudis (bob@rud.is) wrote the package based on <code>ulid</code> C++
library by Suyash Verma.

Dirk Eddelbuettel now maintains the package.

## See Also

The <a href="https://github.com/ulid/spec">ulid specification</a>
provides the reference.

## Examples

``` r
library("ulid")

ULIDgenerate()
```

    [1] "01KYG3229643QS0BEA7Y24F5PJ"

``` r
unmarshal(generate())
```

                       ts              rnd
    1 2026-07-26 20:49:56 2D6DZQVJX996FT20

``` r
ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01"))
```

    [1] "01BXW1H7C0V37PF6NHX0PZXZK0"

``` r
is_ulid(ULIDgenerate())
```

    [1] TRUE
