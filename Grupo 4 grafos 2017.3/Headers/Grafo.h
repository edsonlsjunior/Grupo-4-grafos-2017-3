#ifndef HEADERS_GRAFO_H_
#define HEADERS_GRAFO_H_

#include <iostream>
#include "No.h"

using namespace std;

class No;

class Grafo
{
	public:
		Grafo();
		Grafo(int n);
		~Grafo();
		void decrementarOrdem();
		void incrementarOrdem();
		void mostrarGrafo();
		int getOrdem();
		bool ehTrivial();
		bool ehNulo();
		bool ehKRegular(int k);
		int ehKRegular();
		bool ehDirecionado();
		void setEhDirecionado(bool direcionado);
		bool ehCompleto();
		bool ehPonderado();
		void mostrarVizinhancaAberta(int idNo);
		void mostrarVizinhancaFechada(int idNo);
		void adicionarArestasEntreVizinhos(Grafo* grafo, No* noCentral);

		void inserirNo();
		No *procurarNo(int idProcurado);
		void excluirNo(int idNo);
		No* getPrimeiroNo();
		void setPrimeiroNo(No* no);
		No* getUltimoNo();
		void setUltimoNo(No* no);

		void inserirArestaGrafo(No* noOrigem, No* noDestino, int pesoAresta);
		void inserirArestaGrafo(int idNo1, int idNo2, int pesoAresta);
		void excluirArestaGrafo(int idNoOrigem, int idNoDestino, int peso);
		void excluirArestaGrafo(int idAresta);

	private:
		int ordem;              	// Numero de nos no Grafo
		int grau;					// Grau do Grafo ( em Grafos Direcionados, e' o maior (grauEntrada + grauSaida) entre os Nos )
		bool direcionado;			// Informa se o Grafo e' direcionado
		int maiorIdNo;				// Id do ultimo No inserido no Grafo
		int maiorIdAresta;			// Id da ultima Aresta inserida no Grafo
		No *primeiroNo;         	// Primeiro No inserido ao Grafo
		No *ultimoNo;				// Ponteiro para facilitar insercao de Nos
};

#endif /* HEADERS_GRAFO_H_ */
