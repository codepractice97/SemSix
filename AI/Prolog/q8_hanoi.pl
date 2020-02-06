hanoi:-
	write('Enter number of rings: '),
	read(N),
	A is 1,
	B is 2,
	C is 3,
	run_hanoi(N, A, B, C).
run_hanoi(1,A,B,C):-
	move(1,A,C),!.
run_hanoi(N,A,B,C):-
	T is N-1,
	run_hanoi(T,A,C,B),
	move(N,A,B),
	run_hanoi(T,B,A,C).
move(N,A,B):-
	write('Move disk '),
	write(N),
	write(' from '),
	write(A),
	write(' to '),
	write(B),nl.
