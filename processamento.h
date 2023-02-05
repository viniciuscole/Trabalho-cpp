#ifndef PROCESSAMENTO_H
#define PROCESSAMENTO_H

#include <string>
#include <locale>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <chrono>

class Candidato;
class Partido;

#define tipoCandidatoIndice 13
#define situacaoIndice 68
#define numeroCandidatoIndice 16
#define nomeIndice 18
#define numeroPartidoIndice 27
#define siglaPartidoIndice 28
#define numeroFederacaoIndice 30
#define dataNascimentoIndice 42
#define situacaoEleitoIndice 56
#define generoIndice 45
#define tipoVotoIndice 67

#define cargoIndice 17
#define numeroVotadoIndice 19
#define qtdVotosIndice 21

using namespace std;

class Processamento
{
    bool compare_pt_BR(const string &s1, const string &s2);
    string iso_8859_1_to_utf8(string &str);
    map<int, Candidato*> candidatos = map<int, Candidato*>();
    map<int, Partido*> partidos = map<int, Partido*>();
    int tipoDeEleicao = -1;
    vector<string> linhasArquivoCandidatos = vector<string>();
    vector<string> linhasArquivoVotos = vector<string>();
    vector<string> separaPalavraPorChar(string str, char delimitador);
    bool ehMaisVelho(string dataNascimento1, string dataNascimento2);
    
    public:
        Processamento(vector <string> linhasArquivoCandidatos, vector<string> linhasArquivoVotos, int tipoDeEleicao);
        void processar(int tipoDeEleicao);
        void gerarRelatorios(string dataDaEleicao, int tipoDeEleicao);
        void gerarCandidatos();
        void gerarPartido(int numeroPartido, string siglaPartido);
        void gerarVotos();
        void deletarCandidatos();
        void deletarPartidos();
        map<int, Candidato*> elegeCandidatos(map<int, Candidato*> candidatos);
        list<Candidato*> ordenaCandidatosEmLista(map<int, Candidato*> candidatos);
        list<Partido*>  ordenaPartidosEmLista(map<int, Partido*> partidos);

};

#endif // PROCESSAMENTO_H