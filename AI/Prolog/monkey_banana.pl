on(floor,monkey).
on(floor,chair).
on(ceiling,banana).

in(room,monkey).
in(room,chair).
in(room,banana).

position(chair,corner). 
position(banana,center).

grasp(monkey,banana).

can_climb(monkey,chair).

can_move(monkey,chair,center).

under(X,Y):-
	% X=banana
	% Y=chair
	% Z=monkey
	in(room,X),
	in(room,Y),
	in(room,Z),
	position(X,P1),
	can_move(Z,Y,P1).

can_reach(X,Z):-
	% X=banana
	% Y=chair
	% Z=monkey
	on(floor,Z),
	on(floor,Y),
	on(ceiling,X),
	under(X,Y),
	can_climb(Z,Y).

can_get(X,Z):-
	% X=banana
	% Y=chair
	% Z=monkey
	can_reach(X,Z),
	grasp(Z,X).