#include <iostream>
#include "Headers/Grafo.h"
#include "Headers/FileUtils.h"

using namespace std;

/********************************************************
 ********************************************************/

int main(int argc, char **argv)
{
	if(argc == 3)   //precisa configurar o arg na IDE pra funcionar
	{
		FileUtils f(argv);
		Grafo *grafo = f.retornarGrafo();
		grafo->mostrarGrafo();
		grafo->mostrarGrafoComplementar();
		//f.salvarGrafo(grafo);
		grafo->nosDeArticulacao();
	}
	else
		cout << "Formato invalido!";
	return 0;
}
