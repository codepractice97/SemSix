noun([cat|X],X).
noun([dog|X],X).
noun([mouse|X],X).
verb([ate|X],X).
verb([chases|X],X).
verb([jumped|X],X).
adjective([big|X],X).
adjective([brown|X],X).
adjective([lazy|X],X).
adjective([quick|X],X).
article([a|X],X).
preposition([at|X],X).
preposition([in|X],X).
determiner([the|X],X):-!.

nounphrase(NP,X):- determiner(NP,R), nounphrase(R,X).
nounphrase(NP,X):- adjective(NP,R), nounphrase(R,X).
nounphrase(NP,X):- article(NP,R), noun(R,X).
nounphrase(NP,X):- article(NP,R1), adjective(R1,R2), noun(R2,X).
nounphrase(NP,X):- noun(NP,X).

verbphrase(VP,X):- verb(VP,R), preposition(R,X).
verbphrase(VP,X):- verb(VP,R), nounphrase(R,X).
verbphrase(VP,R):- verb(VP,R).

sentence(I,O):-
    nounphrase(I,R), verbphrase(R,O).

checkSentence(L):- sentence(L,[]).

grammar:-
	write('Use following words to form a sentence: "dog,cat,mouse,ate,chases,jumped,big,brown,lazy,quick,a,the,at,in"\n'),
	write('Enter sentence in list form: '),
	read(L),
	checkSentence(L),
	write('Valid Sentence'),!;
	write('Invalid Sentence'),!.