#include "..\Headers\Aresta.h"

Aresta::Aresta(No* no2, int peso)
{
    segundoNo = no2;
    this->peso = peso;
    proxima = nullptr;
}

Aresta::~Aresta()
{
}

Aresta* Aresta:: getProx ()
{
    return proxima;
}

void Aresta:: setProx (Aresta* a)
{
    proxima = a;
}
