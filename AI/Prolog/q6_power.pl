pow:-
	write('Enter the number'),
	read(N),
	write('Enter the power'),
	read(P),
	call_pow(N,P,R),
	write('The result is '),
	write(R).
	call_pow(A,0,1).
	call_pow(A,B,R):-
		F is B-1,
		call_pow(A,F,R1),
		R is R1*A.
