
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

    ## [1] "0001E2CP1V7SS4P8R3JXKS654H"

### Many

``` r
ulid::ULIDgenerate(20)
```

    ##  [1] "0001E2CP1V9W5X9W7EXKPERJZT" "0001E2CP1V8GJ9FD9XJB2HEZBK" "0001E2CP1VDEM79FEDZJTK57DR" "0001E2CP1V8X07N2597NBGZQD1"
    ##  [5] "0001E2CP1VP0B03JYW2P27NEGY" "0001E2CP1VDZ9F06K04RJR68NB" "0001E2CP1V8MS3FVT3JYS7S642" "0001E2CP1VJC64WK60QB9N7V2S"
    ##  [9] "0001E2CP1VC26CCDS4BH730NFP" "0001E2CP1VFB04MCPB6CJDV2Z5" "0001E2CP1V24NC0SCDEDVS4AWZ" "0001E2CP1V08JV5664P962S6BY"
    ## [13] "0001E2CP1V0Y5Y8PXHMKYRS4G2" "0001E2CP1VHSNXR7GSBFE817G4" "0001E2CP1V09C00K3EZKEK6FD7" "0001E2CP1V19CKBAXNBN2CPJQ8"
    ## [17] "0001E2CP1VK35KF7PB0JQY567H" "0001E2CP1VT8WQ5W0K452JR4XG" "0001E2CP1VJTB1NB6344MH7QW5" "0001E2CP1VJ8QB3C3M7VVPS0Q6"
