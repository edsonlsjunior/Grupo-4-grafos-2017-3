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
        grafo->setEhDirecionado(1);
		grafo->mostrarGrafo();
//		grafo->ehKRegular();
//		cout << "O grafo e 3 regular? " << grafo->ehKRegular(3) << endl;
//        cout << "O grafo e completo? " << grafo->ehCompleto() << endl;
//        cout << "O grafo e ponderado? " << grafo->ehPonderado() << endl;
//        cout << "O grafo eh k-reuglar? " << grafo->ehKRegular() << endl;
		grafo->excluirArestaGrafo(7);
		grafo->mostrarGrafo();
		//f.salvarGrafo(grafo);
	}
	else
		cout << "Formato invalido!";

	return 0;
}
