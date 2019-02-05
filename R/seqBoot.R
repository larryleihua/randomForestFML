#' @param indMat an indicator matrix obtained from randomForestFML::getIndMat()
#' @param sLen number of observations to be sampled (with replacement); 'sLen' should not be greater than the number of columns of 'indMat'
#' @return a vector of indices sampled
#' 
#' @examples
#' t1_Fea <- c(2,5,11)
#' t1 <- c(9,11,15)
#' indMat <- getIndMat(t1_Fea, t1)
#' seqBoot(indMat)
seqBoot <- function(indMat, sLen=NULL)
{
  ## construct indicator matrix 1_{t,i}: indMat
  I <- ncol(indMat)
  t1_max <- nrow(indMat)
  
  ## sequential bootstrap
  if(is.null(sLen)){sLen <- I}
  
  phi <- sample(1:sLen, 1) # phi: the vector used to store the sampled features bars index
  prev_rowSums <- indMat[, phi]
  while(length(phi)<sLen) # the loop for sequential bootstrap
  {
    # update average uniqueness based on phi
    u_ti <- indMat / (1 + prev_rowSums)
    ubar_i <- apply(u_ti,2,sum) / apply(indMat,2,sum)
    
    # sample the next one based on updated average uniqueness
    sampl <- sample(1:I, 1, prob = ubar_i / sum(ubar_i))
    phi <- c(phi, sampl)
    prev_rowSums <- prev_rowSums + indMat[, sampl]
  }
  return(phi)
}

#' @param t1_Fea a vector for time index (in terms of tick/volume/dollar/etc. bars) for the end of each features bars
#' @param t1 a vector for time index (in terms of tick/volume/dollar/etc. bars) that corresponds to the event (eg, hitting some barrier)
#' @examples
#' t1_Fea <- c(2,5,11)
#' t1 <- c(9,11,15)
#' getIndMat(t1_Fea, t1)
getIndMat <- function(t1_Fea, t1) {
  I <- length(t1_Fea) # number of features bars
  if(I!=length(t1)){stop("Error! The number of features bars should be the same as the number of t1")}
  t1_max <- max(t1) # this should be the same as the total number of bars
  indMat <- matrix(0, t1_max, I)# indicator matrix 1_{t,i}
  for(i in 1:I)
  {
    indMat[(t1_Fea[i]+1):t1[i],i] <- 1
  }
  return(indMat)
}
