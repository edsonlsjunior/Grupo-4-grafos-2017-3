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
	grauEntrada = 0;
	grauSaida = 0;
	grafo->incrementarOrdem();
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

/*****************************************
 * Retorna o Grafo ao qual o No pertence
 *****************************************/
Grafo* No::getGrafo()
{
	return this->grafo;
}

/*********************************************
 * Retorna o Grau do No
 *********************************************/
int No::getGrau()
{
	if(grafo->ehDirecionado())
		return this->grauSaida + this->grauEntrada;
	else
		return this->grauSaida; // Neste caso, grauEntrada = grauSaida
}

/******************************************
 * (Grafo Não-Direcionado)
 * Incrementa o Grau do No em uma unidade
 ******************************************/
void No::incrementarGrau()
{
	if(grafo->ehDirecionado() == false)
		cout
		        << "O Grafo nao e' direcionado. Incremente o Grau de Entrada ou Saida"
		        << endl;
	else
	{
		this->grauSaida++;
		this->grauEntrada++;
	}
}

/******************************************
 * (Grafo Não-Direcionado)
 * Decrementa o Grau do No em uma unidade
 ******************************************/
void No::decrementarGrau()
{
	if(grafo->ehDirecionado() == false)
		cout
		        << "O Grafo nao e' direcionado. Decremente o Grau de Entrada ou Saida"
		        << endl;
	else
	{
		this->grauSaida--;
		this->grauEntrada--;
	}
}

/*********************************************
 * Retorna o Grau de Entrada do No
 *********************************************/
int No::getGrauEntrada()
{
	return this->grauEntrada;
}

/*****************************************************
 * Incrementa o Grau de Entrada do No em uma unidade
 *****************************************************/
void No::incrementarGrauEntrada()
{
	this->grauEntrada++;
	if(grafo->ehDirecionado() == false)
		this->grauSaida++;
}

/*****************************************************
 * Decrementa o Grau de Entrada do No em uma unidade
 *****************************************************/
void No::decrementarGrauEntrada()
{
	this->grauEntrada--;
	if(grafo->ehDirecionado() == false)
		this->grauSaida--;
}

/*********************************************
 * Retorna o Grau de Saida do No
 *********************************************/
int No::getGrauSaida()
{
	return this->grauSaida;
}

/*****************************************************
 * Incrementa o Grau de Saída do No em uma unidade
 ****************************************************/
void No::incrementarGrauSaida()
{
	this->grauSaida++;
	if(grafo->ehDirecionado() == false)
		this->grauEntrada--;
}

/****************************************************
 * Decrementa o Grau de Saida do No em uma unidade
 ****************************************************/
void No::decrementarGrauSaida()
{
	this->grauSaida--;
	if(grafo->ehDirecionado() == false)
		this->grauEntrada--;
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
void No::mostrarNosAdjacentes()
{
	Aresta *arestaAuxiliar = primAresta;
	string adj = "";
	for(int i = 0; i < grauSaida; i++)
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
 * que tenha o peso informado. Se não, retorna NULL
 *
 * ATENÇÃO!!! Se houver mais de uma Aresta com o mesmo
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

/**************************************************************
 * Checa se o id deste No existe no vetor de ids de Nos
 * informado. A funcao necessita tambem do tamanho do vetor
 **************************************************************/
bool No::existeDentroDoVetor(int idsNos[], int tamanhoVetor)
{
	int idNoProcurado = this->id;
	bool noExisteNoArray = false;
	for(int i = 0; i < tamanhoVetor; i++)
		if(idNoProcurado == idsNos[i])
			noExisteNoArray = true;
	return noExisteNoArray;
}
