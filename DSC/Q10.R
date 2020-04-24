getMode <- function(x){
  uniqVal = unique(x)
  uniqVal[which.max(tabulate(match(x,uniqVal)))]
}

x = c(rep(20,5), rep(21,3), rep(22,4), rep(23,3))

cat("Data: ", x)

part1 = median(x[x<22])
part2 = median(x)
part3 = mean(x)
part4 = getMode(x)

x = append(x,c(23,23))
cat("New Data: ",x)

part5_1 = median(x)
part5_2 = mean(x)
part5_3 = getMode(x)

print(paste("median of less than 22 is",part1))
print(paste("median of all is",part2))
print(paste("mean of all is",part3))
print(paste("mode of all is",part4))
print(paste("mean,median,mode of of new data are",part5_1,part5_2,part5_3))