#include <iostream>
#include "Headers/Grafo.h"
#include "Headers/FileUtils.h"

using namespace std;

int main(int argc, char **argv)
{
	FileUtils* leitor = new FileUtils(argv);
	Grafo* g = leitor->retornarGrafo();
	cout << "\nArquivo lido com sucesso" << endl;
	int escolha = 1;

	while(escolha != 0)
	{
		cout << "\nEscolha uma opcao*****************************" << endl;
		cout << "1 - Leitura do arquivo" << endl;
		cout << "2 - Escrever grafo em arquivo" << endl;
		cout << "3 - Inserir ou excluir no ou aresta" << endl;
		cout << "4 - Imprimir grau do no" << endl;
		cout << "5 - Verificar k - regularidade" << endl;
		cout << "6 - Imprimir ordem do grafo" << endl;
		cout << "7 - Informar se o grafo eh trivial" << endl;
		cout << "8 - Informar se o grafo eh nulo" << endl;
		cout << "9 - Mostrar vizinhança aberta de um no" << endl;
		cout << "10 - Mostrar vizinhança fechada de um no" << endl;
		cout << "11 - Verificar se o grafo eh multigrafo" << endl;
		cout << "12 - Verificar se o grafo eh completo" << endl;
		cout << "13 - Verificar se o grafo eh bipartido" << endl;
		cout << "14 - Caminho minimo e custo entre dois vertices" << endl;
		cout << "15 - Imprimir grau do grafo" << endl;
		cout << "16 - Apresentar sequencia de graus" << endl;
		cout << "17 - Apresentar o subgrafo induzido por um dado conjunto de vértices" << endl;
		cout << "18 - Apresentar o complementar do grafo" << endl;
		cout << "19 - Verificar se o grafo eh Euleriano" << endl;
		cout << "20 - Apresentar os nos de articulacao" << endl;
		cout << "21 - Apresentar as arestas ponte" << endl;
		cout << "22 - Apresentar a AGM" << endl;
		cout << "23 - Apresentar o raio, o diâmetro, o centro e\na periferia do grafo" << endl;
		cout << "24 - Apresentar as Componentes Conexas" << endl;
		cout << "0 - Sair" << endl;
		printf("\n");
		cin >> escolha;
//        switch (escolha)
//        {
//            case 1:
//
//		}
	}
	if(argc == 3)   //precisa configurar o arg na IDE pra funcionar
	{
		FileUtils f(argv);
		Grafo *grafo = f.retornarGrafo();
		grafo->mostrarGrafo();
		grafo->mostrarGrafoComplementar();
		//f.salvarGrafo(grafo);
		grafo->arestasPonte();
	}
	else
		cout << "Formato invalido!";
	return 0;
}
