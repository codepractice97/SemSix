factorial:-
	write('Enter the number'),
	read(X),
	fact(X,Z),
	write(Z).
fact(0,R):-
	R is 1.
fact(X,R):-
	F is X-1,
	fact(F,R1),
	R is X*R1.

