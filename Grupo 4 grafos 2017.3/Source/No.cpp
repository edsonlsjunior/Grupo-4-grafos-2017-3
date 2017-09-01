#include "..\Headers\No.h"
#include "..\Headers\Aresta.h"

No::No(int id)
{
    this->id = id;
    proximo = NULL;
    primAresta = NULL;
    ultAresta = NULL;
}

No::~No()
{
    Aresta *p;
    while (primAresta!= NULL)
    {
        p = primAresta->getProx();
        delete primAresta;
        primAresta = p;
    }
}
void No:: setProx (No* proxNo)
{
    proximo = proxNo;
}

No* No::getProx ()
{
    return proximo;
}

int No::getId()
{
    return id;
}

void No::inserirArestaNo(No* no2,int pesoAresta)
{
    Aresta *a = new Aresta(no2, pesoAresta);
    if (primAresta == NULL)
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
