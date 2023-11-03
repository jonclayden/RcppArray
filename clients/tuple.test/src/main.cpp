#include "RcppArray.h"

using namespace Rcpp;

typedef typename std::tuple<int,double,std::string> TT;

void printTuple (const TT &tup) {
  Rcout << "Tuple: " << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << std::endl;
}

// [[Rcpp::export]]
void foo() {
  List l = List::create(1, 2.56, "test");
  Rcpp::print(l);
  TT t = Rcpp::as<TT>(l);
  printTuple(t);
}

// [[Rcpp::export]]
RObject bar() {
  return wrap(TT({ 1, 2.56, "test" }));
}

// [[Rcpp::export]]
RObject baz() {
  return wrap(std::tuple<unsigned int,double,std::string>({ 1, 2.56, "test" }));
}
