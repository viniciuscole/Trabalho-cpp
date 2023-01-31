#ifndef PROCESSAMENTO_H
#define PROCESSAMENTO_H

#include <string>
#include <locale>
#include <map>
#include <vector>
#include <list>

#include "candidato.h"

using namespace std;

class Processamento
{
    bool compare_pt_BR(const string &s1, const string &s2);
    string iso_8859_1_to_utf8(string &str);
    map<int, Candidato*> candidatos = map<int, Candidato*>();
    map<int, Partido*> partidos = map<int, Partido*>();
    vector<string> linhas = vector<string>();
    public:
        Processamento(vector <string> linhas);
        void processar(int tipoDeEleicao);
        void processarEleicaoDeputadosEstaduais();
        void processarEleicaoDeputadosFedereais();
        map<int, Candidato*> elegeCandidatos(map<int, Candidato*> candidatos);
        list<Candidato*> ordenaCandidatosEmLista(map<int, Candidato*> candidatos);
        list<Partido*>  ordenaPartidosEmLista(map<int, Partido*> partidos);

};

#endif // PROCESSAMENTO_H