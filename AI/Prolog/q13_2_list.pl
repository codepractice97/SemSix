list:-
	write('Enter list to check if palindrome: '),
	read(L),
	lastval(L,LAST),
	write(LAST),!.
	lastval([H|[]],H).
	lastval([_|T],R):-
		lastval(T,R).
