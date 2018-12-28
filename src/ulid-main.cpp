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
