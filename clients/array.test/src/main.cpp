#include "RcppArray.h"

using namespace Rcpp;

template <typename T, size_t D> void printArray (const std::array<T,D> &arr) {
  Rcout << "Array: ";
  for (const T& el : arr)
    Rcout << el << " ";
  Rcout << std::endl;
}

// [[Rcpp::export]]
void foo() {
  Rcpp::NumericVector v = Rcpp::NumericVector::create(1,2,3);
  Rcpp::print(v);
  std::array<double,3> a = Rcpp::as<std::array<double,3>>(v);
  printArray(a);
}

// [[Rcpp::export]]
RObject bar() {
  return wrap(std::array<int,3>({ 1, 2, 3}));
}

// [[Rcpp::export]]
RObject baz() {
  return wrap(std::array<unsigned int,3>({ 1, 2, 3}));
}
