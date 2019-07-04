
[![Travis-CI Build
Status](https://travis-ci.org/hrbrmstr/ulid.svg?branch=master)](https://travis-ci.org/hrbrmstr/ulid)
[![AppVeyor build
status](https://ci.appveyor.com/api/projects/status/github/hrbrmstr/ulid?branch=master&svg=true)](https://ci.appveyor.com/project/hrbrmstr/ulid)
[![Coverage
Status](https://codecov.io/gh/hrbrmstr/ulid/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/ulid)
[![CRAN\_Status\_Badge](https://www.r-pkg.org/badges/version/ulid)](https://cran.r-project.org/package=ulid)

# ulid

Universally Unique Lexicographically Sortable Identifiers

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
install.packages("ulid", repos = "https://cinc.rud.is")
# or
devtools::install_git("https://git.rud.is/hrbrmstr/ulid.git")
# or
devtools::install_git("https://git.sr.ht/~hrbrmstr/ulid")
# or
devtools::install_gitlab("hrbrmstr/ulid")
# or
devtools::install_bitbucket("hrbrmstr/ulid")
# or
devtools::install_github("hrbrmstr/ulid")
```

## Usage

``` r
library(ulid)

# current verison
packageVersion("ulid")
```

    ## [1] '0.3.0'

### One

``` r
ulid::ULIDgenerate()
```

    ## [1] "0001EHX2TS3FANDH25PE5CT843"

### Many

``` r
(u <- ulid::ULIDgenerate(20))
```

    ##  [1] "0001EHX2TSMATE28BM0P9P4ZT7" "0001EHX2TSQ07QG90YYBCCGVRH" "0001EHX2TS3QJ5X4JA9WVDZCTM" "0001EHX2TSJRXPB6F8C8FQRCVN"
    ##  [5] "0001EHX2TSKPY54201E740DZGP" "0001EHX2TSNERDHBA5WW6JVHV7" "0001EHX2TS8PSY34CSC9J0FRBZ" "0001EHX2TS20FZ80A0H1JXH2HJ"
    ##  [9] "0001EHX2TSVM253MAWW6GY2VS7" "0001EHX2TSCR0AWQKH6NNXSYAM" "0001EHX2TSWAZDQ9E87PBEG4AG" "0001EHX2TS6WHF11YM851XMWXC"
    ## [13] "0001EHX2TSS52C9F7RG4BH39ME" "0001EHX2TSEPB58N4M551QFGCS" "0001EHX2TSZC15E2F729MS59AB" "0001EHX2TST95FS48CAFBYVG8S"
    ## [17] "0001EHX2TSQQ9QYG7YMY5VDXBC" "0001EHX2TSKBET2J6ZQ7YGJ3FT" "0001EHX2TSJW2JNK61RQ8JSSNA" "0001EHX2TSV4CV21CTVNAAQE4V"

### Unmarshal

``` r
unmarshal(u)
```

    ##                     ts              rnd
    ## 1  2019-07-04 19:27:21 MATE28BM0P9P4ZT7
    ## 2  2019-07-04 19:27:21 Q07QG90YYBCCGVRH
    ## 3  2019-07-04 19:27:21 3QJ5X4JA9WVDZCTM
    ## 4  2019-07-04 19:27:21 JRXPB6F8C8FQRCVN
    ## 5  2019-07-04 19:27:21 KPY54201E740DZGP
    ## 6  2019-07-04 19:27:21 NERDHBA5WW6JVHV7
    ## 7  2019-07-04 19:27:21 8PSY34CSC9J0FRBZ
    ## 8  2019-07-04 19:27:21 20FZ80A0H1JXH2HJ
    ## 9  2019-07-04 19:27:21 VM253MAWW6GY2VS7
    ## 10 2019-07-04 19:27:21 CR0AWQKH6NNXSYAM
    ## 11 2019-07-04 19:27:21 WAZDQ9E87PBEG4AG
    ## 12 2019-07-04 19:27:21 6WHF11YM851XMWXC
    ## 13 2019-07-04 19:27:21 S52C9F7RG4BH39ME
    ## 14 2019-07-04 19:27:21 EPB58N4M551QFGCS
    ## 15 2019-07-04 19:27:21 ZC15E2F729MS59AB
    ## 16 2019-07-04 19:27:21 T95FS48CAFBYVG8S
    ## 17 2019-07-04 19:27:21 QQ9QYG7YMY5VDXBC
    ## 18 2019-07-04 19:27:21 KBET2J6ZQ7YGJ3FT
    ## 19 2019-07-04 19:27:21 JW2JNK61RQ8JSSNA
    ## 20 2019-07-04 19:27:21 V4CV21CTVNAAQE4V

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
```

    ## [1] "0001CZM6DGX836E94E630NTNNB"

``` r
unmarshal(ut)
```

    ##                    ts              rnd
    ## 1 2017-11-01 15:00:00 X836E94E630NTNNB

## Package Code Metrics

``` r
cloc::cloc_pkg_md()
```

| Lang         | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C/C++ Header |        3 | 0.27 | 763 | 0.86 |         238 | 0.72 |      302 | 0.53 |
| C++          |        2 | 0.18 |  87 | 0.10 |          22 | 0.07 |       37 | 0.07 |
| Rmd          |        2 | 0.18 |  20 | 0.02 |          65 | 0.20 |      136 | 0.24 |
| R            |        4 | 0.36 |  15 | 0.02 |           7 | 0.02 |       94 | 0.17 |
