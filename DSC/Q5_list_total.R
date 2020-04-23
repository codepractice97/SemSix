total <- function(l){
  res <- 0;
  for(value in l)
    res <- res+value;
  res;
}

total(list(1,32,43))
