#' @title
#' Generate Universally Unique Lexicographically Sortable Identifiers
#'
#' @description
#' As described in the [ulid specification repo](https://github.com/ulid/spec), and slightly edited here,
#' UUID use can be suboptimal for many uses-cases because:(grifted from <https://github.com/ulid/spec>)
#'
#' UUID can be suboptimal for many uses-cases because:
#'
#' - It isn't the most character efficient way of encoding 128 bits of randomness
#' - UUID v1/v2 is impractical in many environments, as it requires access to a unique, stable MAC address
#' - UUID v3/v5 requires a unique seed and produces randomly distributed IDs, which can cause fragmentation in many data structures
#' - UUID v4 provides no other information than randomness which can cause fragmentation in many data structures
#'
#' Instead, an alternative is proposed in ULID:
#'
#' ```
#' ulid() // 01ARZ3NDEKTSV4RRFFQ69G5FAV
#' ```
#'
#' with the following properties:
#'
#' - 128-bit compatibility with UUID
#' - 1.21e+24 unique ULIDs per millisecond
#' - Lexicographically sortable!
#' - Canonically encoded as a 26 character string, as opposed to the 36 character UUID
#' - Uses Crockford's base32 for better efficiency and readability (5 bits per character)
#' - Case insensitive
#' - No special characters (URL safe)
#' - Monotonic sort order (correctly detects and handles the same millisecond)
#'
#' ```
#' 01AN4Z07BY      79KA1307SR9X4MV3
#'
#' |----------|    |----------------|
#'   Timestamp          Randomness
#'    48bits              80bits
#' ```
#'
#' **Components**
#'
#' _Timestamp_
#' - 48 bit integer
#' - UNIX-time in milliseconds
#' - Will not run out of space until the year 10889 AD.
#'
#' _Randomness_
#' - 80 bits
#' - Cryptographically secure source of randomness, if possible
#'
#' **Sorting**
#'
#' The left-most character must be sorted first, and the right-most character sorted last (lexical order).
#' The default ASCII character set must be used. Within the same millisecond, sort order is not guaranteed.
#'
#' @md
#' @name ulid
#' @author Bob Rudis (bob@@rud.is) wrote the package based on `ulid` C++ library by Suyash Verma.
#'
#' Dirk Eddelbuettel now maintains the package.
#' @useDynLib ulid, .registration = TRUE
#' @importFrom Rcpp evalCpp
#' @seealso The [ulid specification](https://github.com/ulid/spec) provides the reference.
"_PACKAGE"

#' @rdname ulid
#' @export
ulid <- generate

#' @rdname ulid
#' @export
ulid_generate <- generate

#' @rdname ulid
#' @export
ULIDgenerate <- generate
