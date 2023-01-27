#include "RcppArray.h"

using namespace Rcpp;

template <typename T, size_t D> void printSpan (const std::span<T,D> &sp) {
  Rcout << "Span: ";
  for (size_t i=0; i<sp.size(); i++)
    Rcout << sp[i] << " ";
  Rcout << std::endl;
}

// [[Rcpp::export]]
void foo(RObject x) {
  std::span<int,3> s = Rcpp::as<std::span<int,3>>(x);
  printSpan(s);
}

// [[Rcpp::export]]
RObject bar() {
  Rcpp::NumericVector v = Rcpp::NumericVector::create(1,2,3);
  std::span s(v.begin(), v.end());
  return wrap(s);
}
