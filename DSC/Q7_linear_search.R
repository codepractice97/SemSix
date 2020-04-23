lsearch <- function(L, ele){
  result <- -1
  for (i in 1:length(L)) {
    if ( ele == L[i]){
      result <- i
      break
    }
  }
  result
}

lsearch(list(1,23,45,3,45,423,2), 45)
