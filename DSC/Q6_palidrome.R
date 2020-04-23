checkPalindrome <- function(str){
  f = 0
  for(i in 1:(nchar(str)/2 +1)) {
    if(substr(str,i,i)!=substr(str,(nchar(str)+1)-i,(nchar(str)+1)-i)) {
      f=1
      break
    }
  }
  if(f==0)
    "Palindrome"
  else
    "Not Palindrome"
}

str = readline("enter string: ")
checkPalindrome(str)
