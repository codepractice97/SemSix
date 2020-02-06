list:-
	write('Enter two lists to concat: '),
	read(L1),
	read(L2),
	write('Concated list: '),
	conc(L1,L2,L3),
	write(L3),!.
	conc([],L,L).
	conc([X|L1],L2,[X|L3]):-
		conc(L1,L2,L3).
