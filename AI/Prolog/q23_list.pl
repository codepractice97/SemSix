list:-
    write('Enter lists L1 and L2 to merge\n'),
	write('Enter list L1: '),
	read(L1),
	write('Enter list L2: '),
    read(L2),
    merge(L1,L2,L3),
    write('Merged list L3 is: '),
    write(L3).
merge([],L2,L2).
merge([X|L1],L2,[X|L3]):-
    merge(L1,L2,L3).