#include <string>
#include <ctime>

#include "candidato.h"

using namespace std;

Candidato::Candidato(int tipoCandidato, int situacao, int numeroCandidato, string nome, int numeroFederacao, time_t dataNascimento, int situacaoEleito, int genero){

    this->tipoCandidato = tipoCandidato;
    this->situacao = situacao;
    this->numeroCandidato = numeroCandidato;
    this->nome = nome;
    this->numeroFederacao = numeroFederacao;
    this->dataNascimento = dataNascimento;
    this->situacaoEleito = situacaoEleito;
    this->genero = genero;
};
int Candidato::getTipoCandidato()
{
    return this->tipoCandidato;
}
int Candidato::getSituacao()
{
    return this->situacao;
}
int Candidato::getNumeroCandidato()
{
    return this->numeroCandidato;
}
string Candidato::getNome()
{
    return this->nome;
}
int Candidato::getNumeroFederacao()
{
    return this->numeroFederacao;
}
time_t Candidato::getDataNascimento()
{
    return this->dataNascimento;
}
int Candidato::getSituacaoEleito()
{
    return this->situacaoEleito;
}
int Candidato::getGenero()
{
    return this->genero;
}
int Candidato::getVotos()
{
    return this->votos;
}
Partido* Candidato::Candidato::getPartido()
{
    return this->partido;
}
void Candidato::setPartido(Partido* partido)
{
    this->partido = partido;
}
void Candidato::addVotos(int votos)
{
    this->votos += votos;
}

string Candidato::toString()
{
    return       std::string("Candidato [tipoCandidato=") + std::to_string(tipoCandidato) + ", situacao=" + std::to_string(situacao) + ", numeroCandidato="
                + std::to_string(numeroCandidato) + ", nome="
                + nome + ", numeroFederacao="
                + std::to_string(numeroFederacao) + ", dataNascimento=" + std::to_string(dataNascimento) + ", situacaoEleito=" + std::to_string(situacaoEleito)
                + ", genero=" + std::to_string(genero) + ", votos=" + std::to_string(votos) + "]";
}
