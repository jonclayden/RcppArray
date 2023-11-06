#' @importFrom Rcpp evalCpp
#' @useDynLib RcppArray
NULL

#' The 'RcppArray' package
#' 
#' This package presents no user-facing R code, but instead provides linked
#' packages containing C++ code with the ability to convert easily between R
#' vector types and the \code{std::array}, \code{std::tuple} and
#' \code{std::span} classes. See the package README and/or included header
#' \code{RcppArray.h} for further details.
#' 
#' @keywords internal
"_PACKAGE"
