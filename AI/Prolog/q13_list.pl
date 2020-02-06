list:-
	write('Enter list to check if palindrome: '),
	read(L),
	reverse(L,R),
	check(L,R),!.
	check([],[]):-
		write('List is a palindrome'),!.
	check([H1|T1],[H1|T2]):-
		check(T1,T2).
	check([H1|_],[H2|_]):-
		write('List is not a palindrome'),!.
