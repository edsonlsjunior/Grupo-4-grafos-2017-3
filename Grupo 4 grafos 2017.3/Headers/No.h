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
		void incrementarGrau();
		void decrementarGrau();

		bool existeAresta(int idNoDestino);
		bool existeAresta(int idNoDestino, int peso);
		Aresta* getAresta(int idNoDestino, int peso);
		Aresta* getPrimAresta();
		void setPrimAresta(Aresta *a);
		Aresta* getUltAresta();
		void setUltAresta(Aresta *a);
		void inserirArestaNo(int id, No* no2, int pesoAresta);
		void imprimirNosAdjacentes();

	private:
		int id;
		int grau;					// Numero de Arestas do No
		No *proximo;
		Aresta *primAresta;
		Aresta *ultAresta;
};

#endif /* HEADERS_NO_H_ */
