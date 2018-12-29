
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
must be used. Within the same millisecond, sort order is not guaranteed.

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

    ## [1] "0001E2ERKHVPKZJ6FA6ZWHH1KS"

### Many

``` r
(u <- ulid::ULIDgenerate(20))
```

    ##  [1] "0001E2ERKHVX5QF5D59SX2E65T" "0001E2ERKHKD6MHKYB1G8JHN5X" "0001E2ERKHTK0XEHVV2G5877K9" "0001E2ERKHKFGG5NPN24PC1N0W"
    ##  [5] "0001E2ERKH3F48CAKJCVMSCBKS" "0001E2ERKHF3N0B94VK05GTXCW" "0001E2ERKH24GCJ2CT3Z5WM1FD" "0001E2ERKH381RJ232KK7SMWQW"
    ##  [9] "0001E2ERKH7NAZ1T4HR4ZRQRND" "0001E2ERKHSATC17G2QAPYXE0C" "0001E2ERKH76R83NFST3MZNW84" "0001E2ERKHFKS52SD8WJ8FHXMV"
    ## [13] "0001E2ERKHQM6VBM5JB235JJ1W" "0001E2ERKHXG2KNYWHHFS8X69Z" "0001E2ERKHQW821KPRM4GQFANJ" "0001E2ERKHD5KWTM5S345A3RP4"
    ## [17] "0001E2ERKH0D901W6KX66B1BHE" "0001E2ERKHKPHZBFSC16FC7FFC" "0001E2ERKHQQH7315GMY8HRYXV" "0001E2ERKH016YBAJAB7K9777T"

### Unmarshal

``` r
unmarshal(u)
```

    ##                     ts              rnd
    ## 1  2018-12-29 07:02:57 VX5QF5D59SX2E65T
    ## 2  2018-12-29 07:02:57 KD6MHKYB1G8JHN5X
    ## 3  2018-12-29 07:02:57 TK0XEHVV2G5877K9
    ## 4  2018-12-29 07:02:57 KFGG5NPN24PC1N0W
    ## 5  2018-12-29 07:02:57 3F48CAKJCVMSCBKS
    ## 6  2018-12-29 07:02:57 F3N0B94VK05GTXCW
    ## 7  2018-12-29 07:02:57 24GCJ2CT3Z5WM1FD
    ## 8  2018-12-29 07:02:57 381RJ232KK7SMWQW
    ## 9  2018-12-29 07:02:57 7NAZ1T4HR4ZRQRND
    ## 10 2018-12-29 07:02:57 SATC17G2QAPYXE0C
    ## 11 2018-12-29 07:02:57 76R83NFST3MZNW84
    ## 12 2018-12-29 07:02:57 FKS52SD8WJ8FHXMV
    ## 13 2018-12-29 07:02:57 QM6VBM5JB235JJ1W
    ## 14 2018-12-29 07:02:57 XG2KNYWHHFS8X69Z
    ## 15 2018-12-29 07:02:57 QW821KPRM4GQFANJ
    ## 16 2018-12-29 07:02:57 D5KWTM5S345A3RP4
    ## 17 2018-12-29 07:02:57 0D901W6KX66B1BHE
    ## 18 2018-12-29 07:02:57 KPHZBFSC16FC7FFC
    ## 19 2018-12-29 07:02:57 QQH7315GMY8HRYXV
    ## 20 2018-12-29 07:02:57 016YBAJAB7K9777T

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
```

    ## [1] "0001CZM6DGE66RJEY4N05F5R95"

``` r
unmarshal(ut)
```

    ##                    ts              rnd
    ## 1 2017-11-01 15:00:00 E66RJEY4N05F5R95

## Package Code Metrics

``` r
cloc::cloc_pkg_md()
```

| Lang         | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C/C++ Header |        3 | 0.27 | 755 | 0.87 |         231 | 0.78 |      264 | 0.57 |
| C++          |        2 | 0.18 |  81 | 0.09 |          22 | 0.07 |       37 | 0.08 |
| R            |        5 | 0.45 |  17 | 0.02 |           7 | 0.02 |       95 | 0.20 |
| Rmd          |        1 | 0.09 |  10 | 0.01 |          37 | 0.12 |       69 | 0.15 |
