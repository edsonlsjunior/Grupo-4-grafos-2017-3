#include "../Headers/Grafo.h"
#include "../Headers/FileUtils.h"
#include "../Headers/Aresta.h"
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
	maiorIdNo = 0;
	maiorIdAresta = 0;
	primeiroNo = nullptr;
	ultimoNo = nullptr;
	cout << "Grafo vazio criado." << endl;
}

Grafo::Grafo(int n)
{
	ordem = 0;
	grau = 0;
	maiorIdNo = 0;
	maiorIdAresta = 0;
	for(int i = 0; i < n; i++)
		inserirNo();
	cout << "Grafo com " << ordem << " nos criado." << endl;
}

Grafo::~Grafo()
{
	No* p;
	while(primeiroNo != nullptr)
	{
		p = primeiroNo->getProx();
		delete primeiroNo;
		primeiroNo = p;
	}
}

/********************************************************
 * Funcao para inserir um No vazio ao Grafo
 ********************************************************/
void Grafo::inserirNo()
{
	maiorIdNo++;
	No *p = new No(maiorIdNo);
	if(ordem == 0)
	{
		primeiroNo = p;
		ultimoNo = p;
	}
	else
	{
		ultimoNo->setProx(p);
		ultimoNo = p;
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
	p = this->primeiroNo;
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
		maiorIdAresta++;
		no1->inserirArestaNo(maiorIdAresta, no2, pesoAresta);
		int grauNo = no1->getGrau();
		if(grauNo > this->grau)
			this->grau = grauNo;
	}
}

/*********************************************************
 * Exclui uma Aresta que liga o No de Origem e o No de
 * Destino e tenha o Peso informado
 *********************************************************/
void Grafo::excluirArestaGrafo(int idNoOrigem, int idNoDestino, int peso)
{
	No* noOrigem = procurarNo(idNoOrigem);
	Aresta* a = noOrigem->getAresta(idNoDestino, peso);
	if(a != nullptr)
		delete a;
}

/********************************************
 * Exclui a Aresta que tem o id informado
 ********************************************/
void Grafo::excluirArestaGrafo(int idAresta)
{
	No* n = primeiroNo;
	Aresta* a;
	while(n != nullptr)
	{
		a = n->getPrimAresta();
		while(a != nullptr)
		{
			if(a->getId() == idAresta)
			{
				delete a;
				return;
			}
			a = a->getProx();
		}
		n = n->getProx();
	}
}

/********************************************************
 * Printa as informacoes do Grafo: (posicao da sequencia,
 * id do No, grau do No e as arestas de sua lista)
 * a formatacao deve ser revisada
 ********************************************************/
void Grafo::mostrarGrafo()
{
	No* p = primeiroNo;
//    for (int i = 0; i < ordem; i++)
//    {
//        cout << "No " << i+1 << " de id: "<< p->getId()<< " e Arestas: ";
//        p->imprimirArestas();
//        cout << endl;
//        p = p->getProx();
//    }
<<<<<<< HEAD

    cout << setw(3) << "No" << setw(10) << "ID" << setw(10) << "Grau" << setw(13) << "Arestas" << endl;
    for(int i = 0; i < ordem; i++)
    {
        cout << setw(3) << i + 1 << setw(10) << p->getId() << setw(10) << p->getGrau() << setw(13);
        p->imprimirArestas();
        cout << endl;
        p = p->getProx();
    }



=======
	cout << setw(3) << "No" << setw(10) << "ID" << setw(10) << "Grau" << setw(17) << "Nos Adjacentes" << endl;
	for(int i = 0; i < ordem; i++)
	{
		cout << setw(3) << i + 1 << setw(10) << p->getId() << setw(10) << p->getGrau() << setw(17);
		p->imprimirNosAdjacentes();
		cout << endl;
		p = p->getProx();
	}
>>>>>>> ff90f54b5ace50a4ee21f04506552b56fbf0797f
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
 * Retorna true se o Grafo nao possuir Arestas ou false
 * caso possua alguma
 ********************************************************/
bool Grafo::ehNulo()
{
	No *n = this->primeiroNo;
	while(n != nullptr)
	{
		if(n->getPrimAresta() != nullptr)
			return false;
		n = n->getProx();
	}
	return true;
}

<<<<<<< HEAD
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
=======
>>>>>>> ff90f54b5ace50a4ee21f04506552b56fbf0797f
