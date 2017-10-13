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
 * parâmetro para o programa
 ************************************************************/
Grafo* FileUtils::retornarGrafo()
{
	ifstream leitor;
	leitor.open(argv[1]);
	int n, no1, no2, peso;
	leitor >> n;
	Grafo *g = new Grafo(n);
	while(leitor >> no1 >> no2 >> peso)
	{
		g->inserirArestaGrafo(no1, no2, peso);
	}
	leitor.close();
	return g;

//	ifstream leitor;
//	leitor.open(argv[1]);
//	string n;
//	int no1, no2, peso;
//	getline(leitor, n);
//	Grafo *g = new Grafo(stoi(n));
//
//	string line;
//	getline(leitor, line);
//	stringstream ss(line);
//	int contParametros = 0, i;
//
//	while(ss >> i)
//		contParametros++;
//
//	if(contParametros == 3)
//	{
//			while(leitor >> no1 >> no2 >> peso)
//			{
//				cout << no1 << " " << no2 << " " << peso << endl;
//				g->inserirArestaGrafo(no1, no2, peso);
//			}
//	}
//
//	return g;
}

void FileUtils::salvarGrafo(Grafo *g) //incompleto porque ainda nao ha forma de pegar as informacoes do grafo
{
	ofstream leitor;
	leitor.open(argv[2]);
	leitor << g->getOrdem();
	for(int i = g->getOrdem(); i > 0; i--)
	{
		leitor << "\n";
		leitor << i << " " << i + 2 << " " << i - 3;
	}
}
