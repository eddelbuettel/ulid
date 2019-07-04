
[![Travis-CI Build
Status](https://travis-ci.org/hrbrmstr/ulid.svg?branch=master)](https://travis-ci.org/hrbrmstr/ulid)
[![AppVeyor build
status](https://ci.appveyor.com/api/projects/status/github/hrbrmstr/ulid?branch=master&svg=true)](https://ci.appveyor.com/project/hrbrmstr/ulid)
[![Coverage
Status](https://codecov.io/gh/hrbrmstr/ulid/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/ulid)
[![CRAN\_Status\_Badge](https://www.r-pkg.org/badges/version/ulid)](https://cran.r-project.org/package=ulid)

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

    ## [1] "0001EHX0NG5HMT3JM7FPPX3VE4"

### Many

``` r
(u <- ulid::ULIDgenerate(20))
```

    ##  [1] "0001EHX0NGZF5WY8FPK8ZAKSZW" "0001EHX0NG8BFAJMM5WY9TANC3" "0001EHX0NGNW3339V2AC502DZT" "0001EHX0NGJDXCHBH9H6FRT2Z2"
    ##  [5] "0001EHX0NGVEBX1HWE0YJDTHQF" "0001EHX0NG6XQBHZ6W8WEDB327" "0001EHX0NGPKVDNQRD11MEZB0A" "0001EHX0NGKYPGCBZ4254AW24R"
    ##  [9] "0001EHX0NGRCVC3AD2HMCDS0SK" "0001EHX0NGDWNZV19PFS0NKFS0" "0001EHX0NGKYV3BSBJF55DDSZ1" "0001EHX0NG7C16T3C373PD72K6"
    ## [13] "0001EHX0NG915080RV94QRNMJG" "0001EHX0NGFTD707BDMVJR7HQE" "0001EHX0NGYVAG9SVHVDGCZMWC" "0001EHX0NGYCDAPTJSCGAF0DQ8"
    ## [17] "0001EHX0NGG8MTT1RVSCP20VCG" "0001EHX0NGQBM57RVGW82WN2JA" "0001EHX0NGBKRM0DNC66RAMWT9" "0001EHX0NGA30VQ2FKTC2VBZFH"

### Unmarshal

``` r
unmarshal(u)
```

    ##                     ts              rnd
    ## 1  2019-07-04 18:50:24 ZF5WY8FPK8ZAKSZW
    ## 2  2019-07-04 18:50:24 8BFAJMM5WY9TANC3
    ## 3  2019-07-04 18:50:24 NW3339V2AC502DZT
    ## 4  2019-07-04 18:50:24 JDXCHBH9H6FRT2Z2
    ## 5  2019-07-04 18:50:24 VEBX1HWE0YJDTHQF
    ## 6  2019-07-04 18:50:24 6XQBHZ6W8WEDB327
    ## 7  2019-07-04 18:50:24 PKVDNQRD11MEZB0A
    ## 8  2019-07-04 18:50:24 KYPGCBZ4254AW24R
    ## 9  2019-07-04 18:50:24 RCVC3AD2HMCDS0SK
    ## 10 2019-07-04 18:50:24 DWNZV19PFS0NKFS0
    ## 11 2019-07-04 18:50:24 KYV3BSBJF55DDSZ1
    ## 12 2019-07-04 18:50:24 7C16T3C373PD72K6
    ## 13 2019-07-04 18:50:24 915080RV94QRNMJG
    ## 14 2019-07-04 18:50:24 FTD707BDMVJR7HQE
    ## 15 2019-07-04 18:50:24 YVAG9SVHVDGCZMWC
    ## 16 2019-07-04 18:50:24 YCDAPTJSCGAF0DQ8
    ## 17 2019-07-04 18:50:24 G8MTT1RVSCP20VCG
    ## 18 2019-07-04 18:50:24 QBM57RVGW82WN2JA
    ## 19 2019-07-04 18:50:24 BKRM0DNC66RAMWT9
    ## 20 2019-07-04 18:50:24 A30VQ2FKTC2VBZFH

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
```

    ## [1] "0001CZM6DG02A5QRDFBXV6W9CN"

``` r
unmarshal(ut)
```

    ##                    ts              rnd
    ## 1 2017-11-01 15:00:00 02A5QRDFBXV6W9CN

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
