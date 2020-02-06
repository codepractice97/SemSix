multiply:-
	write('Enter the first number'),
	read(N1),
	write('Enter the second number'),
	read(N2),
	mult(N1,N2,R),
	write(R).
	mult(N1,N2,R):-
		R is N1*N2.
		
