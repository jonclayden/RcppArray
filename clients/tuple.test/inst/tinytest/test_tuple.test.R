expect_stdout(tuple.test:::foo(), "1 2.56 test")
expect_identical(tuple.test:::bar(), list(1,2.56,"test"))
expect_inherits(tuple.test:::baz(), "list")
expect_equal(tuple.test:::baz(), list(1,2.56,"test"))
