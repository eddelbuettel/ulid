#!/usr/bin/env Rscript

library(ulid)
gen_ulid <- \(sleep) replicate(5, {Sys.sleep(sleep); generate()})

u <- gen_ulid(.1)
u
df <- unmarshal(u)
format(df$ts, "%Y-%m-%d %H:%M:%OS3")
diff(df$ts)
