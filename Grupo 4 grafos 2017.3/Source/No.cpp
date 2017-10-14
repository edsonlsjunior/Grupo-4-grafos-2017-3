#include "..\Headers\Grafo.h"
#include "..\Headers\No.h"
#include "..\Headers\Aresta.h"
#include <sstream>

No::No(int id, Grafo* grafo)
{
	this->id = id;
	this->grafo = grafo;
	proximo = nullptr;
	primAresta = nullptr;
	ultAresta = nullptr;
	grau = 0;
}

No::~No()
{
	Aresta *a;
	while(primAresta != nullptr)
	{
		a = primAresta->getProx();
		delete primAresta;
		primAresta = a;
	}

	if(this == grafo->getPrimeiroNo())
	{
		if(this == grafo->getUltimoNo())
		{
			grafo->setPrimeiroNo(nullptr);
			grafo->setUltimoNo(nullptr);
		}
		else
			grafo->setPrimeiroNo(this->getProx());
	}
	else
	{
		No* n = grafo->getPrimeiroNo();
		while(n->getProx() != this)
			n = n->getProx();

		if(this == grafo->getUltimoNo())
		{
			grafo->setUltimoNo(n);
			n->setProx(nullptr);
		}
		else
			n->setProx(this->getProx());
	}
	grafo->decrementarOrdem();
}

/*********************************************
 * Define o proximo No da lista
 *********************************************/
void No::setProx(No* proxNo)
{
	proximo = proxNo;
}

/*********************************************
 * Retorna o proximo No da lista
 *********************************************/
No* No::getProx()
{
	return proximo;
}

/*********************************************
 * Retorna o id do No
 *********************************************/
int No::getId()
{
	return id;
}

/*********************************************
 * Retorna o grau do No
 *********************************************/
int No::getGrau()
{
	int qtdArestas = 0;
	Aresta *a = this->primAresta;

	if(a == nullptr)
		return 0;

	while(a != nullptr)
	{
		qtdArestas++;
		a = a->getProx();
	}
	return qtdArestas;
}

/******************************************
 * Incrementa o Grau do No em uma unidade
 ******************************************/
void No::incrementarGrau()
{
	this->grau++;
}

/******************************************
 * Decrementa o Grau do No em uma unidade
 ******************************************/
void No::decrementarGrau()
{
	this->grau--;
}

/************************************************
 * Retorna a primeira Aresta da lista de Arestas
 * conectadas ao No
 ************************************************/
Aresta* No::getPrimAresta()
{
	return this->primAresta;
}

/***********************************************
 * Define a primeira Aresta da lista de Arestas
 * conectadas ao No
 ***********************************************/
void No::setPrimAresta(Aresta* a)
{
	this->primAresta = a;
}

/***********************************************
 * Retorna a ultima Aresta da lista de Arestas
 * conectadas ao No
 */
Aresta* No::getUltAresta()
{
	return this->ultAresta;
}

/***********************************************
 * Define a ultima Aresta da lista de Arestas
 * conectadas ao No
 */
void No::setUltAresta(Aresta *a)
{
	this->ultAresta = a;
}

/***********************************************
 * Insere uma Aresta que conecta o no atual ao
 * No do parametro
 */
void No::inserirArestaNo(int idAresta, No* no2, int pesoAresta)
{
	incrementarGrau();
	Aresta *a = new Aresta(idAresta, this, no2, pesoAresta);
	if(primAresta == nullptr)
	{
		primAresta = a;
		ultAresta = a;
	}
	else
	{
		ultAresta->setProx(a);
		ultAresta = a;
	}
}

/***********************************************
 * Imprime o id de todos os Nos adjacentes ao No
 ***********************************************/
void No::imprimirNosAdjacentes()
{
	Aresta *arestaAuxiliar = primAresta;
	string adj = "";
	for(int i = 0; i < grau; i++)
	{
		adj += " " + to_string(arestaAuxiliar->getIdNoDestino());
		arestaAuxiliar = arestaAuxiliar->getProx();
	}
	cout << adj;
}

/***********************************************
 * Retorna true se existir uma ou mais Arestas
 * para o No de destino informado
 ***********************************************/
bool No::existeAresta(int idNoDestino)
{
	Aresta* a = getAresta(idNoDestino);
	return (a != nullptr);
}

/**************************************************
 * Retorna true se existir uma ou mais Arestas
 * para o No de destino que tenha(m) o Peso informado
 **************************************************/
bool No::existeAresta(int idNoDestino, int peso)
{
	Aresta* a = getAresta(idNoDestino, peso);
	return (a != nullptr);
}

/*****************************************************
 * Se existir, retorna uma Aresta para o No de destino
 * que tenha o peso informado. Se n�o, retorna NULL
 *
 * ATEN��O!!! Se houver mais de uma Aresta com o mesmo
 * Peso e mesmo No Destino, apenas uma sera' retornada
 *****************************************************/
Aresta* No::getAresta(int idNoDestino, int peso)
{
	Aresta* a = this->primAresta;

	while((a != nullptr) && (a->getIdNoDestino() != idNoDestino)
	        && (a->getPeso() == peso))
		a = a->getProx();

	return a;
}

/***********************************************
 * Retorna a primeira Aresta encontrada para o
 * No de Destino, ou NULL se nao houver nenhuma
 ***********************************************/
Aresta* No::getAresta(int idNoDestino)
{
	Aresta* a = this->primAresta;
	while((a != nullptr) && (a->getIdNoDestino() != idNoDestino))
		a = a->getProx();
	return a;
}
