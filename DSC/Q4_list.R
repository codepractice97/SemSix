N=as.integer(readline("Entersize of number"))
print("Enter elements")
L=list()
for(i in 1:N)
{
  L[i]=as.integer(readline())
}
max_el=as.integer(L[1])
for(i in 2:N)
{
  if(as.integer(L[i])>max_el)
    max_el=as.integer(L[i])
}
print(paste(max_el,"is largest"))