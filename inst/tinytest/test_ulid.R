library(ulid)

x <- ULIDgenerate()
expect_true(is.character(x))
expect_true(nchar(x) == 26)

x <- ULIDgenerate(20)
expect_true(is.character(x))
expect_true(length(x) == 20)
expect_true(sum(nchar(x)) == 520)
expect_true(all(rle(x)[["values"]] == x))

x <- unmarshal(x)
expect_true(is.data.frame(x))
expect_true(nrow(x) == 20)
expect_true(inherits(x[["ts"]], "POSIXct"))
expect_true(is.character(x[["rnd"]]))
expect_true(sum(nchar(x[["rnd"]])) == 320)
expect_true(all(rle(x[["rnd"]])[["values"]] == x[["rnd"]]))

x <- ts_generate(as.POSIXct("2017-11-01 15:00:00"))
y <- unmarshal(x)
expect_true(is.data.frame(y))
expect_true(y[["ts"]][[1]] == "2017-11-01 15:00:00")
expect_true(is.character(y[["rnd"]][[1]]))
expect_true(nchar(y[["rnd"]][[1]]) == 16)

## now with milliseconds
x <- ts_generate(as.POSIXct("2017-11-01 15:00:00") + (0:4)*0.25)
y <- unmarshal(x)
expect_true(is.data.frame(y))
expect_true(y[["ts"]][[1]] == "2017-11-01 15:00:00")
expect_true(y[["ts"]][[5]] == "2017-11-01 15:00:01")
expect_true(is.character(y[["rnd"]][[1]]))
expect_true(nchar(y[["rnd"]][[1]]) == 16)

## check time difference is the 250ms we started from
expect_equal(as.numeric(diff(y$ts)), rep(0.25, 4))

## check sorting still holds too
expect_equal(xtfrm(x), seq(1,5))
