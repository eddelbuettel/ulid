
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
devtools::install_git("https://git.sr.ht/~hrbrmstr/ulid")
# or
devtools::install_gitlab("hrbrmstr/ulid")
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

    ## [1] "0001EHX06QWTHZTAT6TE2GVAVT"

### Many

``` r
(u <- ulid::ULIDgenerate(20))
```

    ##  [1] "0001EHX06Q1C0H9NQPZQW7YN65" "0001EHX06QN1D7PYNDZ33B7QF1" "0001EHX06QZHV13RGNDWAJ7VX9" "0001EHX06Q2XC40QWY7AFR8DCZ"
    ##  [5] "0001EHX06QXWZRT9EJ1YM75214" "0001EHX06QYDSTG3KRWSKG01EE" "0001EHX06QNC8YWTX0H2M7HHYQ" "0001EHX06QFPBJWQ1PAQ1KXTJY"
    ##  [9] "0001EHX06Q6HW1WE5GP8Q9J6D6" "0001EHX06Q3QEY4KF2DX0FKTFB" "0001EHX06QS3FDSPSHW2W7AB7X" "0001EHX06QS2VENPTAADWYKAQW"
    ## [13] "0001EHX06QQJ7XEK9ZDT5542SD" "0001EHX06QHWVRKRF2SC86KB3Z" "0001EHX06QKG0V1129FBA0A5XY" "0001EHX06QY66KTA09CB9KKQP8"
    ## [17] "0001EHX06QZ9VMBDT8YZMXK1B5" "0001EHX06QJ60ZFVA45DFAGB5R" "0001EHX06QC0CXK917QFWXA71M" "0001EHX06QBW2TTWPDAFG23J7E"

### Unmarshal

``` r
unmarshal(u)
```

    ##                     ts              rnd
    ## 1  2019-07-04 18:42:31 1C0H9NQPZQW7YN65
    ## 2  2019-07-04 18:42:31 N1D7PYNDZ33B7QF1
    ## 3  2019-07-04 18:42:31 ZHV13RGNDWAJ7VX9
    ## 4  2019-07-04 18:42:31 2XC40QWY7AFR8DCZ
    ## 5  2019-07-04 18:42:31 XWZRT9EJ1YM75214
    ## 6  2019-07-04 18:42:31 YDSTG3KRWSKG01EE
    ## 7  2019-07-04 18:42:31 NC8YWTX0H2M7HHYQ
    ## 8  2019-07-04 18:42:31 FPBJWQ1PAQ1KXTJY
    ## 9  2019-07-04 18:42:31 6HW1WE5GP8Q9J6D6
    ## 10 2019-07-04 18:42:31 3QEY4KF2DX0FKTFB
    ## 11 2019-07-04 18:42:31 S3FDSPSHW2W7AB7X
    ## 12 2019-07-04 18:42:31 S2VENPTAADWYKAQW
    ## 13 2019-07-04 18:42:31 QJ7XEK9ZDT5542SD
    ## 14 2019-07-04 18:42:31 HWVRKRF2SC86KB3Z
    ## 15 2019-07-04 18:42:31 KG0V1129FBA0A5XY
    ## 16 2019-07-04 18:42:31 Y66KTA09CB9KKQP8
    ## 17 2019-07-04 18:42:31 Z9VMBDT8YZMXK1B5
    ## 18 2019-07-04 18:42:31 J60ZFVA45DFAGB5R
    ## 19 2019-07-04 18:42:31 C0CXK917QFWXA71M
    ## 20 2019-07-04 18:42:31 BW2TTWPDAFG23J7E

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
```

    ## [1] "0001CZM6DGVRVF68B8AP8VATS0"

``` r
unmarshal(ut)
```

    ##                    ts              rnd
    ## 1 2017-11-01 15:00:00 VRVF68B8AP8VATS0

## Package Code Metrics

``` r
cloc::cloc_pkg_md()
```

| Lang         | \# Files | (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | --: | --: | ---: | ----------: | ---: | -------: | ---: |
| C/C++ Header |        3 | 0.3 | 763 | 0.87 |         238 | 0.78 |      302 | 0.60 |
| C++          |        2 | 0.2 |  87 | 0.10 |          22 | 0.07 |       37 | 0.07 |
| R            |        4 | 0.4 |  15 | 0.02 |           7 | 0.02 |       94 | 0.19 |
| Rmd          |        1 | 0.1 |  10 | 0.01 |          38 | 0.12 |       73 | 0.14 |
