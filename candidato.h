#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
#include <ctime>
#include "partido.h"

using namespace std;


class Candidato
{
    int tipoCandidato;
    int situacao;
    int numeroCandidato;
    string nome;
    int numeroFederacao;
    time_t dataNascimento;
    int situacaoEleito;
    int genero;
    int votos=0;
    Partido* partido;
    
    public: 
    
    Candidato(int tipoCandidato, int situacao, int numeroCandidato, string nome, int numeroFederacao,
              time_t dataNascimento, int situacaoEleito, int genero);
    int getTipoCandidato();
    int getSituacao();
    int getNumeroCandidato();
    string getNome();
    int getNumeroFederacao();
    time_t getDataNascimento();
    int getSituacaoEleito();
    int getGenero();
    int getVotos();
    Partido* getPartido();
    void setPartido(Partido* partido);
    void addVotos(int votos);
    string toString();

};

#endif // CANDIDATO_H