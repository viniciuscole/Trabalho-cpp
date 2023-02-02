#ifndef LEITOR_H
#define LEITOR_H

#include <string>
#include <locale>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Leitor
{   
    string caminho;
    locale loc;
    public:
        Leitor();
        void setCaminho(string caminho);
        vector<string> lerArquivoCandidatos();
        vector<string> lerArquivoVotos();
    
};

#endif