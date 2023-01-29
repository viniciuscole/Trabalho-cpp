#include <string>
#include <ctime>

#include "candidato.h"

Candidato(int tipoCandidato, int situacao, int numeroCandidato, string nome, int numeroFederacao, time_t dataNascimento, int situacaoEleito, int genero){

    this->tipoCandidato = tipoCandidato;
    this->situacao = situacao;
    this->numeroCandidato = numeroCandidato;
    this->nome = nome;
    this->numeroFederacao = numeroFederacao;
    this->dataNascimento = dataNascimento;
    this->situacaoEleito = situacaoEleito;
    this->genero = genero;
};
int getTipoCandidato();
int getSituacao();
int getNumeroCandidato();
string getNome();
int getNumeroFederacao();
time_t getDataNascimento();
int getSituacaoEleito();
int getGenero();
int getVotos();
Partido getPartido();
void setPartido(Partido partido);
void addVotos(int votos);
string toString();