s1 <- sample(1:6, 40, replace = TRUE)
s2 <- sample(1:6, 70, replace = TRUE)
s3 <- sample(1:6, 100, replace = TRUE)

t1 <- table(s1)
t2 <- table(s2)
t3 <- table(s3)

rel1 <- (t1)/length(s1)
rel2 <- (t2)/length(s2)
rel3 <- (t3)/length(s3)

df1=merge(as.data.frame(t1),as.data.frame(rel1),by.x="s1",by.y="s1")
names(df1)[1]="item"
names(df1)[2]="frequency"
names(df1)[3]="probablity"

print("sample of 40:")
print(df1)

barplot(t1, main = "BAR PLOT OF SAMPLE", xlab = "Faces of dice", ylab = "Frequency", border = "dark blue", col = gray(1-rel1))