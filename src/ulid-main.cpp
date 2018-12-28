#include <Rcpp.h>

#include "ulid.h"

using namespace Rcpp;

//' Generate ULID
//'
//' [ULIDgenerate()] generates a new []Universally Unique Lexicographically
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
//' @examples
//' unmarshal(ULIDgenerate())
// [[Rcpp::export]]
DataFrame unmarshal(std::vector<std::string> ulids) {

  unsigned long sz = ulids.size();
  std::vector<Rcpp::Datetime> dt(sz);
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

