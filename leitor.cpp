#include "leitor.h"



Leitor::Leitor()
{
}

void Leitor::setCaminho(string caminho)
{
    this->caminho = caminho;
}

vector<string> Leitor::lerArquivoCandidatos()
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
    }catch(std::ios_base::failure const&){
        cerr << "Erro ao abrir o arquivo" << endl;
    }
    
    return linhas;
}

vector<string> Leitor::lerArquivoVotos()
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
    }catch(std::ios_base::failure const&){
        cerr << "Erro ao abrir o arquivo" << endl;
    }
    
    return linhas;
}