#include "../Headers/Grafo.h"
#include "../Headers/FileUtils.h"
#include <iomanip>
#include <sstream>


using std::cout;
using std::setw;

/**********************************************************
 * Construtores sobrecarregados para criar um Grafo vazio
 * (1o construtor) ou um Grafo com n nos (2o construtor)
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
	for(int i = 0; i < n; i++)
	{
		inserirNo();
	}
	cout << "Grafo criado" << endl;
}

Grafo::~Grafo()
{
	No* p;
	while(primeiro != nullptr)
	{
		p = primeiro->getProx();
		delete primeiro;
		primeiro = p;
	}
}

/********************************************************
 * Funcao para inserir No ao Grafo
 ********************************************************/
void Grafo::inserirNo()
{
	contId++;
	No *p = new No(contId);
	if(ordem == 0)
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
 * Funcao auxiliar que procura um No usando apenas o id
 * do No
 ********************************************************/
No* Grafo::procurarNo(int idProcurado)
{
	No* p; // ponteiro auxiliar
	p = this->primeiro;
	for(int i = 0; i < ordem; i++)
	{
		if(p->getId() == idProcurado) return p;
		p = p->getProx();
	}
	cout << "o No " << idProcurado << " nao foi encontrado" << endl; //codigo apenas para identificar erros
	return p;
}

/********************************************************
 * Funcao para inserir Aresta ao grafo. A Aresta sera
 * alocada ao primeiro No do par, que e' referente ao
 * primeiro parametro da funcao
 ********************************************************/
void Grafo::inserirArestaGrafo(int idNo1, int idNo2, int pesoAresta)
{
	No *no1 = procurarNo(idNo1);
	No *no2 = procurarNo(idNo2);
	if(no1 != nullptr && no2 != nullptr)
	{
		no1->inserirArestaNo(no2, pesoAresta);
	}
}

/********************************************************
 * Printa as informacoes do Grafo: (posicao da sequencia,
 * Id do No, grau do No e as arestas de sua lista)
 * a formatacao deve ser revisada
 ********************************************************/
void Grafo::mostrarGrafo()
{
	No* p = primeiro;
//    for (int i = 0; i < ordem; i++)
//    {
//        cout << "No " << i+1 << " de id: "<< p->getId()<< " e Arestas: ";
//        p->imprimirArestas();
//        cout << endl;
//        p = p->getProx();
//    }

    cout << setw(3) << "No" << setw(10) << "ID" << setw(10) << "Grau" << setw(13) << "Arestas" << endl;
    for(int i = 0; i < ordem; i++)
    {
        cout << setw(3) << i + 1 << setw(10) << p->getId() << setw(10) << p->getGrau() << setw(13);
        p->imprimirArestas();
        cout << endl;
        p = p->getProx();
    }



}

/*********************************************
 * Retorna a ordem do Grafo
 *********************************************/
int Grafo::getOrdem()
{
	return ordem;
}

/********************************************************
 * Retorna true se o Grafo possuir apenas um No
 * ou falso caso possua dois ou mais
 ********************************************************/
bool Grafo::ehTrivial()
{
	return getOrdem() == 1;
}

/********************************************************
 * Retorna true se o Grafo nao possuir Arestas ou falso
 * caso possua alguma
 ********************************************************/
bool Grafo::ehNulo()
{
	No *n = this->primeiro;
	while(n != nullptr)
	{
		if(n->getPrimAresta() != nullptr)
			return false;
		n = n->getProx();
	}
	return true;
}

bool Grafo::ehKRegular(int k)
{
	No *n = this->primeiro;

	for(int i = 0; i < this->getOrdem(); i++)
	{
		if(n->getGrau() != k)
			return false;
        n = n->getProx();
	}

	return  true;
}

void Grafo::ehKRegular()
{
	No *ant = this->primeiro;
	No *prox = ant->getProx();

	while(prox != nullptr){

		if(ant->getGrau() != prox->getGrau()){
			break;
		}

		ant = prox;
		prox = prox->getProx();
	}

	if(prox == nullptr)
		cout << "O grafo e " << this->primeiro->getGrau()  << "-regular" << endl;
	else
		cout << "O grafo nao e regular" << endl;

}

bool Grafo::ehCompleto()
{
    if(this->ehKRegular(this->ordem - 1))
        return true;

    return false;
}

bool Grafo::ehDirecionado()
{
	return direcionado;
}

bool Grafo::setEhDirecionado(bool direcionado)
{
	this->direcionado = direcionado;
}

bool Grafo::ehPonderado()
{
    ifstream file(_argv[1]);
    string line;
    getline(file,line); //lê a primeira linha com o numero de vertices
    getline(file,line); //lê a segunda linha para identificar se o grafo é ponderado

    stringstream ss(line);
    int i, cont = 0;

    while(ss >> i)
        cont++;

    if(cont == 3)
        return true;

    return false;
}
