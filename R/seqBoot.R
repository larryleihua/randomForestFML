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
    # u_ti <- indMat[prev_rowSums!=0,]/prev_rowSums[prev_rowSums!=0]
    u_ti <- indMat / (1 + prev_rowSums)
    ubar_i <- apply(u_ti,2,sum) / apply(indMat,2,sum)
    
    # sample the next one based on updated average uniqueness
    sampl <- sample(1:I, 1, prob = ubar_i / sum(ubar_i))
    phi <- c(phi, sampl)
    prev_rowSums <- prev_rowSums + indMat[, sampl]
  }
  return(phi)
}

get_indM <- function(t1_Fea, t1) {
  I <- length(t1_Fea) # number of features bars
  if(I!=length(t1)){stop("Error! The number of features bars should be the same as the number of t1")}
  t1_max <- max(t1) # this should be the same as the total number of bars
  indMat <- matrix(0, t1_max, I)# indicator matrix 1_{t,i}
  for(i in 1:I)
  {
    indMat[(t1_Fea[i]+1):t1[i],i] <- 1
  }
}