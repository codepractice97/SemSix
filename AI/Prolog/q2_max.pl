max2:-
	write('Enter the first number'),
	read(X),
	write('Enter the second number'),
	read(Y),
	max(X,Y,Z),
	write(Z).
max(A,B,C):- 
	C is A, A>B. 
max(A,B,C):-	
	C is B, B>A.
