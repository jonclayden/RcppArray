#' Test the issue
#' 
#' This function just calls into C++ to convert its argument to a std::array,
#' and then prints its elements. An error will be produced if vec doesn't have
#' three elements or can't be converted to double.
#' 
#' @param vec Test vector
#' @export
test <- function (vec)
{
    .Call("test", vec, PACKAGE="Rcpp.asArray")
}

#' @importFrom Rcpp evalCpp
#' @useDynLib Rcpp.asArray
NULL
