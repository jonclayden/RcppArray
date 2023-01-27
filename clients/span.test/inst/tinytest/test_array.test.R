expect_stdout(span.test:::foo(1:3), "1 2 3")
expect_stdout(span.test:::foo(c(1.1,2.2,3.3)), "1 2 3")
expect_identical(span.test:::bar(), c(1,2,3))
# expect_identical(span.test:::baz(1:3), 1:2)
