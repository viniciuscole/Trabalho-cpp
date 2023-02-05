#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include <list>
#include <vector>
#include <sstream>

class Candidato;

using namespace std;

class Partido
{
    list<Candidato*> candidatos = list<Candidato*>();
    string sigla;
    int numero;
    int votosLegenda = 0;
    vector<string> separaPalavraPorChar(string str, char delimitador);
    bool ehMaisVelho(string dataNascimento1, string dataNascimento2);

    public:
    
    Partido(string sigla, int numero);
    list<Candidato*> getCandidatos();
    string getSigla();
    int getNumero();
    int getVotosLegenda();
    int getVotosNominais();
    int getVotosTotais();
    void ordenaCandidatos();
    void addVotosLegenda(int votosLegenda);
    void addCandidato(Candidato* candidato);
};

#endif //PARTIDO_H