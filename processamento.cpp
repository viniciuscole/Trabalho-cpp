#include "processamento.h"


//private

    vector<string> separaPalavraPorChar(string str, char delimitador) {
        vector<string> palavras;
        stringstream ss(str);
        string palavra;
        
        while(getline(ss, palavra, delimitador)) {
            palavras.push_back(palavra);
        }
        
        return palavras;
    }

//


Processamento::Processamento(vector<string> linhas)
{
    this->linhas = linhas;
}

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


void Processamento::processar(int tipoDeEleicao)
{
    switch (tipoDeEleicao)
    {
    case 1:
        processarEleicaoDeputadosEstaduais();
        break;
    case 2:
        processarEleicaoDeputadosFederais();
        break;
    default:
        break;
    }
}

void Processamento::processarEleicaoDeputadosEstaduais()
{
    
}

void Processamento::processarEleicaoDeputadosFederais()
{
}

void Processamento::gerarCandidatos()
{
    vector<string> informacoes;
    for(string linhaIso : linhas)
    {
        string linha = iso_8859_1_to_utf8(linhaIso);
        informacoes = separaPalavraPorChar(linha, ';');
        int tipoCandidato = stoi
        (informacoes[tipoCandidatoIndice].substr(1, informacoes[tipoCandidatoIndice].size() - 2));  //retira aspas
        int situacao = stoi(informacoes[situacaoIndice].substr(1, informacoes[situacaoIndice].size() - 2));
        int numeroCandidato = stoi(informacoes[numeroCandidatoIndice].substr(1, informacoes[numeroCandidatoIndice].size() - 2));
        string nome = informacoes[nomeIndice].substr(1, informacoes[nomeIndice].size() - 2);
        int numeroPartido = stoi(informacoes[numeroPartidoIndice].substr(1, informacoes[numeroPartidoIndice].size() - 2));
        string siglaPartido = informacoes[siglaPartidoIndice].substr(1, informacoes[siglaPartidoIndice].size() - 2);
        int numeroFederacao = stoi(informacoes[numeroFederacaoIndice].substr(1, informacoes[numeroFederacaoIndice].size() - 2));

        string dataNascimentoStr = informacoes[dataNascimentoIndice].substr(1, informacoes[dataNascimentoIndice].size() - 2);
        istringstream dataNascimentoStream(dataNascimentoStr);
        tm dataNascimento = {};
        dataNascimentoStream >> get_time(&dataNascimento, "%d/%m/%Y");
        if(dataNascimentoStream.fail())
        {
            cout << "Erro ao converter data de nascimento" << endl;
            exit(1);
        }
        auto dataNascimentoTime = mktime(&dataNascimento);
        int situacaoEleito = stoi(informacoes[situacaoEleitoIndice].substr(1, informacoes[situacaoEleitoIndice].size() - 2));
        int tipoVoto = stoi(informacoes[tipoVotoIndice].substr(1, informacoes[tipoVotoIndice].size() - 2));


        bool partidoJaExiste = false;
        for(const auto& partido : partidos)
        {
            if(partido.second->getNumero() == numeroPartido)
            {
                partidoJaExiste = true;
                break;
            }
        }
        if(!partidoJaExiste)
        {
            gerarPartido(numeroPartido, siglaPartido);
        }





    }
}

void Processamento::gerarPartido(int numeroPartido, string siglaPartido)
{
    Partido* partido = new Partido(siglaPartido, numeroPartido);
    partidos.insert(pair<int, Partido*>(numeroPartido, partido));
}

void Processamento::gerarVotos()
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
