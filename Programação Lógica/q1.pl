primo(X,X).
primo(X, N):- N < X, A is (X mod N), A\=0, Z is N+1, primo(X, Z).

primos([X]):-primo(X,2).
primos([X|L1]):-primo(X,2), primos(L1).
