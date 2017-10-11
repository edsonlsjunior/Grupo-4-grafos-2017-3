#ifndef HEADERS_ARESTA_H_
#define HEADERS_ARESTA_H_
#include <iostream>
#include "../Headers/No.h"

using namespace std;

class No;
class Aresta
{
	public:
		Aresta(No* no2, int peso);
		~Aresta();
		Aresta* getProx();
		void setProx(Aresta* a);
		int idDoPar();                 //retorna o id do par da aresta;

	private:
		int peso;
		No *segundoNo;
		Aresta *proxima;
};

#endif /* HEADERS_ARESTA_H_ */
