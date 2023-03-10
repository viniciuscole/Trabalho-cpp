#include "processamento.h"

#include "relatorios.h"
#include "candidato.h"
#include "partido.h"

//private

    vector<string> Processamento::separaPalavraPorChar(string str, char delimitador) {
        vector<string> palavras;
        stringstream ss(str);
        string palavra;
        
        while(getline(ss, palavra, delimitador)) {
            palavras.push_back(palavra);
        }
        
        return palavras;
    }


    bool Processamento::ehMaisVelho(string dataNascimento1, string dataNascimento2)
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

    void Processamento::deletarCandidatos()
    {   
        for(const auto& candidato : *candidatos)
        {   
            delete candidato.second;
        }
        delete candidatos;
    }

    void Processamento::deletarPartidos()
    {
        for(const auto& partido : *partidos)
        {
            delete partido.second;
        }
        delete partidos;
    }

//


Processamento::Processamento(vector<string> linhasArquivoCandidatos, vector<string> linhasArquivoVotos, int tipoDeEleicao)
{
    this->linhasArquivoCandidatos = linhasArquivoCandidatos;
    this->linhasArquivoVotos = linhasArquivoVotos;
    this->tipoDeEleicao = tipoDeEleicao;
}


void Processamento::processar(int tipoDeEleicao)
{
    gerarCandidatos();
    gerarVotos();
}

void Processamento::gerarRelatorios(string dataEleicao, int tipoDeEleicao)
{
    Relatorios relatorio = Relatorios(dataEleicao, tipoDeEleicao);
    relatorio.setCandidatos(ordenaCandidatosEmLista(candidatos));
    relatorio.setCandidatosEleitos(ordenaCandidatosEmLista(elegeCandidatos(candidatos)));
    relatorio.setPartidos(ordenaPartidosEmLista(partidos));
    relatorio.gerarRelatorios();
    deletarCandidatos();
    deletarPartidos();
}

void Processamento::gerarCandidatos()
{
    vector<string> informacoes;

    int i = 0;
    for(string linhaIso : linhasArquivoCandidatos)
    {   
        if(linhaIso == linhasArquivoCandidatos[0])
        {
            continue;
        }
        string linha = iso_8859_1_to_utf8(linhaIso);
        informacoes = separaPalavraPorChar(linha, ';');
        
        int tipoCandidato = stoi(informacoes[tipoCandidatoIndice].substr(1, informacoes[tipoCandidatoIndice].size() - 2));  //retira aspas
        int situacao = stoi(informacoes[situacaoIndice].substr(1, informacoes[situacaoIndice].size() - 2));
        int numeroCandidato = stoi(informacoes[numeroCandidatoIndice].substr(1, informacoes[numeroCandidatoIndice].size() - 2));
        string nome = informacoes[nomeIndice].substr(1, informacoes[nomeIndice].size() - 2);
        int numeroPartido = stoi(informacoes[numeroPartidoIndice].substr(1, informacoes[numeroPartidoIndice].size() - 2));
        string siglaPartido = informacoes[siglaPartidoIndice].substr(1, informacoes[siglaPartidoIndice].size() - 2);
        int numeroFederacao = stoi(informacoes[numeroFederacaoIndice].substr(1, informacoes[numeroFederacaoIndice].size() - 2));
        string dataNascimento = informacoes[dataNascimentoIndice].substr(1, informacoes[dataNascimentoIndice].size() - 2);
        int situacaoEleito = stoi(informacoes[situacaoEleitoIndice].substr(1, informacoes[situacaoEleitoIndice].size() - 2));
        int genero = stoi(informacoes[generoIndice].substr(1, informacoes[generoIndice].size() - 2));
        string tipoVoto = informacoes[tipoVotoIndice].substr(1, informacoes[tipoVotoIndice].size() - 2);
        


        bool partidoJaExiste = false;
        for(const auto& partido : *partidos)
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

        if(tipoVoto == "V??lido (legenda)") //candidato de voto destinado ao partido
        {
            Candidato* candidato = new Candidato(tipoCandidato, situacao, numeroCandidato, nome, numeroFederacao,
                        dataNascimento, situacaoEleito, genero, true);
            candidatos->insert(pair<int, Candidato*>(numeroCandidato, candidato));
            
            (*partidos)[numeroPartido]->addCandidato(candidato);


            candidato->setPartido((*partidos)[numeroPartido]);
            i++;
        }
        else if ((situacao==2 || situacao==16))
        {   
            switch(tipoDeEleicao)
            {   
                case -1:
                    cout << "Tipo de elei????o n??o definido" << endl;
                    break;
                case 0:
                    if(tipoCandidato==6)
                    {
                        Candidato* candidato = new Candidato(tipoCandidato, situacao, numeroCandidato, nome, numeroFederacao,
                        dataNascimento, situacaoEleito, genero, false);
                        candidatos->insert(pair<int, Candidato*>(numeroCandidato, candidato));
                        (*partidos)[numeroPartido]->addCandidato(candidato);
                        candidato->setPartido((*partidos)[numeroPartido]);
                        i++;
                    }
                    break;
                case 1:
                    if(tipoCandidato==7)
                    {
                        Candidato* candidato = new Candidato(tipoCandidato, situacao, numeroCandidato, nome, numeroFederacao,
                        dataNascimento, situacaoEleito, genero, false);
                        candidatos->insert(pair<int, Candidato*>(numeroCandidato, candidato));
                        (*partidos)[numeroPartido]->addCandidato(candidato);
                        candidato->setPartido((*partidos)[numeroPartido]);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void Processamento::gerarPartido(int numeroPartido, string siglaPartido)
{
    Partido* partido = new Partido(siglaPartido, numeroPartido);
    partidos->insert(pair<int, Partido*>(numeroPartido, partido));
}

void Processamento::gerarVotos()
{
    vector<string> informacoes;
    for(string linhaIso : linhasArquivoVotos)
    {
        //pular a primeira linha
        if(linhaIso == linhasArquivoVotos[0])
        {
            continue;
        }

        string linha = iso_8859_1_to_utf8(linhaIso);
        informacoes = separaPalavraPorChar(linha, ';');
        
        int cargo = stoi(informacoes[cargoIndice].substr(1, informacoes[cargoIndice].size() - 2));
        int numeroVotado = stoi(informacoes[numeroVotadoIndice].substr(1, informacoes[numeroVotadoIndice].size() - 2));
        int qtdVotos = stoi(informacoes[qtdVotosIndice].substr(1, informacoes[qtdVotosIndice].size() - 2));

        if((numeroVotado != 95 && numeroVotado !=96 && numeroVotado !=97 && numeroVotado !=98)) //ignora votos nulos e em branco
        {
            switch(tipoDeEleicao)
            {
                case -1:
                    cout << "Tipo de elei????o n??o definido" << endl;
                    break;
                case 0:
                    if(cargo==6)
                    {  

                        if((*partidos)[numeroVotado]!=NULL)
                        {   
                            (*partidos)[numeroVotado]->addVotosLegenda(qtdVotos);
                        }
                        else if((*candidatos)[numeroVotado]!=NULL)
                        {
                            if((*candidatos)[numeroVotado]->getEhCandidatoLegenda()==true)
                            {   
                                (*candidatos)[numeroVotado]->getPartido()->addVotosLegenda(qtdVotos);
                            }
                            else
                            {   
                                (*candidatos)[numeroVotado]->addVotos(qtdVotos);
                            }
                        }
                        else
                        {   
                            break;
                        }
                    }
                    break;
                case 1:
                    if(cargo==7)
                    {
                        if((*partidos)[numeroVotado] != NULL)
                        {
                            (*partidos)[numeroVotado]->addVotosLegenda(qtdVotos);
                        }
                        else if((*candidatos)[numeroVotado] != NULL)
                        {
                            if((*candidatos)[numeroVotado]->getEhCandidatoLegenda() == true)
                            {
                                (*candidatos)[numeroVotado]->getPartido()->addVotosLegenda(qtdVotos);
                            }
                            else
                            {
                                (*candidatos)[numeroVotado]->addVotos(qtdVotos);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }}

map<int, Candidato*>* Processamento::elegeCandidatos(map<int, Candidato*>* candidatos)
{
    for(const auto& candidato : *candidatos)
    {
        if(candidato.second==NULL)
        {
            continue;
        }
        if(candidato.second->getSituacaoEleito() == 2 || candidato.second->getSituacaoEleito() == 3)
        {
            candidatosEleitos->insert(pair<int, Candidato*>(candidato.first, candidato.second));
        }
    }
    return candidatosEleitos;
}

list<Candidato*>* Processamento::ordenaCandidatosEmLista(map<int, Candidato*>* candidatos)
{
    list<Candidato*> *candidatosOrdenados = new list<Candidato*>();
    for(const auto& candidato : *candidatos)
    {   
        if(candidato.second!=NULL)
        candidatosOrdenados->push_back(candidato.second);
    }
    candidatosOrdenados->sort([this](Candidato* c1, Candidato* c2) 
        {   
            if(c1->getVotos() != c2->getVotos())
                return c2->getVotos() < c1->getVotos(); 
            else
                return ehMaisVelho(c2->getDataNascimento(), c1->getDataNascimento());
        });

    return candidatosOrdenados;
}

list<Partido *>* Processamento::ordenaPartidosEmLista(map<int, Partido *>* partidos)
{
    list <Partido *>* partidosOrdenados = new list<Partido *>();
    for(const auto& partido : *partidos)
    {
        partidosOrdenados->push_back(partido.second);
    }
    partidosOrdenados->sort([](Partido* p1, Partido* p2) 
        {
            if(p1!=NULL && p2!=NULL)
            {
                if(p1->getVotosTotais() != p2->getVotosTotais())
                {
                    return p2->getVotosTotais() < p1->getVotosTotais(); 
                }
                else if(p1->getNumero() != p2->getNumero())
                    return p1->getNumero() < p2->getNumero();
                else
                    return false;
            }

            else
            {
                return false;
            }
        });

        for(Partido* partido : *partidosOrdenados)
        {   
            if(partido==NULL)
            {
                continue;
            }
            partido->ordenaCandidatos();
        }
    

    return partidosOrdenados;
}

Processamento::~Processamento()
{
}
