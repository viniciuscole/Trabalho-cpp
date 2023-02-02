#include "leitor.h"

Leitor::Leitor(string caminho)
{
    this->caminho = caminho;
}

void Leitor::setCaminho(string caminho)
{
    this->caminho = caminho;
}

vector<string> Leitor::ler()
{
    ifstream entrada;
    locale loc = locale("pt_BR.ISO8859-1");
    entrada.imbue(loc);
    entrada.exceptions(ifstream::badbit);
    vector<string> linhas;
    try{
        entrada.open(this->caminho);
        string linha;
        while(getline(entrada, linha)){
            linhas.push_back(linha);
        }
        entrada.close();
    }catch(ifstream::failure e){
        cerr << "Erro ao abrir o arquivo" << endl;
    }
    
    return linhas;
}
