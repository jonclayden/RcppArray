expect_stdout(Rcpp.asArray:::foo(), "1 2 3")

expect_stdout(Rcpp.asArray:::intArray(1:3), "1 2 3")
expect_error(Rcpp.asArray:::intArray(1:4), "expected number of elements")

expect_stdout(Rcpp.asArray:::doubleArray(runif(3)), "0.")

expect_error(Rcpp.asArray:::int64Array(1:3), "Wrong R type")
