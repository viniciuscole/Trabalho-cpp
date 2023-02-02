#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include <list>

class Candidato;

using namespace std;

class Partido
{
    list<Candidato*> candidatos = list<Candidato*>();
    string sigla;
    int numero;
    int votosLegenda = 0;
    
    public:
    
    Partido(string sigla, int numero);
    list<Candidato*> getCandidatos();
    string getSigla();
    int getNumero();
    int getVotosLegenda();
    int getVotosNominais();
    int getVotosTotais();
    void addVotosLegenda(int votosLegenda);
    void addCandidato(Candidato* candidato);
};

#endif //PARTIDO_H