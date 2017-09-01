#include "../Headers/Grafo.h"

/**********************************************************
 * Construtores sobrecarregados para criar um grafo vazio
 * (1o construtor) ou um grafo com n nos (2o construtor)
 * e destrutor do grafo
 **********************************************************/
Grafo::Grafo()
{
    ordem = 0;
    grau = 0;
    contId = 0;
    primeiro = nullptr;
    ultimo = nullptr;
}

Grafo::Grafo(int n)
{
    ordem = 0;
    grau = 0;
    contId = 0;
    for(int i=0; i < n; i++)
    {
        inserirNo();
    }
    cout << "grafo criado" << endl;
}
Grafo::~Grafo()
{
    No* p;
    while (primeiro!= nullptr)
    {
        p = primeiro->getProx();
        delete primeiro;
        primeiro = p;
    }
}

/********************************************************
 * Funcao para inserir no ao grafo
 ********************************************************/
void Grafo::inserirNo()
{
    contId++;
    No *p = new No(contId);
    if (ordem == 0)
    {
        primeiro = p;
        ultimo = p;
    }
    else
    {
        ultimo->setProx(p);
        ultimo = p;
    }
    ordem++;
}

/********************************************************
 * Funcao auxiliar que procura um no usando apenas o id
 * do no
 ********************************************************/
No* Grafo::procurarNo(int idProcurado)
{
    No* ponteiroAuxiliar;
    ponteiroAuxiliar = this->primeiro;
    for (int i = 0; i < ordem; i++)
    {
        if (ponteiroAuxiliar->getId() == idProcurado)
            return ponteiroAuxiliar;
        ponteiroAuxiliar = ponteiroAuxiliar->getProx();
    }
    cout << "o No " << idProcurado<< " nao foi encontrado";       //codigo apenas para identificar erros
     return ponteiroAuxiliar;
}

/********************************************************
 * Funcao para inserir aresta ao grafo, a aresta sera
 * alocada ao primeiro no' do par, que e' referente ao
 * primeiro parametro da funcao
 ********************************************************/
void Grafo::inserirArestaGrafo(int idNo1, int idNo2, int pesoAresta)
{
    No *no1 = procurarNo(idNo1);
    No *no2 = procurarNo (idNo2);
    if (no1 != nullptr && no2 != nullptr)
    {
        no1->inserirArestaNo(no2, pesoAresta);
    }
}

/********************************************************
 * Printa as informacoes do grafo: (posicao da sequencia,
 * id do no, e as arestas de sua lista)
 ********************************************************/
void Grafo::mostrarGrafo ()
{
    No* p = primeiro;
    for (int i = 0; i < ordem; i++)
    {
        cout << "No " << i+1 << " de id: "<< p->getId()<< " e Arestas: ";
        p->imprimirArestas();
        cout << endl;
        p = p->getProx();
    }
}
