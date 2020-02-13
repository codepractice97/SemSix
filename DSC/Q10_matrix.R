r1=as.integer(readline("Enter the size of row"))
c1=as.integer(readline("Enter the size of the column"))
print("Enter the elements of first matrix")
M1=matrix(,r1,c1,byrow=TRUE)
for(i in 1:r1){
  for(j in 1:c1)
  {
    M1[i,j]=as.integer(readline("Enter the element"))
  }
}
print("Enter the elements of the second matrix")
M2=matrix(,r1,c1,byrow = TRUE)
for(i in 1:r1){
  for(j in 1:c1){
    M2[i,j]=as.integer(readline("Enter the element"))
  }
}
M3=matrix(,r1,c1,byrow = TRUE)
M4=matrix(,r1,c1,byrow = TRUE)
M5=matrix(,r1,c1,byrow=TRUE)
M3=M1+M2
M4=M1-M2
M5=M1*M2
print("The resultant matrix after addition is")
print(M3)
print("The resultant matrix after subtrcation is")
print(M4)
print("The resultant matrix after multiplication is")
print(M5)