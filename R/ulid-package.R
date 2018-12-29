#' Generate Universally Unique Lexicographically Sortable Identifier
#'
#' (grifted from <https://github.com/ulid/spec>)
#'
#' UUID can be suboptimal for many uses-cases because:
#'
#' - It isn't the most character efficient way of encoding 128 bits of randomness
#' - UUID v1/v2 is impractical in many environments, as it requires access to a unique, stable MAC address
#' - UUID v3/v5 requires a unique seed and produces randomly distributed IDs, which can cause fragmentation in many data structures
#' - UUID v4 provides no other information than randomness which can cause fragmentation in many data structures
#'
#' Instead, herein is proposed ULID:
#'
#' ```
#' ulid() // 01ARZ3NDEKTSV4RRFFQ69G5FAV
#' ```
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
#' - Won't run out of space till the year 10889 AD.
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
#' - URL: <https://gitlab.com/hrbrmstr/ulid>
#' - BugReports: <https://gitlab.com/hrbrmstr/ulid/issues>
#'
#' @md
#' @name ulid
#' @docType package
#' @author Bob Rudis (bob@@rud.is)
#' @useDynLib ulid, .registration = TRUE
#' @importFrom Rcpp sourceCpp
NULL
