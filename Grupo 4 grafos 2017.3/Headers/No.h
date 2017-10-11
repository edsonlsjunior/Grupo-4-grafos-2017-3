#ifndef HEADERS_NO_H_
#define HEADERS_NO_H_

#include <iostream>

using namespace std;

class Aresta;
class No
{
	public:
		No(int id);
		~No();
		void setProx(No *proxNo);
		No* getProx();
		int getId();
		int getGrau();
		Aresta* getPrimAresta();
		void setPrimAresta(Aresta *a);
		Aresta* getUltAresta();
		void setUltAresta(Aresta *a);
		void inserirArestaNo(No* no2, int pesoAresta);
		void imprimirArestas();

	private:
		int id;
		int grau;					// numero de arestas do no
		No *proximo;
		Aresta *primAresta;
		Aresta *ultAresta;
};

#endif /* HEADERS_NO_H_ */
