
[![Project Status: Active – The project has reached a stable, usable
state and is being actively
developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Signed
by](https://img.shields.io/badge/Keybase-Verified-brightgreen.svg)](https://keybase.io/hrbrmstr)
![Signed commit
%](https://img.shields.io/badge/Signed_Commits-90.0%25-lightgrey.svg)
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
## [1] "0001EKRG9Z3CR2GXQG3MCN7R8T"
```

### Many

``` r
(u <- ulid::ULIDgenerate(20))
##  [1] "0001EKRG9Z9G02VMWAJPN6RTST" "0001EKRG9ZTEVMMA961V1PSH56" "0001EKRG9ZBK7SVA6W2YGKNM66" "0001EKRG9ZN5M21HPD49YY1GYF"
##  [5] "0001EKRG9ZF74J6RYS68QF1NGX" "0001EKRG9ZS7TPM10KKHCKNCZ5" "0001EKRG9ZBGGFSGE1EAM2F13M" "0001EKRG9Z2DQ9R0ZX907VXYZW"
##  [9] "0001EKRG9ZYAYCB3SC72P3F5ZE" "0001EKRG9Z8KZ1NC97DQT9CM9K" "0001EKRG9Z0TTWPCAAZ74XN9G3" "0001EKRG9Z7RBF3WJ63RG3JEMP"
## [13] "0001EKRG9Z1BW9WXS6H0M9E7R2" "0001EKRG9Z0PJTW7V4X030HDG0" "0001EKRG9ZG79SSF47HM064N50" "0001EKRG9Z6E260CXJ0MSSJM9J"
## [17] "0001EKRG9ZM0AHQ5PZMWHNP5P3" "0001EKRG9ZBMWP7JJQ86PVTDGT" "0001EKRG9Z49YK1FK9H8DMYX12" "0001EKRG9ZVSCHBCMN344AAFKQ"
```

### Unmarshal

``` r
unmarshal(u)
##                     ts              rnd
## 1  2019-07-27 08:19:11 9G02VMWAJPN6RTST
## 2  2019-07-27 08:19:11 TEVMMA961V1PSH56
## 3  2019-07-27 08:19:11 BK7SVA6W2YGKNM66
## 4  2019-07-27 08:19:11 N5M21HPD49YY1GYF
## 5  2019-07-27 08:19:11 F74J6RYS68QF1NGX
## 6  2019-07-27 08:19:11 S7TPM10KKHCKNCZ5
## 7  2019-07-27 08:19:11 BGGFSGE1EAM2F13M
## 8  2019-07-27 08:19:11 2DQ9R0ZX907VXYZW
## 9  2019-07-27 08:19:11 YAYCB3SC72P3F5ZE
## 10 2019-07-27 08:19:11 8KZ1NC97DQT9CM9K
## 11 2019-07-27 08:19:11 0TTWPCAAZ74XN9G3
## 12 2019-07-27 08:19:11 7RBF3WJ63RG3JEMP
## 13 2019-07-27 08:19:11 1BW9WXS6H0M9E7R2
## 14 2019-07-27 08:19:11 0PJTW7V4X030HDG0
## 15 2019-07-27 08:19:11 G79SSF47HM064N50
## 16 2019-07-27 08:19:11 6E260CXJ0MSSJM9J
## 17 2019-07-27 08:19:11 M0AHQ5PZMWHNP5P3
## 18 2019-07-27 08:19:11 BMWP7JJQ86PVTDGT
## 19 2019-07-27 08:19:11 49YK1FK9H8DMYX12
## 20 2019-07-27 08:19:11 VSCHBCMN344AAFKQ
```

### Use defined timestamps

``` r
(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
## [1] "0001CZM6DGXNMVPCQG0B295F3S"

unmarshal(ut)
##                    ts              rnd
## 1 2017-11-01 15:00:00 XNMVPCQG0B295F3S
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
