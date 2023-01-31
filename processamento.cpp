#include "processamento.h"

bool Processamento::compare_pt_BR(const string &s1, const string &s2)
{
    locale loc = locale("pt_BR.UTF-8");
    const collate<char> &col = use_facet<collate<char>>(loc);
    return (col.compare(s1.data(), s1.data() + s1.size(),
                      s2.data(), s2.data() + s2.size()) < 0);
}

string Processamento::iso_8859_1_to_utf8(string &str)
{
    string strOut;
    for (string::iterator it = str.begin(); it != str.end(); ++it)
    {
        uint8_t ch = *it;
        if (ch < 0x80)
        {
        strOut.push_back(ch);
        }
        else
        {
        strOut.push_back(0b11000000 | (ch >> 6));
        strOut.push_back(0b10000000 | (ch & 0b00111111));
        }
    }
    return strOut;
}

Processamento::Processamento(vector<string> linhas)
{
    this->linhas = linhas;
}

void Processamento::processar(int tipoDeEleicao)
{
    switch (tipoDeEleicao)
    {
    case 1:
        processarEleicaoDeputadosEstaduais();
        break;
    case 2:
        processarEleicaoDeputadosFedereais();
        break;
    default:
        break;
    }
}

void Processamento::processarEleicaoDeputadosEstaduais()
{

}

void Processamento::processarEleicaoDeputadosFedereais()
{
}

map<int, Candidato*> Processamento::elegeCandidatos(map<int, Candidato*> candidatos)
{
    map<int, Candidato*> candidatosEleitos = map<int, Candidato*>();
    for(const auto& candidato : candidatos)
    {
        if(candidato.second->getSituacaoEleito() == 2)
        {
            candidatosEleitos.insert(pair<int, Candidato*>(candidato.first, candidato.second));
        }
    }

}

list<Candidato*> Processamento::ordenaCandidatosEmLista(map<int, Candidato*> candidatos)
{
    list<Candidato*> candidatosOrdenados = list<Candidato*>();
    for(const auto& candidato : candidatos)
    {
        candidatosOrdenados.push_back(candidato.second);
    }
    candidatosOrdenados.sort([](Candidato* c1, Candidato* c2) 
        {   
            if(c1->getVotos() != c2->getVotos())
                return c2->getVotos() - c1->getVotos(); 
            else
                return (int)(difftime(c2->getDataNascimento(), c1->getDataNascimento()));
        });

    return candidatosOrdenados;
}

list<Partido *> Processamento::ordenaPartidosEmLista(map<int, Partido *> partidos)
{
    list <Partido *> partidosOrdenados = list<Partido *>();
    for(const auto& partido : partidos)
    {
        partidosOrdenados.push_back(partido.second);
    }

    partidosOrdenados.sort([](Partido* p1, Partido* p2) 
        {   
            if(p1->getVotosTotais() != p2->getVotosTotais())
                return p2->getVotosTotais() - p1->getVotosTotais(); 
            else
                return p1->getNumero() - p2->getNumero();
        });

    return partidosOrdenados;
}
