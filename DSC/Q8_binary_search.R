bsearch <- function(L, ele, left, right){
  if (left <= right){
    m <- as.integer(( left + right ) / 2)
    if (ele == L[m])
      return(m)
    else if (ele < L[m])
      return(bsearch(L, ele, left, m-1))
    else
      return(bsearch(L, ele, m+1, right))
  } else
    return(-1)
}

bsearch(list(1,2,43,45,67,87,88),43,1,7)