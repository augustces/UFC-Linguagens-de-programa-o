n_esimo(1,[Y|_],Y).
n_esimo(N,[_|L],X):-Z is N-1, n_esimo(Z,L,X).