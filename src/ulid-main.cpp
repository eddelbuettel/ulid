#include <Rcpp.h>

#include "ulid.h"

using namespace Rcpp;

//' Generate ULIDs from timestamps
//'
//' This function generates a new [Universally Unique Lexicographically
//' Sortable Identifier](https://github.com/ulid/spec) from a vector of
//' `POSIXct` timestamps.
//'
//' @md
//' @param tsv vector of `POSIXct` values
//' @export
//' @examples
//' ts_generate(as.POSIXct("2017-11-01 15:00:00", origin="1970-01-01"))
// [[Rcpp::export]]
CharacterVector ts_generate(Rcpp::DatetimeVector tsv) {
  CharacterVector c(tsv.size());
  for (long i=0; i<tsv.size(); i++) {
    ulid::ULID u = 0;
    time_t t = static_cast<time_t>(tsv[i]);
    ulid::EncodeTime(t, u);
    ulid::EncodeEntropyRand(u);
    c[i] = ulid::Marshal(u);
  }
  return(c);
}

inline long intrand() {
  GetRNGstate();
  long ret = (long)(unif_rand()*RAND_MAX);
  PutRNGstate();
  return(ret);
}

//' Generate ULID
//'
//' [ULIDgenerate()] generates a new [Universally Unique Lexicographically
//' Sortable Identifier](https://github.com/ulid/spec).
//'
//' @md
//' @param n number of id's to generate (default = `1`)
//' @export
//' @examples
//' ULIDgenerate()
// [[Rcpp::export]]
CharacterVector ULIDgenerate(long n=1) {
  CharacterVector c(n);
  for (long i=0; i<=(n-1); i++) {
    c[i] = ulid::Marshal(ulid::CreateNowRand());
  }
  return(c);
}


//' Unmarshal a ULID into a data frame with timestamp and random bitstring columns
//'
//' @md
//' @param ulids character ULIDs (e.g. created with [ULIDgenerate()])
//' @export
//' @return data frame (tibble)
//' @examples
//' unmarshal(ULIDgenerate())
// [[Rcpp::export]]
DataFrame unmarshal(std::vector<std::string> ulids) {

  unsigned long sz = ulids.size();
  Rcpp::DatetimeVector dt(sz);
  std::vector<std::string> cv(sz);

  for (unsigned long i=0; i<sz; i++) {

    ulid::ULID u = ulid::Unmarshal(ulids[i]);

    dt[i] = Rcpp::Datetime(ulid::Time(u));
    cv[i] = ulids[i].substr(10);

  }

  DataFrame out =
    DataFrame::create(
      _["ts"] = dt,
      _["rnd"] = cv,
      _["stringsAsFactors"] = false
    );

  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");

  return(out);

}

