
#include "relatorios.h"
#include "candidato.h"
#include "partido.h"


Relatorios::Relatorios(string dataDaEleicao, int tipoDeEleicao)
{
    this->dataDaEleicao = dataDaEleicao;
    this->tipoDeEleicao = tipoDeEleicao;
    cout.imbue(locBR);
}

//PRIVATE
string Relatorios::transformaMaisculo(string str)
{
    string strOut;
    for (string::iterator it = str.begin(); it != str.end(); ++it)
    {
        strOut.push_back(toupper(*it, locBR));
    }
    return strOut;
}
bool Relatorios::checaSeCandidatoEstaNaLista(list<Candidato *>* lista, Candidato *candidato)
{
    for (Candidato* candidatoLista : *lista)
    {
        if (candidatoLista->getNumeroCandidato() == candidato->getNumeroCandidato())
        {
            return true;
        }
    }
    return false;
}
int Relatorios::posicaoCandidatoNaLista(list<Candidato *>* lista, Candidato *candidato)
    {
        int posicao = 0;
        for (Candidato* candidatoLista : *lista)
        {
            if (candidatoLista->getNumeroCandidato() == candidato->getNumeroCandidato())
            {
                return posicao;
            }
            posicao++;
        }
        return -1;
}
Candidato *Relatorios::candidatoComMenosVotos(list<Candidato *>* lista)
{   
    int i=0;
    Candidato* candidatoComMenosVotos;
    for (Candidato* candidato : *lista)
    {
        if(i==0)
        {
            candidatoComMenosVotos = candidato;
        }
        else
        {
            if(candidato->getVotos() <= candidatoComMenosVotos->getVotos() && candidato->getEhCandidatoLegenda()==false)
            {
                candidatoComMenosVotos = candidato;
            }
        }
        i++;
    }
    return candidatoComMenosVotos;
}
vector<string> Relatorios::separaPalavraPorChar(string str, char delimitador)
{
    vector<string> palavras;
        stringstream ss(str);
        string palavra;
        
        while(getline(ss, palavra, delimitador)) {
            palavras.push_back(palavra);
        }
        
    return palavras;
}
bool Relatorios::ehMaisVelho(string dataNascimento1, string dataNascimento2)
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



//PUBLIC
void Relatorios::setCandidatos(list<Candidato *>* candidatos)
{
    this->candidatosOrdenados = candidatos;
}

void Relatorios::setPartidos(list<Partido *>* partidos)
{
    this->partidosOrdenados = partidos;
}

void Relatorios::setCandidatosEleitos(list<Candidato *>* candidatosEleitos)
{
    this->candidatosEleitosOrdenados = candidatosEleitos;
}


void Relatorios::setLocale(locale loc)
{
    this->locBR = loc;
}

void Relatorios::imprimeCandidatos()
{
    for(Candidato* candidato : *candidatosOrdenados)
    {
        cout << candidato->toString() << endl;
    }
}

void Relatorios::imprimePartidos()
{
    for(Partido* partido : *partidosOrdenados)
    {
        cout << partido->getSigla() << "-" << partido->getNumero()  << endl;
    }
}

void Relatorios::imprimeCandidatosEleitos()
{
    for(Candidato* candidato : *candidatosEleitosOrdenados)
    {
        cout << candidato->toString() << endl;
    }
}

void Relatorios::gerarRelatorios()
{   
    cout << fixed << setprecision(2);
    gerarRelatorio1();
    cout << endl;
    gerarRelatorio2();
    cout << endl;
    gerarRelatorio3();
    cout << endl;
    gerarRelatorio4();
    cout << endl;
    gerarRelatorio5();
    cout << endl;
    gerarRelatorio6();
    cout << endl;
    //gerarRelatorio7();
    //cout << endl;
    gerarRelatorio8();
    cout << endl;
    gerarRelatorio9();
    cout << endl;
    gerarRelatorio10();
    cout << endl;
    gerarRelatorio11();
    delete candidatosOrdenados;
    delete partidosOrdenados;
    delete candidatosEleitosOrdenados;
    cout.imbue(locale::classic());
}

void Relatorios::gerarRelatorio1()
{
    cout << "Número de vagas: " << candidatosEleitosOrdenados->size() << endl;
}

void Relatorios::gerarRelatorio2()
{
    int i = 1;
    if(tipoDeEleicao == 1)
    {
        cout << "Deputados estaduais eleitos:" << endl;
        for(Candidato* candidatoEleito : *candidatosEleitosOrdenados)
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
        for(Candidato* candidatoEleito : *candidatosEleitosOrdenados)
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
    unsigned long int i = 1;
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    for(Candidato* candidato : *candidatosOrdenados)
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

        if(i > candidatosEleitosOrdenados->size())
            break;
        
    }
}

void Relatorios::gerarRelatorio4()
{
    unsigned long int i = 1;
    
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;

    for(Candidato* candidato : *candidatosOrdenados)
    {
        string votoStr = candidato->getVotos() == 1 ? " voto" : " votos";
        
        if(checaSeCandidatoEstaNaLista(candidatosEleitosOrdenados, candidato) == false)
        {
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
        }

        i++;

        if(i > candidatosEleitosOrdenados->size())
            break;
        
    }
}

void Relatorios::gerarRelatorio5()
{
    unsigned long int i = 1;
    
    cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;


    list<Candidato*>* candidatosMaisVotados = new list<Candidato*>();

    for(Candidato* candidato : *candidatosOrdenados)
    {
        candidatosMaisVotados->push_back(candidato);
        i++;
        if(i > candidatosEleitosOrdenados->size())
            break;
    }

    for(Candidato* candidatoEleito : *candidatosEleitosOrdenados)
    {

        string votoStr = candidatoEleito->getVotos() == 1 ? " voto" : " votos";


        if(checaSeCandidatoEstaNaLista(candidatosMaisVotados, candidatoEleito)==false)
        {
            if(candidatoEleito->getNumeroFederacao()==-1)
            {
                cout << posicaoCandidatoNaLista(candidatosOrdenados, candidatoEleito)+1 << " - " << transformaMaisculo(candidatoEleito->getNome())
                    << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                    << candidatoEleito->getVotos() << votoStr << ")" << endl;
            }
            else
            {
                cout << posicaoCandidatoNaLista(candidatosOrdenados, candidatoEleito)+1 << " - *" << transformaMaisculo(candidatoEleito->getNome())
                    << " (" << candidatoEleito->getPartido()->getSigla() << ", " 
                    << candidatoEleito->getVotos() << votoStr << ")" << endl;
            }
        }
        i++;
    }
    delete candidatosMaisVotados;
}

void Relatorios::gerarRelatorio6()
{
    int i=1, j=0;

    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;

    for(Partido* partido : *partidosOrdenados)
    {   
        if(partido==NULL)
            continue;
        string votoStr = partido->getVotosTotais() <= 1 ? " voto" : " votos";
        string nominalStr = partido->getVotosNominais() <= 1 ? " nominal" : " nominais";
    
        j=0;
        for(Candidato* candidato : *(partido->getCandidatos()))
        {
            if(checaSeCandidatoEstaNaLista(candidatosEleitosOrdenados, candidato))
                j++;
        }

        string eleitoStr = j <= 1 ? " candidato eleito" : " candidatos eleitos";
        
        
        cout << i << " - " << partido->getSigla() << " - " << partido->getNumero() << ", "
             << partido->getVotosTotais() << votoStr << " (" << partido->getVotosNominais()
             << nominalStr << " e " << partido->getVotosLegenda() << " de legenda), " << j 
             << eleitoStr << endl;

        i++;

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


    list<Candidato*>* candidatosMaisVotados = new list<Candidato*>();
    for(Partido* partido : *partidosOrdenados){
        if(partido==NULL)
            continue;
        if((*partido->getCandidatos()).size()>0 && (*partido->getCandidatos()).front()->getVotos()>0)
            candidatosMaisVotados->push_back((*partido->getCandidatos()).front());
    }

    candidatosMaisVotados->sort([this](Candidato* c1, Candidato* c2) { 
        if(c1==NULL || c2==NULL)
            return false;
        if(c1->getVotos() != c2->getVotos())
            return c2->getVotos() < c1->getVotos();
        else
            return ehMaisVelho(c2->getDataNascimento(), c1->getDataNascimento());
    });

    int i=1;
    for(Candidato* candidato : *candidatosMaisVotados)
    {
        Candidato* candidatoMenosVotado = candidatoComMenosVotos(candidato->getPartido()->getCandidatos()); // pega o candidato com menos votos do partido, excluindo os "candidatos de legenda"
         
    

        string votoStrCandidatoMaisVotos = candidato->getVotos() <= 1 ? " voto" : " votos";
        string votoStrCandidatoMenosVotos =  candidatoMenosVotado->getVotos() <= 1 ? " voto" : " votos";
        
        stringstream candidatoMaisVotadoNumeroStr;                                      // converte o número de ambos os candidatos para string
        candidatoMaisVotadoNumeroStr << candidato->getNumeroCandidato();                // dessa forma, é possível imprimir o número do candidato
        stringstream candidatoMenosVotadoNumeroStr;                                     // sem a formatação padrão do locale previamente setado
        candidatoMenosVotadoNumeroStr << candidatoMenosVotado->getNumeroCandidato();    // ex: 1.234.567 -> 1234567
            
        cout << i << " - " << candidato->getPartido()->getSigla() << " - "
            << candidato->getPartido()->getNumero() << ", " << transformaMaisculo(candidato->getNome()) 
            << " (" << candidatoMaisVotadoNumeroStr.str() << ", " << candidato->getVotos()
            << votoStrCandidatoMaisVotos << ") / " << transformaMaisculo(candidatoMenosVotado->getNome())
            << " (" << candidatoMenosVotadoNumeroStr.str() << ", " << candidatoMenosVotado->getVotos()
            << votoStrCandidatoMenosVotos << ")" << endl;
    
        i++;
    }
    delete candidatosMaisVotados;
}

void Relatorios::gerarRelatorio9()
{
    int menorQue30 = 0, entre30e40 = 0, entre40e50 = 0, entre50e60 = 0, maiorQue60 = 0;

    for(Candidato* candidato : *candidatosEleitosOrdenados){
        if(candidato==NULL)
            continue;
        int idade = candidato->calculaIdade(dataDaEleicao);
        if(idade < 30)
            menorQue30++;
        else if(idade >= 30 && idade < 40)
            entre30e40++;
        else if(idade >= 40 && idade < 50)
            entre40e50++;
        else if(idade >= 50 && idade < 60)
            entre50e60++;
        else
            maiorQue60++;
    }

    float percentualMenorQue30 = (float)menorQue30/(float)candidatosEleitosOrdenados->size()*100;
    float percentualEntre30e40 = (float)entre30e40/(float)candidatosEleitosOrdenados->size()*100;
    float percentualEntre40e50 = (float)entre40e50/(float)candidatosEleitosOrdenados->size()*100;
    float percentualEntre50e60 = (float)entre50e60/(float)candidatosEleitosOrdenados->size()*100;
    float percentualMaiorQue60 = (float)maiorQue60/(float)candidatosEleitosOrdenados->size()*100;

    cout << "Eleitos, por faixa etária (na data da eleição):" << endl;
    cout << "      Idade < 30: " << menorQue30 << " (" << percentualMenorQue30 << "%)" << endl;
    cout << "30 <= Idade < 40: " << entre30e40 << " (" << percentualEntre30e40 << "%)" << endl;
    cout << "40 <= Idade < 50: " << entre40e50 << " (" << percentualEntre40e50 << "%)" << endl;
    cout << "50 <= Idade < 60: " << entre50e60 << " (" << percentualEntre50e60 << "%)" << endl;
    cout << "60 <= Idade     : " << maiorQue60 << " (" << percentualMaiorQue60 << "%)" << endl;

}

void Relatorios::gerarRelatorio10()
{
    cout << "Eleitos, por gênero:" << endl;
    int qtdMasculino = 0, qtdFeminino = 0;

    for(Candidato* candidato : *candidatosEleitosOrdenados){
        if(candidato==NULL)
            continue;
        if(candidato->getGenero() == 2)
            qtdMasculino++;
        else if(candidato->getGenero() == 4)
            qtdFeminino++;
    }

    float percentualMasculino = (float)qtdMasculino/(float)candidatosEleitosOrdenados->size()*100;
    float percentualFeminino = (float)qtdFeminino/(float)candidatosEleitosOrdenados->size()*100;

    cout << "Feminino: " << qtdFeminino << " (" << percentualFeminino << "%)" << endl;
    cout << "Masculino: " << qtdMasculino << " (" << percentualMasculino << "%)" << endl;
}

void Relatorios::gerarRelatorio11(){
    int votosNominais = 0, votosLegenda = 0;
    for(Candidato* candidato : *candidatosOrdenados){
        if(candidato==NULL)
            continue;
        votosNominais += candidato->getVotos();
    }
    for(Partido* partido : *partidosOrdenados){
        if(partido==NULL)
            continue;
        votosLegenda += partido->getVotosLegenda();
    }

    float percentualVotosNominais = (float)votosNominais/(float)(votosNominais+votosLegenda)*100;
    float percentualVotosLegenda = (float)votosLegenda/(float)(votosNominais+votosLegenda)*100;

    cout << "Total de votos válidos: " << votosNominais + votosLegenda << endl;
    cout << "Total de votos nominais:   " << votosNominais << " (" << percentualVotosNominais << "%)" << endl;
    cout << "Total de votos de legenda: " << votosLegenda << " (" << percentualVotosLegenda << "%)" << endl;
}

Relatorios::~Relatorios()
{
    
}
