#include "RcppArray.h"

#include <Rcpp/Lightest>

using namespace Rcpp;

template <typename T, size_t D> void printArray (const std::array<T,D> &arr) {
  Rcout << "Array: ";
  for (size_t i=0; i<D; i++)
    Rcout << arr[i] << " ";
  Rcout << std::endl;
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

// [[Rcpp::export]]
void intDoubleString(RObject x) {
  std::tuple<int,double,std::string> t = Rcpp::as<std::tuple<int,double,std::string>>(x);
  Rcout << "Tuple: " << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) << std::endl;
}

// [[Rcpp::export]]
SEXP wrapTuple() {
  std::tuple<int,double,std::string> t = { 1, 2.56, "test" };
  return Rcpp::wrap(t);
}
