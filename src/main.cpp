#include "array.h"

#include <Rcpp/Lightest>

// [[Rcpp::export]]
void foo() {
  Rcpp::NumericVector v = Rcpp::NumericVector::create(1,2,3);
  Rcpp::print(v);
  std::array<double,3> a = Rcpp::as<std::array<double,3>>(v);
  Rcpp::Rcout << "Hi "
              << a[0] << " "
              << a[1] << " "
              << a[2] << std::endl;
}
