#include "partido.h"
#include "candidato.h"



Partido::Partido(string sigla, int numero)
{
    this->sigla = sigla;
    this->numero = numero;
}

list<Candidato*> Partido::getCandidatos()
{
    return this->candidatos;
}

string Partido::getSigla()
{
    return this->sigla;
}

int Partido::getNumero()
{
    return this->numero;
}

int Partido::getVotosLegenda()
{
    return this->votosLegenda;
}

int Partido::getVotosNominais()
{
   int votos=0;

   for (Candidato* candidato : candidatos)
   {
       votos += candidato->getVotos();
   }

   return votos;
}

int Partido::getVotosTotais()
{
   return votosLegenda + getVotosNominais();
}

void Partido::addVotosLegenda(int votosLegenda)
{
    this->votosLegenda += votosLegenda;
}

void Partido::addCandidato(Candidato* candidato)
{
    candidatos.push_back(candidato);
}
