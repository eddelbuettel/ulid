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
//' Note that the current implementations has a limitation that results in
//' second rather than millisecond resolution. See for example issue #13 at
//' the upstream repo.
//'
//' @md
//' @param n number of id's to generate (default = `1`)
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
//' @return A `data.frame` with two columns `ts` and `rnd`.
//' @examples
//' unmarshal(generate())
// [[Rcpp::export]]
Rcpp::DataFrame unmarshal(std::vector<std::string> ulids) {
    unsigned long sz = ulids.size();
    Rcpp::DatetimeVector dt(sz);
    std::vector<std::string> cv(sz);
    for (unsigned long i=0; i<sz; i++) {
        ulid::ULID u = ulid::Unmarshal(ulids[i]);
        // convert std::chrono object to a millisecond-resolution time point
        auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(ulid::Time(u));
        // scale to get POSIXct fractional seconds since epoch, at msec resolution
        double d = tp.time_since_epoch().count() / 1000.0;
        dt[i] = Rcpp::Datetime(d);
        cv[i] = ulids[i].substr(10);
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
