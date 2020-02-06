list:-
	write('Enter a list'),
	read(L),
	write('Enter number to check'),
	read(N),
	memb(N,L),
	write('Number in list'),!;
	write('Number not in list'),!.
	memb(N, [N|Tail]).
	memb(N, [Head|Tail]):- memb(N, Tail).
