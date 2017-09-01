#include "..\Headers\No.h"
#include "..\Headers\Aresta.h"

No::No(int id)
{
    this->id = id;
    proximo = nullptr;
    primAresta = nullptr;
    ultAresta = nullptr;
    grau = 0;
}

No::~No()
{
    Aresta *p;
    while (primAresta!= nullptr)
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
    grau++;
    Aresta *a = new Aresta(no2, pesoAresta);
    if (primAresta == nullptr)
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

void No:: imprimirArestas()
{
    Aresta *ponteiroAuxiliar = primAresta;
    for (int i = 0; i < grau; i++)
    {
        cout << ponteiroAuxiliar->idDoPar() << "  ";
        ponteiroAuxiliar ->getProx();
    }
}