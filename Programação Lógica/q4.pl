pertence(X,[X|_]).
pertence(X,[Y|L]):-pertence(X,L).

elimina_repetidos([],[]).
elimina_repetidos([X|L1],L2):- pertence(X,L1), elimina_repetidos(L1,L2).
elimina_repetidos([X|L1],[X|L2]):- \+pertence(X,L1), elimina_repetidos(L1,L2).