#ifndef HEADERS_GRAFO_H_
#define HEADERS_GRAFO_H_

#include <iostream>
#include "No.h"
#include "Aresta.h"

using namespace std;

class No;

class Grafo
{
	public:
		// Funcoes relacionadas ao Grafo
		Grafo(bool direcionado);
		Grafo(int n, bool direcionado);
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
		void setEhMultigrafo(bool tf);
		bool ehCompleto();
		bool ehPonderado();
		void mostrarVizinhancaAberta(int idNo);
		void mostrarVizinhancaFechada(int idNo);
		void adicionarArestasEntreVizinhos(Grafo* grafo, No* noCentral);
		Grafo* copiarNosParaNovoGrafo();
		bool verificaMultigrafo();
		void mostrarGrafoComplementar();
		Grafo* retornarGrafoComplementar();
		void mostrarSequenciaDeGraus();
		void mostrarSubGrafoInduzido(int idsNos[], int qtdNos);
		bool verificaBipartido();
		bool auxVerificaBipartido(int ver, No* n, int* vet);
		bool verificaSeContemCiclo(No* n);
		void mostrarArvoreGeradoraMinima();
		int componentesConexas();
		void auxComponentesConexas(No* no);
		bool ehEuleriano();
		void mostrarArvoreDeBuscaEmProfundidade(int idNo);
		Grafo* fechoTransitivoIndireto(int idNo);
		Grafo* fechoTransitivoDireto(int idNo);
		void fechoTransitivoIndiretoAux(int idNo, Grafo* fechoIndireto, Grafo* grafoInverso);
		void fechoTransitivoDiretoAux(int idNo, Grafo* fechoDireto);

		// Funcoes relacionadas a Nos
		void inserirNo();
		void inserirNo(int id);
		No *procurarNo(int idProcurado);
		void excluirNo(int idNo);
		No* getPrimeiroNo();
		void setPrimeiroNo(No* no);
		No* getUltimoNo();
		void setUltimoNo(No* no);

		// Funcoes relacionadas a Arestas
		void inserirArestaGrafo(No* noOrigem, No* noDestino, int pesoAresta);
		void inserirArestaGrafo(int idNo1, int idNo2, int pesoAresta);
		void excluirArestaGrafo(int idNoOrigem, int idNoDestino, int peso);
		void excluirArestaGrafo(int idAresta);

	private:
		bool ehMultigrafo;		// Informa se e' multigrafo ou nao, e' verificado na funcao "Utils.retornarGrafo"
		int ordem;              // Numero de nos no Grafo
		int grau;					// Grau do Grafo ( em Grafos Direcionados, e' o maior (grauEntrada + grauSaida) entre os Nos )
		bool direcionado;			// Informa se o Grafo e' direcionado
		int maiorIdNo;				// Id do ultimo No inserido no Grafo
		int maiorIdAresta;		// Id da ultima Aresta inserida no Grafo
		No* primeiroNo;         // Primeiro No inserido ao Grafo
		No* ultimoNo;				// Ponteiro para facilitar insercao de Nos

		void auxMostrarArvoreDeBuscaEmProfundidade(No* no);
};

#endif /* HEADERS_GRAFO_H_ */
