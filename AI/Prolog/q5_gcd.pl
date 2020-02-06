gcd:-
	write('Enter first number'),
	read(A),
	write('Enter second number'),
	read(B),
	calgcd(A,B,R),
	write('GCD is: '),
	write(R).

calgcd(A,A,A):-!.
calgcd(A,B,R):-
	A>B,
	T is A-B,
	calgcd(T,B,R),!.
calgcd(A,B,R):-
	A<B,
	T is B-A,
	calgcd(A,T,R).
	
