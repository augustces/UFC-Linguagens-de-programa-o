% fatos
sexo(gabi,feminino).
sexo(leila,feminino).
sexo(cleide,feminino).
sexo(conceicao,feminino).
sexo(rosa,feminino).
sexo(silvio,masculino).
sexo(augusto,masculino).
sexo(ribamar,masculino).
sexo(neto,masculino).
sexo(arthur,masculino).
mae(leila,gabi).
mae(leila,augusto).
mae(conceicao,leila).
mae(conceicao,neto).
mae(conceicao,cleide).
mae(rosa,silvio).
pai(ribamar,neto).
pai(ribamar,leila).
pai(ribamar,cleide).
pai(silvio,augusto).
pai(silvio,gabi).
pai(neto,arthur).

%auxiliar
filhe(X,Y):-(pai(Y,X));(mae(Y,X)).

%irma
irma(X,Y):- sexo(X,feminino), filhe(X,A), filhe(Y,A),
 X\==Y.

%irmao
irmao(X,Y):- sexo(X,masculino), filhe(X,A), filhe(Y,A),
 X\==Y.

%descendente
descendente(X,Y):- filhe(X,Y).
descendente(X,Y):- filhe(X,A), descendente(A,Y).

%avô
avoo(X,Y):- filhe(Y,A),
 filhe(A,X),
 sexo(X,masculino).

%avó
avoh(X,Y):- filhe(Y,A), filhe(A,X), sexo(X,feminino).

%tio
tio(X,Y):- irmao(X,A), filhe(Y,A).

%tia
tia(X,Y):- irma(X,A), filhe(Y,A).

%primo
primo(X,Y):-(irmao(A,B);irma(A,B)), filhe(X,A), filhe(Y,B),
 X\==Y, sexo(X, masculino).

%prima
prima(X,Y):-(irmao(A,B);irma(A,B)), filhe(X,A), filhe(Y,B),
 X\==Y, sexo(X, feminino).
