x = c(rep(95.5,5),rep(105.5,8),rep(115.5,22),rep(125.5,27),rep(135.5,17),rep(145.5,9),rep(155.5,5),rep(165.5,5),rep(175.5,2))

print(x)

mean_data = mean(x)
median_data = median(x)
var_data = var(x)
sd_data = sqrt(var_data)

print(paste("mean is",mean_data))
print(paste("median is",median_data))
print(paste("variance is",var_data))
print(paste("standard deviation is",sd_data))