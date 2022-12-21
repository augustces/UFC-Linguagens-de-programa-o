#include "livro.hpp"

//auxiliar
int pegaMaior(std::vector<Livro*> livros){
    int maiorId = livros.front()->getId();
    for(Livro* livro : livros){
        if(livro->getId() > maiorId)
            maiorId = livro->getId();
    }
    return maiorId;
}

// implementação do Livro
Livro::Livro(std::string nome, float valor, std::string genero, int id, int qtdEstoque){
    this->nome = nome;
    this->valor = valor;
    this->genero = genero;
    if (genero == "Aventura") {
        this->descricao = "Com ilustracoes";
    }
    else if (genero == "Comedia") {
        this->descricao = "Com capa do tipo brochura";
    }
    else {
        this->descricao = "Com capa dura";
    }
    this->identificador = id;
    this->qtdEstoque = qtdEstoque;
};

Livro::~Livro(){};

//gets
std::string Livro::getNome(){
    return this->nome;
};

float Livro::getValor(){
    return this->valor;
};

int Livro::getId(){
    return this->identificador;
};

std::string Livro::getGenero(){
    return this->genero;
};

std::string Livro::getDescricao(){
    return this->descricao;
};

int Livro::getQtdEstoque(){
    return this->qtdEstoque;
};

void Livro::addQtdEstoque(int quantidade){
    this->qtdEstoque += quantidade;
};

void Livro::remQtdEstoque(){
    this->qtdEstoque -= 1;
};

std::ostream& operator<<(std::ostream& os, Livro* livro) {
    os << "Identificador: " << livro->getId() << '\n';
    os << "Nome: " << livro->getNome() << '\n';
    os << "Valor: " << std::setprecision(2) << std::fixed << livro->getValor() << '\n';
    os << "Genero: " << livro->genero << "   Descricao: " << livro->descricao << '\n';
    os << "Quantidade em estoque: "  << livro->qtdEstoque << '\n';
    return os;
};

// implementação do Controle
Livro* Controle::pesquisa(std::string nome, std::string genero){
    for(Livro* livro : this->livros){
        if (livro->getNome() == nome && livro->getGenero() == genero) {
            return livro;
        }
    }
    return nullptr;
};

Livro* Controle::pesquisaPorId(int id){
    for(Livro* livro : this->livros) {
    if (livro->getId() == id) {
        return livro;
    }
    }
    throw std::runtime_error("Livro nao esta no estoque!");
};

void Controle::setCaixa(float valor){
    this->caixa = valor;
};

Controle::Controle(){
    std::cout << "Digite o valor inicial do caixa: \n";
    float valor;
    std::cin >> valor;
    this->setCaixa(valor);
};

void Controle::venderLivro(Livro* livro, float valor){
    if (valor < livro->getValor()){
        throw std::runtime_error("Dinheiro insuficiente para a compra!");
    }
    if (livro == nullptr) {
        throw std::runtime_error("Livro indisponivel!");
    }
    else{
        if (livro->getValor() < valor){
            std::cout << "Troco: " << valor - livro->getValor() << '\n';
            this->caixa -= valor - livro->getValor();
        }
        this->caixa += valor;
        this->vendas.push_back(livro);
        this->estoque -= 1;
        livro->remQtdEstoque();
        if( livro->getQtdEstoque() < 1){
            std::vector<Livro*> copia;
            for(Livro* liv : this->livros){
                if(livro->getId() != liv->getId()) {
                    copia.push_back(liv);
                }
            }
            this->livros = copia;
        }            
        std::cout << "Livro vendido!\n";
        
    }
};

void Controle::ComprarLivro(std::string nome, float valor, std::string genero, int quantidade){
    if((valor * quantidade) > this->caixa){
        throw std::runtime_error("Dinheiro no caixa insuficiente, valor que falta : \n" + std::to_string((valor*quantidade) - this->caixa));
    }  
    this->estoque += quantidade;
    this->caixa -= valor * quantidade;
    if (this->livros.empty()){
        Livro* livro1 = new Livro(nome, valor + 0.2*valor, genero, 1, quantidade);
        this->livros.push_back(livro1);
        throw std::runtime_error("Primeiro livro comprado!\n");
    }

    Livro* livro = this->pesquisa(nome, genero);
    if (livro == nullptr) {
        Livro* livro2 = new Livro(nome, valor + 0.2*valor, genero, pegaMaior(this->livros) + 1, quantidade);
        this->livros.push_back(livro2);
    }
    else{
        livro->addQtdEstoque(quantidade);
    }
    std::cout << "Livro Comprado!\n";
};

std::ostream& operator<<(std::ostream& os, Controle* controle) {
    os << "Sistema de livraria\n";
    os << "Dinheiro no caixa: " << std::setprecision(2) << std::fixed << controle->caixa << "\n";
    os << "Quantidade de livros em estoque: " << controle->estoque << '\n';
    os << "Quantidade de vendas: " << controle->vendas.size() << '\n';
    return os;
};

Controle::~Controle(){
    for (Livro* i : this->vendas){
        delete i;
    }
    this->vendas.clear();

    for (Livro* livro : this->livros){
        delete livro;
    }
    this->livros.clear();
};

void Controle::printEstoque(){
    if (this->livros.empty()){
        throw std::runtime_error("Nao existem livros!\n");
    }
    int i {1};
    for(Livro* livro : this->livros){
        std::cout << "Livro " << i << "\n";
        std::cout << livro;
        i++;
    }
    std::cout << '\n';
};

void Controle::printVendas(){
    if (this->vendas.empty()){
        throw std::runtime_error("Nao existem vendas!\n");
    }
    for(int it{0}; it < (int) this->vendas.size(); it++){
        std::cout << "Venda " << it << '\n';
        std::cout << vendas[it];
    }

    std::cout << '\n';
};

void Controle::deposito(float valor){
    this->caixa += valor;
    std::cout << "Deposito realizado!\n";
};

void Controle::saque(float valor){
    if(this->caixa < valor){
        throw std::runtime_error("Dinheiro no caixa é insuficiente!\n");
    }
    this->caixa -= valor;
    std::cout << "Saque realizado!\n";
};

// loop
int main () {
    Controle* controle = new Controle();

    while(true){
        try{
            std::cout << "****MENU****\n";
            std::cout << "Instrucao: Digite uma letra para escolher uma funcao.\n";
            std::cout << "AVISO 1: Usa-se o dinheiro do caixa para comprar livros.\n";
            std::cout << "AVISO 2: O preco de um livro equivale a 20 porcento a mais do valor na sua compra.\n";
            std::cout << "a) Informacoes sobre o sistema (numero de livros e vendas, e quantia no caixa).\n";
            std::cout << "b) Ver estoque de livros.\n";
            std::cout << "c) Ver vendas.\n";
            std::cout << "d) Comprar livro.\n";
            std::cout << "e) Vender livro.\n";
            std::cout << "f) Depositar dinheiro no caixa.\n";
            std::cout << "g) Sacar dinheiro do caixa.\n";
            std::cout << "h) Sair do sistema.\n";
            char opcao{};
            std::cin >> opcao;
            if(opcao == 'a') {
                std::cout << controle;
            }
            else if (opcao == 'b'){
                controle->printEstoque();
            }
            else if (opcao == 'c'){
                controle->printVendas();
            }
            else if (opcao == 'd'){
                std::string genero {""}, nome{""};
                char letra;
                float valor{0};
                std::cout << "Escolha qual genero do livro: \n";
                std::cout << "a) Aventura - contem ilustracoes\n";
                std::cout << "b) Drama - com capa dura\n";
                std::cout << "c) Comedia - capa do tipo brochura\n";
                std::cin >> letra;
                switch (letra)
                {
                case 'a':
                    genero = "Aventura";
                    break;
                case 'b':
                    genero = "Drama";
                    break;
                case 'c':
                    genero = "Comedia";
                    break;
                default:
                    throw std::runtime_error("Escolha um dos generos indicados!\n");
                    break;
                }
                std::cout << "Digite o preco do livro que voce deseja comprar: \n";
                std::cin >> valor;
                std::cout << "Digite o nome do livro que voce deseja comprar: \n";
                std::cin.ignore();
                getline(std::cin, nome);
                int qtd{0};
                std::cout << "Digite a quantidade de livros que voce deseja comprar: \n";
                std::cin >> qtd;
                controle->ComprarLivro(nome, valor, genero, qtd);
            }
            else if(opcao == 'e'){
                int id{0};
                float valor{0};
                std::cout << "Escolha o identificador do livro que voce deseja vender: \n";
                controle->printEstoque();
                std::cin >> id;
                Livro* livro = controle->pesquisaPorId(id);
                std::cout << "Digite o valor dado para comprar o livro: \n";
                std::cin >> valor;
                controle->venderLivro(livro,valor);
            }
            else if (opcao == 'f'){
                std::cout << "Digite o valor para depositar: \n";
                float valor;
                std::cin >> valor;
                controle->deposito(valor);
            }
            else if(opcao == 'g'){
                std::cout << "Digite o valor para sacar: \n";
                float valor;
                std::cin >> valor;
                controle->saque(valor);
            }
            else if(opcao == 'h'){
                break;
            }
            else{
                throw std::runtime_error("Digite uma letra valida!\n");
            }

            std::cout << "\n";
        }
        catch(std::runtime_error(erro)){
            std::cout << erro.what() << '\n';
        }
    }
    delete controle;
    return 0;
}