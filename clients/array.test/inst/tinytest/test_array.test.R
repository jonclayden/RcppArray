expect_stdout(array.test:::foo(), "1 2 3")
expect_identical(array.test:::bar(), 1:3)
expect_equal(array.test:::baz(), 1:3)
expect_inherits(array.test:::baz(), "numeric")
