
# ulid

Universally Unique Lexicographically Sortable Identifier

## Description

(grifted from <https://github.com/ulid/spec>)

UUID can be suboptimal for many uses-cases because:

  - It isn’t the most character efficient way of encoding 128 bits of
    randomness
  - UUID v1/v2 is impractical in many environments, as it requires
    access to a unique, stable MAC address
  - UUID v3/v5 requires a unique seed and produces randomly distributed
    IDs, which can cause fragmentation in many data structures
  - UUID v4 provides no other information than randomness which can
    cause fragmentation in many data structures

Instead, herein is proposed ULID:

``` javascript
ulid() // 01ARZ3NDEKTSV4RRFFQ69G5FAV
```

  - 128-bit compatibility with UUID
  - 1.21e+24 unique ULIDs per millisecond
  - Lexicographically sortable\!
  - Canonically encoded as a 26 character string, as opposed to the 36
    character UUID
  - Uses Crockford’s base32 for better efficiency and readability (5
    bits per character)
  - Case insensitive
  - No special characters (URL safe)
  - Monotonic sort order (correctly detects and handles the same
    millisecond)

<!-- end list -->

``` 
 01AN4Z07BY      79KA1307SR9X4MV3

|----------|    |----------------|
 Timestamp          Randomness
   48bits             80bits
```

### Components

**Timestamp** - 48 bit integer - UNIX-time in milliseconds - Won’t run
out of space till the year 10889 AD.

**Randomness** - 80 bits - Cryptographically secure source of
randomness, if possible

### Sorting

The left-most character must be sorted first, and the right-most
character sorted last (lexical order). The default ASCII character set
must be used. Within the same millisecond, sort order is not guaranteed

## What’s Inside The Tin

The following functions are implemented:

  - `ULIDgenerate`: Generate a time-based ULID
  - `unmarshal`: Unmarshal a ULID into a data frame with timestamp and
    random bitstring columns

## Installation

``` r
devtools::install_github("hrbrmstr/ulid")
```

## Usage

``` r
library(ulid)

# current verison
packageVersion("ulid")
```

    ## [1] '0.1.0'

### One

``` r
ulid::ULIDgenerate()
```

    ## [1] "0001E2CWNS3ERSFZQ31W4WXVSM"

### Many

``` r
(u <- ulid::ULIDgenerate(20))
```

    ##  [1] "0001E2CWNS0ZTZT8N2HBARCQ8F" "0001E2CWNSMQYKTA2DC9M5Q5SG" "0001E2CWNS4SZYS03Z1FXY5THC" "0001E2CWNSS5SJRQESE956SASQ"
    ##  [5] "0001E2CWNS77P6X1MH1E93S9W8" "0001E2CWNSRYBVT63QPFVCHNJ3" "0001E2CWNS7KTHMJ6JPYDR7P66" "0001E2CWNSZRT8DDV952XAC2HH"
    ##  [9] "0001E2CWNS7ZF28CQDHHF84TQA" "0001E2CWNSQT8MDESQ6QGF0FBH" "0001E2CWNSRH50VAGBHAVTZ4C5" "0001E2CWNSQMX29P05JA2NRZ1N"
    ## [13] "0001E2CWNS0873HP4QQ1VP4MC2" "0001E2CWNS1V29YAKW2GY39E7R" "0001E2CWNSA40H808JCB9ZTY6B" "0001E2CWNSQTZ3Q41V7D6V32XW"
    ## [17] "0001E2CWNS9XPF4EG450HH8R9H" "0001E2CWNSHZ15YKJR0VA6TQ8S" "0001E2CWNSRAPRP614BM7VW3BP" "0001E2CWNSTGPN4PF6EKPW5H2A"

### Unmarshall

``` r
unmarshal(u)
```

    ##                     ts              rnd
    ## 1  2018-12-28 14:00:09 0ZTZT8N2HBARCQ8F
    ## 2  2018-12-28 14:00:09 MQYKTA2DC9M5Q5SG
    ## 3  2018-12-28 14:00:09 4SZYS03Z1FXY5THC
    ## 4  2018-12-28 14:00:09 S5SJRQESE956SASQ
    ## 5  2018-12-28 14:00:09 77P6X1MH1E93S9W8
    ## 6  2018-12-28 14:00:09 RYBVT63QPFVCHNJ3
    ## 7  2018-12-28 14:00:09 7KTHMJ6JPYDR7P66
    ## 8  2018-12-28 14:00:09 ZRT8DDV952XAC2HH
    ## 9  2018-12-28 14:00:09 7ZF28CQDHHF84TQA
    ## 10 2018-12-28 14:00:09 QT8MDESQ6QGF0FBH
    ## 11 2018-12-28 14:00:09 RH50VAGBHAVTZ4C5
    ## 12 2018-12-28 14:00:09 QMX29P05JA2NRZ1N
    ## 13 2018-12-28 14:00:09 0873HP4QQ1VP4MC2
    ## 14 2018-12-28 14:00:09 1V29YAKW2GY39E7R
    ## 15 2018-12-28 14:00:09 A40H808JCB9ZTY6B
    ## 16 2018-12-28 14:00:09 QTZ3Q41V7D6V32XW
    ## 17 2018-12-28 14:00:09 9XPF4EG450HH8R9H
    ## 18 2018-12-28 14:00:09 HZ15YKJR0VA6TQ8S
    ## 19 2018-12-28 14:00:09 RAPRP614BM7VW3BP
    ## 20 2018-12-28 14:00:09 TGPN4PF6EKPW5H2A
