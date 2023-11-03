expect_stdout(RcppArray:::intArray(1:3), "1 2 3")
expect_error(RcppArray:::intArray(1:4), "expected number of elements")
expect_stdout(RcppArray:::intArray(runif(3)), "0 0 0")
expect_error(RcppArray:::intArray(letters[1:3]), "Not compatible")

expect_stdout(RcppArray:::doubleArray(runif(3)), "0.")
expect_stdout(RcppArray:::doubleArray(1:3), "1")

expect_stdout(RcppArray:::unsignedArray(1:3), "1 2 3")
expect_stdout(RcppArray:::int64Array(1:3), "1 2 3")

expect_stdout(RcppArray:::stringArray(letters[1:3]), "a b c")
expect_stdout(RcppArray:::stringArray(1:3), "1 2 3")

expect_stdout(RcppArray:::intDoubleString(list(1L,2.56,"test")), "1 2.56 test")
expect_stdout(RcppArray:::intDoubleString(list(1,2,"3")), "1 2 3")
expect_error(RcppArray:::intDoubleString(as.list(1:2)), "expected number of elements")
expect_error(RcppArray:::intDoubleString(list(1,2,3)), "Expecting a single string")
