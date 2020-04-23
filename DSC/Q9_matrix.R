matrixAdd <- function(m1, m2){
  if(nrow(m1) != nrow(m2) && ncol(m1) != ncol(m2))
    return("Dimensions do not match")
  m3 <- matrix(,nrow = nrow(m1), ncol = ncol(m1))
  for (i in 1:nrow(m1)) {
    for (j in 1:ncol(m1)) {
      m3[i,j] <- m1[i,j] + m2[i,j]
    }
  }
  return(m3)
}

matrixSub <- function(m1, m2){
  if(nrow(m1) != nrow(m2) && ncol(m1) != ncol(m2))
    return("Dimensions do not match")
  m3 <- matrix(,nrow = nrow(m1), ncol = ncol(m1))
  for (i in 1:nrow(m1)) {
    for (j in 1:ncol(m1)) {
      m3[i,j] <- m1[i,j] - m2[i,j]
    }
  }
  return(m3)
}

matrixMul <- function(m1, m2){
  if(ncol(m1) != nrow(m2))
    return("Dimensions do not match")
  m3 <- matrix(0, nrow = nrow(m1), ncol = ncol(m2))
  for (i in 1:nrow(m1)) {
    for (j in 1:ncol(m2)) {
      for (k in 1:nrow(m2))
        m3[i,j] <- m3[i,j] + m1[i,k] * m2[k,j]
    }
  }
  return(m3)
}



m1 <- matrix(c(1:9), nrow = 3, ncol = 3, byrow = TRUE)
m2 <- matrix(c(1:9), nrow = 3, ncol = 3, byrow = TRUE)

m3 <- matrix(c(1:8), nrow = 4, ncol = 2, byrow = TRUE)
m4 <- matrix(c(1:8), nrow = 2, ncol = 4, byrow = TRUE)

matrixAdd(m1,m2)
matrixSub(m1,m2)
matrixMul(m3,m4)
