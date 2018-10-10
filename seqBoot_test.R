library(Rcpp)
library(RcppArmadillo)

sourceCpp("seqBoot.cpp")
set.seed(1)
rows <- 200
cols <- 8
sLen <- 20
mat <- matrix(as.integer(runif(n = rows * cols) > 0.5), ncol = cols)
1 + seqBoot(mat, sLen, 1)
