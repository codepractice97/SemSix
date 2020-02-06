fibonacci:-
	write('Enter the number of terms'),
	read(N),
	check(N).
check(1):-
	write('0'),!.
check(2):-
	write('0 1'),!.
check(N):-
	check(2),	
	fibo(0,1,N).
fibo(X,Y,N):-
	N=<2,
	write(' '),!.
fibo(X,Y,N):-
	T is X+Y,
	write(' '),
	write(T),
	N1 is N-1,
	fibo(Y,T,N1).

