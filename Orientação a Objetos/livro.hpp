#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <iomanip>
#include <algorithm>

class Livro{
    std::string nome{""};
    //aumenta 20% do valor da compra
    float valor{0};
    int qtdEstoque{0};
    int identificador{0};
    //qual tipo de livro
    std::string genero{""};
    std::string descricao{""};
    public:
    Livro(std::string nome, float valor, std::string genero, int id, int qtdEstoque);
    ~Livro();
    //gets
    std::string getNome();
    float getValor();
    int getId();
    std::string getGenero();
    std::string getDescricao();
    int getQtdEstoque();
    //adicionar no estoque
    void addQtdEstoque(int quantidade);
    //remover do estoque
    void remQtdEstoque();
    friend std::ostream& operator<<(std::ostream& os, Livro* livro);
};

class Controle{
    std::vector<Livro*> vendas;
    //id e qual livro
    std::vector<Livro*> livros;
    int estoque{0};
    float caixa{0};

    public:
    Controle();
    void venderLivro(Livro* livro, float valor);
    void ComprarLivro(std::string nome, float valor, std::string genero, int quantidade);
    Livro* pesquisa(std::string nome, std::string genero);
    Livro* pesquisaPorId(int id);
    void setCaixa(float valor);
    friend std::ostream& operator<<(std::ostream& os, Controle* controle);
    void printVendas();
    void printEstoque();
    void deposito(float valor);
    void saque(float valor);
    ~Controle();
};