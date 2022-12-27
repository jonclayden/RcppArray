#include "array.h"

#include <Rcpp/Lightest>

using namespace Rcpp;

template <typename T> void printArray (const std::array<T,3> &arr) {
  Rcout << "Hi "
        << arr[0] << " "
        << arr[1] << " "
        << arr[2] << std::endl;
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

// [[Rcpp::export]]
void intArray(RObject x) {
  std::array<int,3> a = Rcpp::as<std::array<int,3>>(x);
  printArray(a);
}

// [[Rcpp::export]]
void unsignedArray(RObject x) {
  std::array<unsigned int,3> a = Rcpp::as<std::array<unsigned int,3>>(x);
  printArray(a);
}

// [[Rcpp::export]]
void doubleArray(RObject x) {
  std::array<double,3> a = Rcpp::as<std::array<double,3>>(x);
  printArray(a);
}

// [[Rcpp::export]]
void stringArray(RObject x) {
  std::array<std::string,3> a = Rcpp::as<std::array<std::string,3>>(x);
  printArray(a);
}

// [[Rcpp::export]]
void int64Array(RObject x) {
  std::array<int64_t,3> a = Rcpp::as<std::array<int64_t,3>>(x);
  printArray(a);
}
