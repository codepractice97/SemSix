x=readline("enter string")
f=0;
for(i in 1:(nchar(x)/2 +1))
{
  if(substr(x,i,i)!=substr(x,(nchar(x)+1)-i,(nchar(x)+1)-i))
  {
    
    f=1
    break
  }
}
if(f==0)
{
  print("palindrome")
}