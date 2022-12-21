%tamanho([],0).
%tamanho([Y|L], Z):-tamanho(L,X), Z is X+1.

se(2,2,[2]).
se(2,Z,[N|L2]):-se(2,N,L), Z is N-1
se(2,N,L):-seq(N,L).
insere(B,L,[B|L]).