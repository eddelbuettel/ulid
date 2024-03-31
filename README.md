
[![CRAN
status](https://www.r-pkg.org/badges/version/ulid)](https://www.r-pkg.org/pkg/ulid)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

# ulid

Universally Unique Lexicographically Sortable Identifiers

## Description

As described in the [ulid specification repo](https://github.com/ulid/spec),
and slightly edited here, UUID use can be suboptimal for many uses-cases because:

  - It is not the most character efficient way of encoding 128 bits of randomness
  - UUID v1/v2 is impractical in many environments, as it requires access to a unique, stable MAC address
  - UUID v3/v5 requires a unique seed and produces randomly distributed IDs, which can cause fragmentation in many data structures
  - UUID v4 provides no other information than randomness which can cause fragmentation in many data structures

Instead, an alternative is proposed in ULID:

``` javascript
ulid() // 01ARZ3NDEKTSV4RRFFQ69G5FAV
```

with the following properties:

  - 128-bit compatibility with UUID
  - 1.21e+24 unique ULIDs per millisecond
  - Lexicographically sortable\!
  - Canonically encoded as a 26 character string, as opposed to the 36 character UUID
  - Uses [base32 by Crockford](https://www.crockford.com/base32.html) for better efficiency and readability (5 bits per character)
  - Case insensitive
  - No special characters (URL safe)
  - Monotonic sort order (correctly detects and handles the same millisecond)


```
 01AN4Z07BY      79KA1307SR9X4MV3

|----------|    |----------------|
 Timestamp          Randomness
   48bits             80bits
```

### Components

**Timestamp**

- 48 bit integer
- UNIX-time in milliseconds
- Will not run out of space until the year 10889 AD.

**Randomness**

- 80 bits
- Cryptographically secure source of randomness, if possible

### Sorting

The left-most character must be sorted first, and the right-most
character sorted last (lexical order). The default ASCII character set
must be used. Within the same millisecond, sort order is not guaranteed.

## What Is Supoorted:

The following functions are implemented:

  - `ts_generate`: Generate ULIDs from timestamps
  - `ULIDgenerate`: Generate ULID
  - `unmarshal`: Unmarshal a ULID into a data frame with timestamp and random bitstring columns
  - `ulid`: Alias fir `ULIDgenerate`

## Installation

The package is currently not on CRAN but can be installed from this repository.

## Usage

``` r
ulid::ULIDgenerate()
## [1] "0001EKRGEEV98QP062VNRX31P2"

(u <- ulid::ULIDgenerate(20))
##  [1] "0001EKRGEEV5XMP54RRRWAK318" "0001EKRGEEKX7VC0PF75AZJXHP" "0001EKRGEEXENNCQEH4KCH8QAD" "0001EKRGEEY41HJ6GMXRV1BQBA"
##  [5] "0001EKRGEE6HVD7ACWZ52MTVCJ" "0001EKRGEEQWXMPXGC0DGQN32B" "0001EKRGEE6W13BK92EF1RXYT7" "0001EKRGEE5A31H38NJFGTK8PC"
##  [9] "0001EKRGEEG2GXS53QY9F3M0A9" "0001EKRGEEDA3Y6Y0T52WTS6RM" "0001EKRGEE5WS2S3D9KY3F5H9Y" "0001EKRGEE24SZW5NATAADAY9Q"
## [13] "0001EKRGEEBEG51QCKXPM8ZS16" "0001EKRGEE1ZC1QY7RCJR9VJ0B" "0001EKRGEECJ50Z4FXM4HW6XWG" "0001EKRGEEER84JP8WTXV5DWV8"
## [17] "0001EKRGEEW3ABA82GZSRXN1RB" "0001EKRGEEAA60CYFGR8832JD6" "0001EKRGEE6W5ARCFHH6T75FPZ" "0001EKRGEE5WT4XNP7NS69BM3X"

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

(ut <- ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01")))
## [1] "0001CZM6DG2THKSAX3F1SF30E7"

unmarshal(ut)
##                    ts              rnd
## 1 2017-11-01 15:00:00 2THKSAX3F1SF30E7
```

## Author

[Suyash Verma](https://github.com/suyash) write the C++ header library [ulid](https://github.com/suyash/ulid).

[Bob Rudis](https://rud.is) created the R package, prepared versions 0.1.0 and 0.2.0, and released version 0.3.0 to CRAN.

[Dirk Eddelbuettel](https://dirk.eddelbuettel.com) is the current maintainer.

## License

The package is licensed under the MIT License
