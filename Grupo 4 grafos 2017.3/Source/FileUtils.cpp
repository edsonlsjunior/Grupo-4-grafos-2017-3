//
// Created by edson on 01/09/2017.
//

#include "../Headers/FileUtils.h"
#include <sstream>

using namespace std;

FileUtils::FileUtils(char **argv)
{
	this->argv = argv;
}

/************************************************************
 * Retorna um Grafo de um arquivo .txt passado como
 * parametro para o programa
 ************************************************************/
Grafo* FileUtils::retornarGrafo()
{
	ifstream leitor;
	leitor.open(argv[1]);
	int n, no1, no2, peso;
	leitor >> n;
	Grafo *g = new Grafo(n, false);
	g->setEhMultigrafo(false);

	if(g->ehPonderado())
		while(leitor >> no1 >> no2 >> peso)
			g->inserirArestaGrafo(no1, no2, peso);
	else
		while(leitor >> no1 >> no2)
			g->inserirArestaGrafo(no1, no2, 1);

	leitor.close();
	return g;
}

/*********************************************
 * Salva o Grafo num arquivo .txt passado
 * como parâmetro para a aplicação
 *********************************************/
void FileUtils::salvarGrafo(Grafo *g)
{
	ofstream leitor;
	leitor.open(argv[2]);
	leitor << g->getOrdem();

	No* n = g->getPrimeiroNo();
	while(n != nullptr)
	{
		Aresta* a = n->getPrimAresta();
		while(a != nullptr)
		{
			leitor << "\n";
			leitor << n->getId() << " " << a->getIdNoDestino() << " " << a->getPeso();
			a = a->getProx();
		}
		n = n->getProx();
	}
}
