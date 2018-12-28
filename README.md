
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

  - `ULIDgenerate` / `generate` / `ulid_generate`: Generate a time-based
    ULID
  - `ts_generate`: Generate ULID from timestamps
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

    ## [1] "0001E2D1EVWTN5G7C2244Q8SJ8"

### Many

``` r
(u <- ulid::ULIDgenerate(20))
```

    ##  [1] "0001E2D1EV54P4DCS24WSYX2R1" "0001E2D1EV0D75WQ55XQ9TQ3RS" "0001E2D1EVPZVD2W626E49GHT6" "0001E2D1EVZCCD9DNH3SSTQN3K"
    ##  [5] "0001E2D1EV6B8SYC81KSMVMM80" "0001E2D1EV5CT6Q9JB5H1SA5RF" "0001E2D1EVZEBD1J5RMGJ9B23S" "0001E2D1EVTX25KJGVGDJ61X5J"
    ##  [9] "0001E2D1EVAT8T7V54G6ZQCX0F" "0001E2D1EVKRPHHANAZ5A070HN" "0001E2D1EVPZJ1NDV7M27TQBH0" "0001E2D1EVVZ0PAJVS3WY08QA4"
    ## [13] "0001E2D1EVZRQGQV0MEK65DKRA" "0001E2D1EVV1KP7XEKSEQDV8XQ" "0001E2D1EVZH19KNXG6GVEKKHP" "0001E2D1EVB7D31MKZQTRQP0S1"
    ## [17] "0001E2D1EVTPGNFEYW4MKGHZA1" "0001E2D1EV8SG2BCSFS3G7SXFV" "0001E2D1EV22JE3JZYF8P33PGS" "0001E2D1EVC6X98C3TT0N9B75C"

### Unmarshal

``` r
unmarshal(u)
```

    ##                     ts              rnd
    ## 1  2018-12-28 15:21:47 54P4DCS24WSYX2R1
    ## 2  2018-12-28 15:21:47 0D75WQ55XQ9TQ3RS
    ## 3  2018-12-28 15:21:47 PZVD2W626E49GHT6
    ## 4  2018-12-28 15:21:47 ZCCD9DNH3SSTQN3K
    ## 5  2018-12-28 15:21:47 6B8SYC81KSMVMM80
    ## 6  2018-12-28 15:21:47 5CT6Q9JB5H1SA5RF
    ## 7  2018-12-28 15:21:47 ZEBD1J5RMGJ9B23S
    ## 8  2018-12-28 15:21:47 TX25KJGVGDJ61X5J
    ## 9  2018-12-28 15:21:47 AT8T7V54G6ZQCX0F
    ## 10 2018-12-28 15:21:47 KRPHHANAZ5A070HN
    ## 11 2018-12-28 15:21:47 PZJ1NDV7M27TQBH0
    ## 12 2018-12-28 15:21:47 VZ0PAJVS3WY08QA4
    ## 13 2018-12-28 15:21:47 ZRQGQV0MEK65DKRA
    ## 14 2018-12-28 15:21:47 V1KP7XEKSEQDV8XQ
    ## 15 2018-12-28 15:21:47 ZH19KNXG6GVEKKHP
    ## 16 2018-12-28 15:21:47 B7D31MKZQTRQP0S1
    ## 17 2018-12-28 15:21:47 TPGNFEYW4MKGHZA1
    ## 18 2018-12-28 15:21:47 8SG2BCSFS3G7SXFV
    ## 19 2018-12-28 15:21:47 22JE3JZYF8P33PGS
    ## 20 2018-12-28 15:21:47 C6X98C3TT0N9B75C

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
```

    ## [1] "0001CZM6DG91GGPEZMYZ1TNKH3"

``` r
unmarshal(ut)
```

    ##                    ts              rnd
    ## 1 2017-11-01 15:00:00 91GGPEZMYZ1TNKH3
