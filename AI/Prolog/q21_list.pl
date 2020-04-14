list:-
	write('Enter list L: '),
	read(L),
	write('Enter position to delete: '),
    read(N),
    delete_nth(N,L,R),
    write('List L after deletion: '),
    write(R).
delete_nth(_,[],[]).
delete_nth(0,[_|L],L).
delete_nth(N,[X|L],[X|R]):-
    N1 is N-1,
    delete_nth(N1,L,R).