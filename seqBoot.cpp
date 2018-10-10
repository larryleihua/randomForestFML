// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;

Rcpp::IntegerVector rowSumsC(Rcpp::IntegerMatrix x) {
  long nrow = x.nrow(), ncol = x.ncol();
  Rcpp::IntegerVector out(nrow);
  
  for (long i = 0; i < nrow; i++) {
    for (long j = 0; j < ncol; j++) {
      out[i] += x(i, j);
    }
  }
  return(out);
}

Rcpp::NumericMatrix colSumsC2(Rcpp::NumericMatrix x) {
  long nrow = x.nrow(), ncol = x.ncol();
  Rcpp::NumericMatrix out(ncol, 2);
  for (long i = 0; i < ncol; i++) {
    for (long j = 0; j < nrow; j++) {
      out(i, 0) += x(j, i);
      if(x(j, i) != 0.0)
        out(i, 1) += 1;
    }
  }
  return(out);
}

long sample_with_p(NumericVector ubar_i, long I) {
  long ret = -1;
  double sum = 0;
  long rand_num = rand();
  double rand_unif = (rand_num % I)/float(I);
  while(sum <= rand_unif) {
    sum += ubar_i[++ret];
  }
  return(ret);
}

Rcpp::NumericVector colMeansWithout0(Rcpp::NumericMatrix u) {
  Rcpp::NumericVector col_means(u.ncol());
  Rcpp::NumericMatrix col_sums = colSumsC2(u);
  for(long i = 0; i < col_sums.nrow(); i++) {
    if(col_sums(i, 1) != 0) {
      col_means[i] = col_sums(i, 0)/col_sums(i, 1);
    }
    else {
      col_means[i] = 0;
    }
  }
  return(col_means);
}

double get_average_uniqueness(IntegerMatrix indM2) {
  Rcpp::NumericVector avg_uniq;
  Rcpp::IntegerVector c = rowSumsC(indM2);
  long rows = indM2.nrow(), cols = indM2.cols(), i, j;
  Rcpp::NumericMatrix u(rows, cols);
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      if(c[i] != 0) {
        u(i, j) = indM2(i, j)/float(c[i]);
      }
      else {
        u(i, j) = 0; // Just to be careful
      }
    }
  }
  avg_uniq = colMeansWithout0(u);
  double avg_uniq1 = avg_uniq[avg_uniq.length() - 1];
  return(avg_uniq1);
}

Rcpp::NumericVector get_prob_from_avg_uniq(Rcpp::NumericVector avg_uniq) {
  long len = avg_uniq.length();
  Rcpp::NumericVector prob(len);
  double sum = 0;
  for(long i = 0; i < len; i++) {
    sum += avg_uniq[i];
  }
  for(long i = 0; i < len; i++) {
    if(sum != 0) {
      prob[i] = avg_uniq[i]/sum;
    }
    else {
      prob[i] = 0;
    }
  }
  return(prob);
}


// [[Rcpp::export]]
Rcpp::IntegerVector seqBoot_index(Rcpp::IntegerMatrix indM, long sLen = -1, long seed = -1) {
  if(seed != -1) {
    srand(seed);
  }
  long I = indM.ncol(), i, j, rows = indM.nrow();
  if(sLen == -1) {
    sLen = I;
  }
  Rcpp::NumericVector avg_uniq(I), prob(I);
  Rcpp::IntegerMatrix indM2(rows, sLen + 1);
  long len = 0;
  Rcpp::IntegerVector y(sLen, -1);
  while(len < sLen) {
    for(i = 0; i < I; i++) {
      for(j = 0; j < rows; j++) {
        indM2(j, sLen) = indM(j, i);
      }
      avg_uniq[i] = get_average_uniqueness(indM2);
    }
    prob = get_prob_from_avg_uniq(avg_uniq);
    y[len] = sample_with_p(prob, I);
    for(j = 0; j < rows; j++) {
      indM2(j, len) = indM(j, y[len]);
    }
    len++;
  }
  return(y);
}
