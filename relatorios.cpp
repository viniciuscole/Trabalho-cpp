#include "relatorios.h"

Relatorios::Relatorios(time_t dataDaEleicao, int tipoDeEleicao)
{
    this->dataDaEleicao = dataDaEleicao;
    this->tipoDeEleicao = tipoDeEleicao;
}

//PRIVATE
string Relatorios::transformaMaisculo(string str)
{
    string strOut;
    for (string::iterator it = str.begin(); it != str.end(); ++it)
    {
        strOut.push_back(toupper(*it, loc));
    }
    return strOut;
}
bool Relatorios::checaSeCandidatoEstaNaLista(list<Candidato *> lista, Candidato *candidato)
{
    for (Candidato* candidatoLista : lista)
    {
        if (candidatoLista->getNumeroCandidato() == candidato->getNumeroCandidato())
        {
            return true;
        }
    }
    return false;
}
//



//PUBLIC
void Relatorios::setCandidatos(list<Candidato *> candidatos)
{
    this->candidatosOrdenados = candidatos;
}

void Relatorios::setPartidos(list<Partido *> partidos)
{
    this->partidosOrdenados = partidos;
}

void Relatorios::setCandidatosEleitos(list<Candidato *> candidatosEleitos)
{
    this->candidatosEleitosOrdenados = candidatosEleitos;
}


void Relatorios::setLocale(locale loc)
{
    this->loc = loc;
}

void Relatorios::gerarRelatorios()
{   
    gerarRelatorio1();
    gerarRelatorio2();
    gerarRelatorio3();
    gerarRelatorio4();
    gerarRelatorio5();
    gerarRelatorio6();
    //gerarRelatorio7();
    gerarRelatorio8();
    gerarRelatorio9();
    gerarRelatorio10();
    gerarRelatorio11();
}

void Relatorios::gerarRelatorio1()
{
    cout << "Número de vagas: " << candidatosEleitosOrdenados.size() << endl;
}

void Relatorios::gerarRelatorio2()
{
    int i = 1;
    if(tipoDeEleicao == 1)
    {
        cout << "Deputados estaduais eleitos:" << endl;
        for(Candidato* candidatoEleito : candidatosEleitosOrdenados)
        {
            
            string votoStr = candidatoEleito->getVotos() == 1 ? " voto" : " votos";
            
            if(candidatoEleito->getNumeroFederacao()==-1)
            {
                
                cout << i << " - " << transformaMaisculo(candidatoEleito->getNome())
                     << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                     << candidatoEleito->getVotos() << votoStr << ")" << endl;

            }
            else 
            {
                cout << i << " - *" << transformaMaisculo(candidatoEleito->getNome())
                     << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                     << candidatoEleito->getVotos() << votoStr << ")" << endl;
            }
            i++;
        }
    }
    else if(tipoDeEleicao == 0)
    {
        cout << "Deputados federais eleitos:" << endl;
        for(Candidato* candidatoEleito : candidatosEleitosOrdenados)
        {
            
            string votoStr = candidatoEleito->getVotos() == 1 ? " voto" : " votos";
            
            if(candidatoEleito->getNumeroFederacao()==-1)
            {
                
                cout << i << " - " << transformaMaisculo(candidatoEleito->getNome())
                     << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                     << candidatoEleito->getVotos() << votoStr << ")" << endl;

            }
            else 
            {
                cout << i << " - *" << transformaMaisculo(candidatoEleito->getNome())
                     << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                     << candidatoEleito->getVotos() << votoStr << ")" << endl;
            }
            i++;
        }
    }
    else
        cout << "Tipo de eleição inválido" << endl;
}

void Relatorios::gerarRelatorio3()
{
    int i = 1;
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    for(Candidato* candidato : candidatosOrdenados)
    {
        string votoStr = candidato->getVotos() == 1 ? " voto" : " votos";
        
        if(candidato->getNumeroFederacao()==-1)
        {
            
            cout << i << " - " << transformaMaisculo(candidato->getNome())
                 << " (" << candidato->getPartido()->getSigla() << ", " 
                 << candidato->getVotos() << votoStr << ")" << endl;
        }
        else
        {
            cout << i << " - *" << transformaMaisculo(candidato->getNome())
                 << " (" << candidato->getPartido()->getSigla() << ", " 
                 << candidato->getVotos() << votoStr << ")" << endl;
        }

        i++;

        if(i > candidatosEleitosOrdenados.size())
            break;
        
    }
}

void Relatorios::gerarRelatorio4()
{
    int i = 1;
    
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;

    for(Candidato* candidato : candidatosOrdenados)
    {
        string votoStr = candidato->getVotos() == 1 ? " voto" : " votos";
        
        if(checaSeCandidatoEstaNaLista(candidatosEleitosOrdenados, candidato) == false)
            if(candidato->getNumeroFederacao()==-1)
            {
                
                cout << i << " - " << transformaMaisculo(candidato->getNome())
                    << " (" << candidato->getPartido()->getSigla() << ", " 
                    << candidato->getVotos() << votoStr << ")" << endl;
            }
            else
            {
                cout << i << " - *" << transformaMaisculo(candidato->getNome())
                    << " (" << candidato->getPartido()->getSigla() << ", " 
                    << candidato->getVotos() << votoStr << ")" << endl;
            }

        i++;

        if(i > candidatosEleitosOrdenados.size())
            break;
        
    }
}

void Relatorios::gerarRelatorio5()
{
    int i = 1;
    
    cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;


    list<Candidato*> candidatosMaisVotados;

    for(Candidato* candidato : candidatosOrdenados)
    {
        candidatosMaisVotados.push_back(candidato);
        i++;
        if(i > candidatosEleitosOrdenados.size())
            break;
    }

    for(Candidato* candidatoEleito : candidatosEleitosOrdenados)
    {

        string votoStr = candidatoEleito->getVotos() == 1 ? " voto" : " votos";


        if(checaSeCandidatoEstaNaLista(candidatosMaisVotados, candidatoEleito)==false)
        {
            if(candidatoEleito->getNumeroFederacao()==-1)
            {
                cout << i << " - " << transformaMaisculo(candidatoEleito->getNome())
                    << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                    << candidatoEleito->getVotos() << votoStr << ")" << endl;
            }
            else
            {
                cout << i << " - *" << transformaMaisculo(candidatoEleito->getNome())
                    << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                    << candidatoEleito->getVotos() << votoStr << ")" << endl;
            }
        }
    }
}

void Relatorios::gerarRelatorio6()
{
    int i=1, j=0;

    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;

    for(Partido* partido : partidosOrdenados)
    {
        string votoStr = partido->getVotosTotais() == 1 ? " voto" : " votos";
        string nominalStr = partido->getVotosNominais() == 1 ? " nominal" : " nominais";
    
        j=0;
        for(Candidato* candidato : partido->getCandidatos())
        {
            if(checaSeCandidatoEstaNaLista(candidatosEleitosOrdenados, candidato))
                j++;
        }

        string eleitoStr = j == 1 ? " candidato eleito" : " candidatos eleitos";
        
        
        cout << i << " - " << partido->getSigla() << " - " << partido->getNumero() << ", "
             << partido->getVotosTotais() << votoStr << " (" << partido->getVotosNominais()
             << nominalStr << " e " << partido->getVotosLegenda() << " de legenda), " << j 
             << eleitoStr << endl;


    }

}

/*
void Relatorios::gerarRelatorio7()
{

}
*/

void Relatorios::gerarRelatorio8()
{
    cout << "Primeiro e último colocados de cada partido:" << endl;
    //TODO
}

