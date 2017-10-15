#ifndef HEADERS_NO_H_
#define HEADERS_NO_H_

#include <iostream>
#include "../Headers/Aresta.h"
#include "../Headers/Grafo.h"

using namespace std;

class Grafo;
class Aresta;
class No
{
	public:
		No(int id, Grafo* grafo);
		~No();
		void setProx(No *proxNo);
		No* getProx();
		int getId();
		Grafo* getGrafo();
		int getGrau();
		int getGrauEntrada();
		int getGrauSaida();
		void incrementarGrau();		// Apenas para Grafos N�o-Direcionados
		void decrementarGrau();		// Apenas para Grafos N�o-Direcionados
		void incrementarGrauEntrada();
		void incrementarGrauSaida();
		void decrementarGrauEntrada();
		void decrementarGrauSaida();

		bool existeAresta(int idNoDestino);
		bool existeAresta(int idNoDestino, int peso);
		Aresta* getAresta(int idNoDestino);
		Aresta* getAresta(int idNoDestino, int peso);
		Aresta* getPrimAresta();
		void setPrimAresta(Aresta *a);
		Aresta* getUltAresta();
		void setUltAresta(Aresta *a);
		void inserirArestaNo(int id, No* no2, int pesoAresta);

		void imprimirNosAdjacentes();

	private:
		int id;						// Id do No
		int grauSaida;				// Numero de Arestas saindo do No
		int grauEntrada;			// Numero de Arestas que incidem no No
		Grafo* grafo;				// Grafo ao qual o No pertence
		No *proximo;				// Proximo No da lista
		Aresta *primAresta;			// Primeira Aresta ligada ao No da lista
		Aresta *ultAresta;			// Ultima Aresta ligada ao No da lista
};

#endif /* HEADERS_NO_H_ */
