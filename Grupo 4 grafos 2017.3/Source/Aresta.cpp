#include "..\Headers\Aresta.h"

Aresta::Aresta(No *no2, int peso)
{
	segundoNo = no2;
	this->peso = peso;
	proxima = nullptr;
}

Aresta::~Aresta()
{
}

/*********************************************
 * Retorna a pr�xima Aresta da lista
 *********************************************/
Aresta* Aresta::getProx()
{
	return proxima;
}

/*********************************************
 * Define a pr�xima Aresta da lista
 *********************************************/
void Aresta::setProx(Aresta* a)
{
	proxima = a;
}

/**********************************************
 * Retorna o id do No de destino da Aresta
 **********************************************/
int Aresta::idDoPar()
{
	return segundoNo->getId();
}
