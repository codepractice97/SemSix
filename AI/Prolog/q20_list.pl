list:-
    write('Enter lists L and S to check if S is a sublist of L\n'),
	write('Enter list L: '),
	read(L),
	write('Enter list S: '),
    read(S),
    sublist(S,L),
    write('S is a sublist of L');
    write('S is not a sublist of L').
sublist([X|S],[X|L]):- checkPrefix(S,L),!.
sublist(S,[_|L]):- sublist(S,L).
checkPrefix([],_).
checkPrefix([X|S],[X|L]):- checkPrefix(S,L).