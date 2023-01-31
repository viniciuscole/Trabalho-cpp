#ifndef LEITOR_H
#define LEITOR_H

#include <string>
#include <locale>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include "partido.h"
#include "candidato.h"

using namespace std;
class Leitor
{   
    string caminho;
    locale loc;
    public:
        Leitor(string caminho);
        void setCaminho(string caminho);
        vector<string> ler();
    
};

#endif