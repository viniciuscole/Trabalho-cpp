#ifndef RELATORIOS_H
#define RELATORIOS_H

#include <list>
#include <time.h>


#include "candidato.h"
#include "partido.h"

class Relatorios
{
    list<Candidato*> candidatosOrdenados;
    list<Partido*> partidosOrdenados;
    list<Candidato*> candidatosEleitosOrdenados;
    int tipoDeEleicao;
    time_t dataDaEleicao;
    public:
        Relatorios(time_t dataDaEleicao, int tipoDeEleicao);
        //decidir se os candidatos serão parte do construtor ou se serão passados por parâmetro
};


#endif // RELATORIOS_H