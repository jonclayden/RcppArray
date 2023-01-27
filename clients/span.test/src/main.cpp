#include "RcppArray.h"

using namespace Rcpp;

#ifndef HAVE_SPAN
#error Span support isn't available
#endif

template <typename T, size_t D> void printSpan (const std::span<T,D> &sp) {
  Rcout << "Span: ";
  for (const T &el : sp)
    Rcout << el << " ";
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

// This will not compile because the converted vector's underlying type
// (double) doesn't match the span's specialised type
/* RObject baz(RObject x) {
  std::span<unsigned int,3> s = Rcpp::as<std::span<unsigned int,3>>(x);
  printSpan(s);
  std::vector<unsigned int> v = { 1, 2, 3 };
  return wrap(std::span(v).first(2));
} */
