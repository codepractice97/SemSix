list:-
	write('Enter list to reverse: '),
	read(L),
	rev(L,R),
	write('Reverse is: '),
	write(R),!.
	rev([],[]).
	rev([H|T],R):-
		rev(T,R1),
		append(R1,[H],R).
