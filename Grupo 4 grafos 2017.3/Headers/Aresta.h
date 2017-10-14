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
		int getIdNoDestino();
		int getPeso();

	private:
		int id;						// Id da Aresta
		int peso;					// Peso da Aresta
		No* noOrigem;				// No de Origem da Aresta
		No* noDestino;				// No de Destino da Aresta
		Aresta* proxima;			// Proxima Aresta da lista
};

#endif /* HEADERS_ARESTA_H_ */
