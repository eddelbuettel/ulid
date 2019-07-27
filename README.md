
[![Project Status: Active – The project has reached a stable, usable
state and is being actively
developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Signed
by](https://img.shields.io/badge/Keybase-Verified-brightgreen.svg)](https://keybase.io/hrbrmstr)
![Signed commit
%](https://img.shields.io/badge/Signed_Commits-100%25-lightgrey.svg)
[![Linux build
Status](https://travis-ci.org/hrbrmstr/ulid.svg?branch=master)](https://travis-ci.org/hrbrmstr/ulid)
[![Windows build
status](https://ci.appveyor.com/api/projects/status/github/hrbrmstr/ulid?svg=true)](https://ci.appveyor.com/project/hrbrmstr/ulid)
[![Coverage
Status](https://codecov.io/gh/hrbrmstr/ulid/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/ulid)
[![cran
checks](https://cranchecks.info/badges/worst/ulid)](https://cranchecks.info/pkgs/ulid)
[![CRAN
status](https://www.r-pkg.org/badges/version/ulid)](https://www.r-pkg.org/pkg/ulid)
![Minimal R
Version](https://img.shields.io/badge/R%3E%3D-3.2.0-blue.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

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

  - `ts_generate`: Generate ULIDs from timestamps
  - `ULIDgenerate`: Generate ULID
  - `unmarshal`: Unmarshal a ULID into a data frame with timestamp and
    random bitstring columns

## Installation

``` r
install.packages("ulid", repos = "https://cinc.rud.is")
# or
remotes::install_git("https://git.rud.is/hrbrmstr/ulid.git")
# or
remotes::install_git("https://git.sr.ht/~hrbrmstr/ulid")
# or
remotes::install_gitlab("hrbrmstr/ulid")
# or
remotes::install_bitbucket("hrbrmstr/ulid")
# or
remotes::install_github("hrbrmstr/ulid")
```

NOTE: To use the ‘remotes’ install options you will need to have the
[{remotes} package](https://github.com/r-lib/remotes) installed.

## Usage

``` r
library(ulid)

# current verison
packageVersion("ulid")
## [1] '0.3.0'
```

### One

``` r
ulid::ULIDgenerate()
## [1] "0001EKRGEEV98QP062VNRX31P2"
```

### Many

``` r
(u <- ulid::ULIDgenerate(20))
##  [1] "0001EKRGEEV5XMP54RRRWAK318" "0001EKRGEEKX7VC0PF75AZJXHP" "0001EKRGEEXENNCQEH4KCH8QAD" "0001EKRGEEY41HJ6GMXRV1BQBA"
##  [5] "0001EKRGEE6HVD7ACWZ52MTVCJ" "0001EKRGEEQWXMPXGC0DGQN32B" "0001EKRGEE6W13BK92EF1RXYT7" "0001EKRGEE5A31H38NJFGTK8PC"
##  [9] "0001EKRGEEG2GXS53QY9F3M0A9" "0001EKRGEEDA3Y6Y0T52WTS6RM" "0001EKRGEE5WS2S3D9KY3F5H9Y" "0001EKRGEE24SZW5NATAADAY9Q"
## [13] "0001EKRGEEBEG51QCKXPM8ZS16" "0001EKRGEE1ZC1QY7RCJR9VJ0B" "0001EKRGEECJ50Z4FXM4HW6XWG" "0001EKRGEEER84JP8WTXV5DWV8"
## [17] "0001EKRGEEW3ABA82GZSRXN1RB" "0001EKRGEEAA60CYFGR8832JD6" "0001EKRGEE6W5ARCFHH6T75FPZ" "0001EKRGEE5WT4XNP7NS69BM3X"
```

### Unmarshal

``` r
unmarshal(u)
##                     ts              rnd
## 1  2019-07-27 08:21:34 V5XMP54RRRWAK318
## 2  2019-07-27 08:21:34 KX7VC0PF75AZJXHP
## 3  2019-07-27 08:21:34 XENNCQEH4KCH8QAD
## 4  2019-07-27 08:21:34 Y41HJ6GMXRV1BQBA
## 5  2019-07-27 08:21:34 6HVD7ACWZ52MTVCJ
## 6  2019-07-27 08:21:34 QWXMPXGC0DGQN32B
## 7  2019-07-27 08:21:34 6W13BK92EF1RXYT7
## 8  2019-07-27 08:21:34 5A31H38NJFGTK8PC
## 9  2019-07-27 08:21:34 G2GXS53QY9F3M0A9
## 10 2019-07-27 08:21:34 DA3Y6Y0T52WTS6RM
## 11 2019-07-27 08:21:34 5WS2S3D9KY3F5H9Y
## 12 2019-07-27 08:21:34 24SZW5NATAADAY9Q
## 13 2019-07-27 08:21:34 BEG51QCKXPM8ZS16
## 14 2019-07-27 08:21:34 1ZC1QY7RCJR9VJ0B
## 15 2019-07-27 08:21:34 CJ50Z4FXM4HW6XWG
## 16 2019-07-27 08:21:34 ER84JP8WTXV5DWV8
## 17 2019-07-27 08:21:34 W3ABA82GZSRXN1RB
## 18 2019-07-27 08:21:34 AA60CYFGR8832JD6
## 19 2019-07-27 08:21:34 6W5ARCFHH6T75FPZ
## 20 2019-07-27 08:21:34 5WT4XNP7NS69BM3X
```

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
## [1] "0001CZM6DG2THKSAX3F1SF30E7"

unmarshal(ut)
##                    ts              rnd
## 1 2017-11-01 15:00:00 2THKSAX3F1SF30E7
```

## ulid Code Metrics

``` r
cloc::cloc_pkg_md()
```

| Lang         | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C/C++ Header |        3 | 0.27 | 763 | 0.86 |         238 | 0.71 |      302 | 0.53 |
| C++          |        2 | 0.18 |  87 | 0.10 |          22 | 0.07 |       37 | 0.06 |
| Rmd          |        2 | 0.18 |  22 | 0.02 |          66 | 0.20 |      137 | 0.24 |
| R            |        4 | 0.36 |  15 | 0.02 |           7 | 0.02 |       94 | 0.16 |

## Code of Conduct

Please note that this project is released with a Contributor Code of
Conduct. By participating in this project you agree to abide by its
terms.
