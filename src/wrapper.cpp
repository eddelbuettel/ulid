#include <Rcpp/Lightest>

#include "ulid/ulid.h"

inline long intrand() {
    GetRNGstate();
    long ret = (long)(unif_rand()*RAND_MAX);
    PutRNGstate();
    return(ret);
}

//' Generate ULID
//'
//' `generate()` generates a new [Universally Unique Lexicographically
//' Sortable Identifier](https://github.com/ulid/spec). Several aliases are
//' available for convience and backwards-compatibility.
//'
//' Note that up until release 0.3.1, the implementations had limitations
//' that resulted in second rather than millisecond resolution. This has
//' been addressed for release 0.4.0 and is now supported as expected.
//'
//' @md
//' @param n number of id's to generate (default = `1`)
//' @return A vector with `n` character strings (for `generate()` and `ts_generate()`)
//' @rdname ulid
//' @export
//' @examples
//' ULIDgenerate()
// [[Rcpp::export]]
Rcpp::CharacterVector generate(long n=1) {
    Rcpp::CharacterVector c(n);
    for (long i=0; i<=(n-1); i++) {
        c[i] = ulid::Marshal(ulid::CreateNowRand());
    }
    return(c);
}


//' Unmarshal a ULID into a data frame with timestamp and random bitstring columns
//'
//' @md
//' @param ulids character ULIDs (e.g. created with `generate()`)
//' @export
//' @rdname ulid
//' @return A `data.frame` with two columns `ts` and `rnd` (for `unmarshal()`)
//' @examples
//' unmarshal(generate())
// [[Rcpp::export]]
Rcpp::DataFrame unmarshal(std::vector<std::string> ulids) {
    size_t sz = ulids.size();
    Rcpp::DatetimeVector dt((int)sz);
    std::vector<std::string> cv(sz);
    for (size_t i=0; i<sz; i++) {
        try {
            // get the ulid out of the string passed in
            ulid::ULID u = ulid::Unmarshal(ulids[i]);
            // get a time_point from the ulid
            std::chrono::time_point ut = ulid::Time(u);
            // convert std::chrono object to a millisecond-resolution time point
            auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(ut);
            // scale to get POSIXct fractional seconds since epoch, at msec resolution
            double d = std::chrono::duration<double>(tp.time_since_epoch()).count();
            // and make that a standard POSIXct in R
            dt[i] = Rcpp::Datetime(d);
            cv[i] = ulids[i].substr(10);
        } catch(...) {
            Rcpp::stop("Cannot unmarshal '%s' which may not be a valid object.", ulids[i]);
        }
    }
    Rcpp::DataFrame out = Rcpp::DataFrame::create(Rcpp::Named("ts") = dt,
                                                  Rcpp::Named("rnd") = cv);
    return(out);
}


//' Generate ULIDs from timestamps
//'
//' This function generates a new [Universally Unique Lexicographically
//' Sortable Identifier](https://github.com/ulid/spec) from a vector of
//' `POSIXct` timestamps.
//'
//' @md
//' @param tsv vector of `POSIXct` values
//' @export
//' @rdname ulid
//' @examples
//' ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01"))
// [[Rcpp::export]]
Rcpp::CharacterVector ts_generate(Rcpp::DatetimeVector tsv) {
    Rcpp::CharacterVector c(tsv.size());
    for (long i=0; i<tsv.size(); i++) {
        ulid::ULID u = 0;
        //time_t t = static_cast<time_t>(tsv[i]);
        std::chrono::duration<double> duration(tsv[i]);
        auto dflr = std::chrono::round<std::chrono::microseconds>(duration);
        auto tp = std::chrono::system_clock::from_time_t(time_t{0}) + dflr;
        ulid::EncodeTime(tp, u);
        ulid::EncodeEntropyRand(u);
        c[i] = ulid::Marshal(u);
    }
    return(c);
}


// Checks if a character is a valid Crockford Base32 symbol (after normalization).
// Normalization maps I, L to 1, O to 0. Hyphens are ignored in the input.
static bool is_valid_Crockford_symbol(char c) {
    // Normalize to uppercase for consistent checking
    unsigned char uc = static_cast<unsigned char>(std::toupper(c));

    // Valid symbols are 0-9 and A-Z, excluding I, L, O, U in their final form.

    // We handle the I, L, O mapping during the check.
    if (uc >= '0' && uc <= '9') return true;
    if (uc >= 'A' && uc <= 'H') return true;
    if (uc >= 'J' && uc <= 'N') return true;
    if (uc >= 'P' && uc <= 'Z') return true;

    // Check for "confusable" characters that map to valid ones
    if (uc == 'I' || uc == 'L') return true; // Map to '1'
    if (uc == 'O') return true;             // Map to '0'

    // Hyphens are allowed and ignored
    if (uc == '-') return true;

    return false;
}

// Checks if the entire string conforms to the Base32 Crockford format rules.
// Does not check the optional checksum.
static bool is_base32_Crockford(const std::string& s) {
    for (char c : s) {
        // If any character is not a valid symbol or an ignored hyphen, the format is invalid
        if (!is_valid_Crockford_symbol(c)) {
            return false;
        }
    }
    return true;
}

//' Validates a ULID heuristicall for length and Crockford Base32
//'
//' Note that this validation leaves open other possible venues for being
//' invalid: a future date for the time component, or a nonsensical date
//' are two examples
//'
//' @md
//' @param s string with a ulid symbol
//' @return A boolean result (for `is_ulid()`)
//' @rdname ulid
//' @export
//' @examples
//' is_ulid(ULIDgenerate())
// [[Rcpp::export]]
bool is_ulid(const std::string& s) {
    return s.length() == 26 && is_base32_Crockford(s);
}
