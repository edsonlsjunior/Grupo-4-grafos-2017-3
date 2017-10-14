#include "..\Headers\Aresta.h"

Aresta::Aresta(int id, No* no1, No *no2, int peso)
{
	this->id = id;
	this->noOrigem = no1;
	this->noDestino = no2;
	this->peso = peso;
	this->proxima = nullptr;
}

Aresta::~Aresta()
{
	if(this == noOrigem->getPrimAresta())
	{
		if(this == noOrigem->getUltAresta())
		{
			noOrigem->setPrimAresta(nullptr);
			noOrigem->setUltAresta(nullptr);
		}
		else
			noOrigem->setPrimAresta(this->getProx());
	}
	else
	{
		Aresta* a = noOrigem->getPrimAresta();
		while(a->getProx() != this)
			a = a->getProx();

		if(this == noOrigem->getUltAresta())
		{
			noOrigem->setUltAresta(a);
			a->setProx(nullptr);
		}
		else
			a->setProx(this->getProx());
	}
	noOrigem->decrementarGrau();
}

/**************************
 * Retorna o id da Aresta
 **************************/
int Aresta::getId()
{
	return this->id;
}

/*********************************************
 * Retorna a próxima Aresta da lista
 *********************************************/
Aresta* Aresta::getProx()
{
	return proxima;
}

/*********************************************
 * Define a próxima Aresta da lista
 *********************************************/
void Aresta::setProx(Aresta* a)
{
	proxima = a;
}

/**********************************************
 * Retorna o id do No de destino da Aresta
 **********************************************/
int Aresta::getIdNoDestino()
{
	return noDestino->getId();
}

/***************************************
 * Retorna o Peso da Aresta
 ***************************************/
int Aresta::getPeso()
{
	return this->peso;
}
