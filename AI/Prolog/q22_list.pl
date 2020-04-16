list:-
    write('Enter a list L: '),
    read(L),
    write('Enter elemnt X to delete all occurrences of from list L: '),
    read(X),
    delete_all(X,L,R),
    write('New list: '),
    write(R).
delete_all(_,[],[]).
delete_all(X,[X|L],R):-
    delete_all(X,L,R).
delete_all(X,[E|L],[E|R]):-
    delete_all(X,L,R).