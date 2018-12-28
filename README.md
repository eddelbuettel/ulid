
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

    ## [1] "0001E2CNHEB71VBCP6Y1M3RAGR"

### Many

``` r
ulid::ULIDgenerate(20)
```

    ##  [1] "0001E2CNHEVGN75257V2TZBSBD" "0001E2CNHE7WRWS5HB52XHCK0X" "0001E2CNHEATMJ0TNJK0D7R9NV" "0001E2CNHE3GS9WDYF9V45YRVG"
    ##  [5] "0001E2CNHEJ4NZPP9TB4K53Z8B" "0001E2CNHE383ZMKDRPNR8N9B0" "0001E2CNHEYPRFKC6BBXXGZ8TK" "0001E2CNHEQK1M8FZKDGPG32TS"
    ##  [9] "0001E2CNHECVSY4VD69NMT8JNK" "0001E2CNHEEVPNZTXZ9QA66DRK" "0001E2CNHESEDDC41ETPJJWN8C" "0001E2CNHEZ4D0D9XGAV2AK5TA"
    ## [13] "0001E2CNHEZF13W414M0AKYKX8" "0001E2CNHEVKZ4WQZTFH4FBX4D" "0001E2CNHE69545C9DN9A29EP8" "0001E2CNHEJMDHYHFW3FBTZG5X"
    ## [17] "0001E2CNHEN9EZ4HHZCS3NQ9C0" "0001E2CNHEWR1SWBEPG69PDHXN" "0001E2CNHEVEPE5P2K5DNHB6CT" "0001E2CNHE8WX898BTPG3EJMQN"
