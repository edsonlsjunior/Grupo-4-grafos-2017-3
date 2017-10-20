#include <iostream>
#include "Headers/Grafo.h"
#include "Headers/FileUtils.h"

using namespace std;


int main(int argc, char **argv)
{
	if(argc == 3)   //precisa configurar o arg na IDE pra funcionar
	{
		FileUtils f(argv);
		Grafo *grafo = f.retornarGrafo();
		grafo->arestasPonte();
        cout << "\nArquivo lido com sucesso" << endl;
        int escolha = -1;
        int id1, id2;
        int *vetor;
        float peso;
        bool boolean;
        while(escolha!=0) {
            cout << "\nEscolha uma opcao*****************************" << endl;
            cout << "1-Inserir Aresta" << endl;
            cout << "2-Excluir Aresta" << endl;
            cout << "3-Imprimir grau do no" << endl;
            cout << "4-Verificar k-regularidade" << endl;
            cout << "5-Imprimir ordem do grafo" << endl;
            cout << "6-Informar se o grafo eh trivial" << endl;
            cout << "7-Informar se o grafo eh nulo" << endl;
            cout << "8-Mostrar vizinhança aberta de um no" << endl;
            cout << "9-Mostrar vizinhança fechada de um no" << endl;
            cout << "10-Verificar se o grafo eh multigrafo" << endl;
            cout << "11-Verificar se o grafo eh completo" << endl;
            cout << "12-Verificar se o grafo eh bipartido" << endl;
            cout << "13-Caminho minimo e custo entre dois vertices" << endl;
            cout << "14-Imprimir grau do grafo" << endl;
            cout << "15-Apresentar sequencia de graus" << endl;
            cout << "16-Apresentar o subgrafo induzido por um dado conjunto de vértices" << endl;
            cout << "17-Apresentar o complementar do grafo" << endl;
            cout << "18-Verificar se o grafo eh Euleriano" << endl;
            cout << "19-Apresentar os nos de articulacao" << endl;
            cout << "20-Apresentar as arestas ponte" << endl;
            cout << "21-Apresentar a AGM" << endl;
            cout << "22-Apresentar o raio, o diâmetro, o centro e a periferia do grafo" << endl;
            cout << "23-Apresentar as Componentes Conexas" << endl;
            cout << "24-Salvar o grafo" << endl;
            cout << "0-Sair" << endl;
            cout << "\n";
            cin >> escolha;
            switch (escolha) {
                case 1:cout << "Digite os ids, e o peso respectivamente: ";
                            cin >> id1>> id2;
                            cin >>peso;
                    grafo->inserirArestaGrafo(id1,id2,peso);break;
                case 2:cout << "Digite os ids, e o peso respectivamente para excluir: ";
                    cin >> id1>> id2;
                    cin >>peso;
                    grafo->excluirArestaGrafo(id1,id2,peso);
                case 3: cout << "Digite o id do no: ";
                    cin >>id1;
                    cout << grafo->procurarNo(id1)->getGrau() << endl; break;
                case 4: cout << "K-Regularidade : " << grafo->ehKRegular() << endl;break;
                case 5: cout << "Ordem do grafo: " << grafo->getOrdem() << endl;break;
                case 6: cout << "Grafo eh trivial: " << grafo->ehTrivial() << endl;break;
                case 7: cout << "Grafo eh nulo: " << grafo->ehNulo() << endl;break;
                case 8: cout << "Digite o id do no: ";
                    cin >> id1; grafo->mostrarVizinhancaAberta(id1); cout << endl; break;
                case 9: cout << "Digite o id do no: ";
                    cin >> id1; grafo->mostrarVizinhancaFechada(id1); cout << endl; break;
                case 10: cout << "Eh multigrafo: " << grafo->verificaMultigrafo();break;
                case 11: cout << "Grafo eh completo: " << grafo->ehCompleto();break;
                case 12: cout << "Grafo eh bipartido: " << grafo->verificaBipartido();break;
                case 13: cout << "Digite os nos desejados e 1 para floyd e 0 para dijkstra respectivamente: ";
                    cin >> id1 >> id2; cin >> boolean; grafo->caminhoMinimo(id1, id2, boolean);break;
                case 14: cout << "Grau do grafo: " ; //<< grafo->getGrau();break;
                case 15: grafo->mostrarSequenciaDeGraus(); break;
                case 16: "digite o numero de nos: "; cin >>id1;
                    vetor= new int(id1);
                    cout << "digite os nos: ";
                    for (int i = 0; i < id1; i++)
                    {
                        cin >>id2;
                        vetor[i] = id2;
                    }
                    grafo->mostrarSubGrafoInduzido(vetor, id1);
                case 17: grafo->mostrarGrafoComplementar();break;
                case 18: cout << "Eh euleriano: " << grafo->ehEuleriano();break;
                case 19: grafo->nosDeArticulacao();break;
                case 20: grafo->arestasPonte();break;
                case 21: grafo->mostrarArvoreGeradoraMinima();break;
                case 22: grafo->dadosDeExcentricidade();break;
                case 23: ;break;
                default: cout << "numero invalido! " << endl;
            }
        }
	}
	else
		cout << "Formato invalido!";
	return 0;
}
