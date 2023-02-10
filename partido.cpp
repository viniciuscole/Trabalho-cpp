#include "partido.h"
#include "candidato.h"

//private

vector<string> Partido::separaPalavraPorChar(string str, char delimitador) {
        vector<string> palavras;
        stringstream ss(str);
        string palavra;
        
        while(getline(ss, palavra, delimitador)) {
            palavras.push_back(palavra);
        }
        
        return palavras;
    }


    bool Partido::ehMaisVelho(string dataNascimento1, string dataNascimento2)
    {
        vector<string> data1 = separaPalavraPorChar(dataNascimento1, '/');
        vector<string> data2 = separaPalavraPorChar(dataNascimento2, '/');
        int ano1 = stoi(data1[2]);
        int ano2 = stoi(data2[2]);
        int mes1 = stoi(data1[1]);
        int mes2 = stoi(data2[1]);
        int dia1 = stoi(data1[0]);
        int dia2 = stoi(data2[0]);
        if(ano1 < ano2)
        {
            return true;
        }
        else if(ano1 > ano2)
        {
            return false;
        }
        else
        {
            if(mes1 < mes2)
            {
                return true;
            }
            else if(mes1 > mes2)
            {
                return false;
            }
            else
            {
                if(dia1 < dia2)
                {
                    return true;
                }
                else if(dia1 > dia2)
                {
                    return false;
                }
                else
                {
                    return false;
                }
            }
        }
    }

//



Partido::Partido(string sigla, int numero)
{
    this->sigla = sigla;
    this->numero = numero;
}

list<Candidato*>* Partido::getCandidatos()
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

   for (Candidato* candidato : *candidatos)
   {
       votos += candidato->getVotos();
   }

   return votos;
}

int Partido::getVotosTotais()
{
   return votosLegenda + getVotosNominais();
}

void Partido::ordenaCandidatos()
{
    candidatos->sort([this](Candidato* c1, Candidato* c2) 
        {   
            if(c1->getVotos() != c2->getVotos())
                return c2->getVotos() < c1->getVotos(); 
            else
                return ehMaisVelho(c1->getDataNascimento(), c2->getDataNascimento());
        });
}

void Partido::addVotosLegenda(int votosLegenda)
{
    this->votosLegenda += votosLegenda;
}

void Partido::addCandidato(Candidato* candidato)
{
    candidatos->push_back(candidato);
}

Partido::~Partido()
{
    delete candidatos;
}
