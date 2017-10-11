#ifndef HEADERS_GRAFO_H_
#define HEADERS_GRAFO_H_

#include <iostream>
#include "No.h"

using namespace std;

class Grafo
{
	public:
		Grafo();
		Grafo(int n);
		~Grafo();
		void inserirNo();
		void inserirArestaGrafo(int idNo1, int idNo2, int pesoAresta);
		void mostrarGrafo();
		No *procurarNo(int idProcurado);
		int getOrdem();
		bool ehTrivial();
		bool ehNulo();

	private:
		//atributos do grafo
		int contId;
		int ordem;              //numero de nos no grafo
		int grau;
		No *primeiro;           //primeiro no inserido ao grafo
		No *ultimo;				//ponteiro para falictar insercao de nos
};

#endif /* HEADERS_GRAFO_H_ */
