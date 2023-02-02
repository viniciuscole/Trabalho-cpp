#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>

#include "partido.h"

using namespace std;


class Candidato
{
    int tipoCandidato;
    int situacao;
    int numeroCandidato;
    string nome;
    int numeroFederacao;
    string dataNascimento;
    int situacaoEleito;
    int genero;
    int votos=0;
    Partido* partido;
    int ehCandidatoLegenda;
    
    public: 
    
    Candidato(int tipoCandidato, int situacao, int numeroCandidato, string nome, int numeroFederacao,
              string dataNascimento, int situacaoEleito, int genero, int ehCandidatoLegenda);
    int getTipoCandidato();
    int getSituacao();
    int getNumeroCandidato();
    string getNome();
    int getNumeroFederacao();
    string getDataNascimento();
    int getSituacaoEleito();
    int getGenero();
    int getVotos();
    int getEhCandidatoLegenda();
    Partido* getPartido();
    void setPartido(Partido* partido);
    void addVotos(int votos);
    string toString();

};

#endif // CANDIDATO_H