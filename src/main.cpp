#include "array.h"

#include <Rcpp.h>

RcppExport SEXP test (SEXP vec)
{
BEGIN_RCPP
    std::array<double,3> arr = Rcpp::as<std::array<double,3>>(vec);
    Rprintf("%f - %f - %f\n", arr[0], arr[1], arr[2]);
    return R_NilValue;
END_RCPP
}
