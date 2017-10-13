#ifndef HEADERS_ARESTA_H_
#define HEADERS_ARESTA_H_
#include <iostream>
#include "../Headers/No.h"

using namespace std;

class No;
class Aresta
{
	public:
		Aresta(int id, No* no1, No* no2, int peso);
		~Aresta();
		int getId();
		Aresta* getProx();
		void setProx(Aresta* a);
		int getIdNoDestino();				// Retorna o id do par da aresta;
		int getPeso();

	private:
		int id;
		int peso;
		No* noOrigem;
		No* noDestino;
		Aresta* proxima;
};

#endif /* HEADERS_ARESTA_H_ */
