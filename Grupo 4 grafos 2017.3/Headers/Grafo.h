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
		void excluirArestaGrafo(int idNoOrigem, int idNoDestino, int peso);
		void excluirArestaGrafo(int idAresta);

		void mostrarGrafo();
		No *procurarNo(int idProcurado);
		int getOrdem();
		bool ehTrivial();
		bool ehNulo();
		bool ehKRegular(int k);
		void ehKRegular();
		bool ehDirecionado();
		bool setEhDirecionado(bool direcionado);
        bool ehCompleto();
        bool ehPonderado(); //verifica se foi inserido o peso das aresta no arquivo de entrada

	private:
		//atributos do grafo
<<<<<<< HEAD
		int contId;
		int ordem;              //numero de nos no grafo
		int grau;				//Não está funcionando
		No *primeiro;           //primeiro no inserido ao grafo
		No *ultimo;				//ponteiro para falictar insercao de nos
		bool direcionado;
=======
		int maiorIdNo;				// Id do ultimo No inserido no Grafo
		int maiorIdAresta;			// Id da ultima Aresta inserida no Grafo
		int ordem;              	// numero de nos no Grafo
		int grau;
		No *primeiroNo;         	// primeiro No inserido ao Grafo
		No *ultimoNo;				// ponteiro para facilitar insercao de Nos
>>>>>>> ff90f54b5ace50a4ee21f04506552b56fbf0797f
};

#endif /* HEADERS_GRAFO_H_ */
