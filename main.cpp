#include <iostream>
#include <locale>
#include <string>

#include "leitor.h"
#include "processamento.h"

using namespace std;

int main(int argc, char const *argv[]){
    locale Brloc("pt_BR.UTF-8");
    cin.imbue(Brloc);
    
    if(argc !=5){
        cout << "Erro: Numero de argumentos invalido" << endl;
        return 1;
    }

    string opcao = argv[1];
    string arquivoCandidatos = argv[2];
    string arquivoVotos = argv[3];
    string data = argv[4];

    int tipo;
    if(opcao== "--federal") tipo = 0;
    else if(opcao == "--estadual") tipo = 1;
    else{
        cout << "Erro: Opcao invalida" << endl;
        return 1;
    }



    Leitor leitor;
    leitor.setCaminho(arquivoCandidatos);
    vector<string> linhasCandidatos = leitor.lerArquivoCandidatos();
    leitor.setCaminho(arquivoVotos);
    vector<string> linhasVotos = leitor.lerArquivoVotos();

    Processamento* processamento = new Processamento(linhasCandidatos, linhasVotos, tipo);
    processamento->processar(tipo);
    processamento->gerarRelatorios(data, tipo);
    delete processamento;
    
    cin.imbue(locale::classic());

    return 0;
}