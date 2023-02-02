#ifndef RELATORIOS_H
#define RELATORIOS_H

#include <list>
#include <time.h>
#include <iostream>
#include <locale>

using namespace std;

#include "candidato.h"
#include "partido.h"

class Relatorios
{
    list<Candidato*> candidatosOrdenados;
    list<Partido*> partidosOrdenados;
    list<Candidato*> candidatosEleitosOrdenados;
    int tipoDeEleicao;
    string dataDaEleicao;
    locale loc = locale("pt_BR.UTF-8");
    string transformaMaisculo(string str);
    bool checaSeCandidatoEstaNaLista(list<Candidato*> lista, Candidato* candidato);
    public:
        Relatorios(string dataDaEleicao, int tipoDeEleicao);
        void setCandidatos(list<Candidato*> candidatos);
        void setPartidos(list<Partido*> partidos);
        void setCandidatosEleitos(list<Candidato*> candidatosEleitos);
        void setLocale(locale loc);
        void gerarRelatorios();
        void gerarRelatorio1();
        void gerarRelatorio2();
        void gerarRelatorio3();
        void gerarRelatorio4();
        void gerarRelatorio5();
        void gerarRelatorio6();
        //void gerarRelatorio7();
        void gerarRelatorio8();
        void gerarRelatorio9();
        void gerarRelatorio10();
        void gerarRelatorio11();
};


#endif // RELATORIOS_H