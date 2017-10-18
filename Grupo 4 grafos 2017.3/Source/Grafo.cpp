#include "../Headers/Grafo.h"
#include "../Headers/FileUtils.h"
#include "../Headers/Aresta.h"
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


/**********************************************************
 * Construtores sobrecarregados para criar um Grafo vazio
 * (1o construtor) ou um Grafo com n nos (2o construtor)
 * e destrutor do grafo
 **********************************************************/
Grafo::Grafo()
{
	ordem = 0;
	grau = 0;
	maiorIdNo = 0;
	maiorIdAresta = 0;
	primeiroNo = nullptr;
	ultimoNo = nullptr;
	direcionado = true;
	ehMultigrafo = false;
	cout << "Grafo vazio criado." << endl;
}

Grafo::Grafo(int n)
{
	ordem = 0;
	grau = 0;
	maiorIdNo = 0;
	maiorIdAresta = 0;
	direcionado = true;
	ehMultigrafo = false;
	for(int i = 0; i < n; i++)
		inserirNo();
	cout << "Grafo com " << ordem << " nos criado." << endl;
}

Grafo::~Grafo()
{
	No* p;
	while(primeiroNo != nullptr)
	{
		p = primeiroNo->getProx();
		delete primeiroNo;
		primeiroNo = p;
	}
}

/*********************************************
 * Decrementa a Ordem do Grafo em uma unidade
 *********************************************/
void Grafo::decrementarOrdem()
{
	this->ordem--;
}

/*********************************************
 * Incrementa a Ordem do Grafo em uma unidade
 *********************************************/
void Grafo::incrementarOrdem()
{
	this->ordem++;
}

/*****************************************
 * Retorna o primeiro No do Grafo
 *****************************************/
No* Grafo::getPrimeiroNo()
{
	return primeiroNo;
}

/*********************************
 * Define o primeiro No do Grafo
 *********************************/
void Grafo::setPrimeiroNo(No* no)
{
	this->primeiroNo = no;
}

/*****************************************
 * Retorna o ultimo No do Grafo
 *****************************************/
No* Grafo::getUltimoNo()
{
	return ultimoNo;
}

/*********************************
 * Define o ultimo No do Grafo
 *********************************/
void Grafo::setUltimoNo(No* no)
{
	this->ultimoNo = no;
}

/********************************************************
 * Funcao para inserir um No vazio ao Grafo
 ********************************************************/
void Grafo::inserirNo()
{
	maiorIdNo++;
	inserirNo(maiorIdNo);
}

/****************************************************
 * Insere um novo No no Grafo com o id especificado
 ****************************************************/
void Grafo::inserirNo(int id)
{
	maiorIdNo = maiorIdNo > id ? maiorIdNo : id;
	No *p = new No(id, this);
	if(ordem == 1)
	{
		primeiroNo = p;
		ultimoNo = p;
	}
	else
	{
		ultimoNo->setProx(p);
		ultimoNo = p;
	}
}

/*******************************************
 * Exclui o No com o id informado junto
 * com todas as Arestas relacionadas
 *******************************************/
void Grafo::excluirNo(int idNo)
{
	No* n = primeiroNo;			// Variavel para percorrer a lista de Nos
	No* del = nullptr;			// No a ser deletado

	while(n != nullptr)
	{
		Aresta* a = n->getAresta(idNo);		// Arestas que apontam para o No del
		while(a != nullptr)
		{
			delete a;
			a = n->getAresta(idNo);
		}

		if(n->getId() == idNo)
			del = n;

		n = n->getProx();
	}

	if(del != nullptr)
		delete del;
	else
		cout << "O No de id " << idNo
		        << " nao pode ser excluido, pois nao foi encontrado." << endl;
}

/********************************************************
 * Funcao auxiliar que procura um No usando apenas o id
 * do No
 ********************************************************/
No* Grafo::procurarNo(int idProcurado)
{
	No* p; // ponteiro auxiliar
	p = this->primeiroNo;
	for(int i = 0; i < ordem; i++)
	{
		if(p->getId() == idProcurado)
			return p;
		p = p->getProx();
	}
	cout << "o No " << idProcurado << " nao foi encontrado" << endl; //codigo apenas para identificar erros
	return p;
}

/********************************************************
 * Funcao para inserir Aresta ao grafo. A Aresta sera
 * alocada ao primeiro No do par, que e' referente ao
 * primeiro parametro da funcao
 ********************************************************/
void Grafo::inserirArestaGrafo(int idNo1, int idNo2, int pesoAresta)
{
	No *no1 = procurarNo(idNo1);
	No *no2 = procurarNo(idNo2);
	if (no1->existeAresta(idNo2))
	{
		setEhMultigrafo(true);
	}
	inserirArestaGrafo(no1, no2, pesoAresta);
}

/********************************************************
 * Funcao para inserir Aresta ao grafo. A Aresta sera
 * alocada ao primeiro No do par, que e' referente ao
 * primeiro parametro da funcao
 ********************************************************/
void Grafo::inserirArestaGrafo(No* noOrigem, No* noDestino, int pesoAresta)
{
	if(noOrigem != nullptr && noDestino != nullptr)
	{
		maiorIdAresta++;
		noOrigem->inserirArestaNo(maiorIdAresta, noDestino, pesoAresta);
		int grauNo1 = noOrigem->getGrau();
		if(grauNo1 > this->grau)
			this->grau = grauNo1;

		if(this->ehDirecionado() == false)
		{
			maiorIdAresta++;
			noDestino->inserirArestaNo(maiorIdAresta, noOrigem, pesoAresta);
			int grauNo2 = noDestino->getGrau();
			if(grauNo2 > this->grau)
				this->grau = grauNo2;
		}
	}
}

/*********************************************************
 * Exclui uma Aresta que liga o No de Origem e o No de
 * Destino e tenha o Peso informado. Se houver mais de uma,
 * apenas a primeira encontrada ser� excluida
 *********************************************************/
void Grafo::excluirArestaGrafo(int idNoOrigem, int idNoDestino, int peso)
{
	No* n = procurarNo(idNoOrigem);					// n = noOrigem
	Aresta* a = n->getAresta(idNoDestino, peso);	// a = noOrigem => noDestino
	if(a != nullptr)
		delete a;

	if(this->ehDirecionado())
	{
		n = procurarNo(idNoDestino);		// n = noDestino
		a = n->getAresta(idNoOrigem, peso);	// a = noDestino => noOrigem
		if(a != nullptr)
			delete a;
	}
}

/********************************************
 * Exclui a Aresta que tem o id informado
 ********************************************/
void Grafo::excluirArestaGrafo(int idAresta)
{
	No* n = primeiroNo;
	Aresta* a;
	while(n != nullptr)
	{
		a = n->getPrimAresta();
		while(a != nullptr)
		{
			if(a->getId() == idAresta)
			{
				delete a;
				return;
			}
			a = a->getProx();
		}
		n = n->getProx();
	}
}

/********************************************************
 * Printa as informacoes do Grafo: (posicao da sequencia,
 * id do No, grau do No e as arestas de sua lista)
 * a formatacao deve ser revisada
 ********************************************************/
void Grafo::mostrarGrafo()
{
	No* p = primeiroNo;

	cout << setw(3) << "No" << setw(10) << "ID" << setw(10) << "Grau"
	        << setw(17) << "Nos Adjacentes" << endl;
	for(int i = 0; i < ordem; i++)
	{
		cout << setw(3) << i + 1 << setw(10) << p->getId() << setw(10)
		        << p->getGrau() << setw(17);
		p->mostrarNosAdjacentes();
		cout << endl;
		p = p->getProx();
	}
}

/*********************************************
 * Retorna a ordem do Grafo
 *********************************************/
int Grafo::getOrdem()
{
	return ordem;
}

/********************************************************
 * Retorna true se o Grafo possuir apenas um No
 * ou falso caso possua dois ou mais
 ********************************************************/
bool Grafo::ehTrivial()
{
	return getOrdem() == 1;
}

/********************************************************
 * Retorna true se o Grafo nao possuir Arestas ou false
 * caso possua alguma
 ********************************************************/
bool Grafo::ehNulo()
{
	No *n = this->primeiroNo;
	while(n != nullptr)
	{
		if(n->getPrimAresta() != nullptr)
			return false;
		n = n->getProx();
	}
	return true;
}

/**************************************************
 * Retorna true se todos os Nos do Grafo tiverem
 * tantas Arestas quanto o numero informado
 **************************************************/
bool Grafo::ehKRegular(int k)
{
	No *n = this->primeiroNo;

	for(int i = 0; i < this->getOrdem(); i++)
	{
		if(n->getGrau() != k)
			return false;
		n = n->getProx();
	}

	return true;
}

/********************************************
 * Compara o Grau do primeiro No com todos os
 * outros, verificando se todos sao iguais
 ********************************************/
int Grafo::ehKRegular()
{
	No *n = this->primeiroNo;

	if(n == nullptr)
		return -1;
	int k = n->getGrau();
	n = n->getProx();

	while(n != nullptr)
	{
		if(n->getGrau() == k)
			n = n->getProx();
		else
			return -1;
	}

	return k;

}

/********************************************
 * Verifica se o Grafo eh completo
 ********************************************/
bool Grafo::ehCompleto()
{
	if(this->ehKRegular(this->ordem - 1))
		return true;

	return false;
}

/********************************************
 * Verifica se o Grafo eh ou nao direcionado
 ********************************************/
bool Grafo::ehDirecionado()
{
	return direcionado;
}

/************************************************
 * Define a propriedade do Grafo ser direcionado
 ************************************************/
void Grafo::setEhDirecionado(bool direcionado)
{
	this->direcionado = direcionado;
}

/*********************************************
 * Verifica se foi inserido o peso das Aresta
 * no arquivo de entrada
 *********************************************/
bool Grafo::ehPonderado()
{
	ifstream file(_argv[1]);
	string line;
	getline(file, line); // Le a primeira linha com o numero de Nos
	getline(file, line); // Le a segunda linha para identificar se o Grafo eh ponderado

	stringstream ss(line);
	int i, cont = 0;

	while(ss >> i)
		cont++;

	if(cont == 3)
		return true;

	return false;
}

/*********************************************
 * Exibe a Vizinhanca Aberta do Grafo
 *********************************************/
void Grafo::mostrarVizinhancaAberta(int idNo)
{
	Grafo* g = new Grafo();
	No* noCentral = procurarNo(idNo);
	Aresta* aresta = nullptr;	// Arestas saindo de n
	if(noCentral != nullptr)
	{
		aresta = noCentral->getPrimAresta();
		while(aresta != nullptr)
		{
			int idNoTemp = aresta->getIdNoDestino();
			g->inserirNo(idNoTemp);
			aresta = aresta->getProx();
		}
		adicionarArestasEntreVizinhos(g, noCentral);
		cout << "Vizinhanca Aberta:" << endl;
		g->mostrarGrafo();
	}
	else
		cout << "ERRO. No' nao encontrado" << endl;
}

/*********************************************
 * Exibe a Vizinhanca Fechada do Grafo
 *********************************************/
void Grafo::mostrarVizinhancaFechada(int idNo)
{
	Grafo* g = new Grafo();
	No* noCentral = procurarNo(idNo);
	Aresta* a = nullptr;	// Arestas saindo de n
	if(noCentral != nullptr)
	{
		inserirNo(noCentral->getId());
		a = noCentral->getPrimAresta();
		while(a != nullptr)
		{
			int idNoTemp = a->getIdNoDestino();
			g->inserirNo(idNoTemp);

			g->inserirArestaGrafo(g->primeiroNo, a->getNoDestino(), a->getPeso());
			if(g->ehDirecionado() == false)
				g->inserirArestaGrafo(a->getNoDestino(), g->primeiroNo, a->getPeso());

			a = a->getProx();
		}

		adicionarArestasEntreVizinhos(g, noCentral);
		cout << "Vizinhanca Fechada:" << endl;
		g->mostrarGrafo();
	}
	else
		cout << "ERRO. No' nao encontrado" << endl;
}

/*********************************************************************
 * Funcao auxiliar na exibicao de vizinhanca aberta e fechada do No.
 * Adiciona as Arestas entre os vizinhos do No central
 *********************************************************************/
void Grafo::adicionarArestasEntreVizinhos(Grafo* grafo, No* noCentral)
{
	No* p = nullptr;		// No auxiliar
	Aresta* b = nullptr;	// Arestas saindo dos vizinhos de n
	Aresta* a = noCentral->getPrimAresta();
	No* x = grafo->primeiroNo;
	while(x != nullptr)
	{
		a = noCentral->getPrimAresta();
		while(a != nullptr)
		{
			p = a->getNoDestino();
			b = p->getPrimAresta();
			while(b != nullptr)
			{
				if(b->getIdNoDestino() == x->getId())
				{
					No* n1 = grafo->procurarNo(p->getId());
					grafo->inserirArestaGrafo(n1->getId(), x->getId(), b->getPeso());
					if(grafo->ehDirecionado() == false)
						grafo->inserirArestaGrafo(x->getId(), n1->getId(), b->getPeso());
				}
				b = b->getProx();
			}
			a = a->getProx();
		}
		x = x->getProx();
	}
}

/******************************************
 * Define se o Grafo e' um Multigrafo
 ******************************************/
void Grafo::setEhMultigrafo(bool tf)
{
	ehMultigrafo = tf;
}

/******************************************
 * Verifica se o Grafo e' um Multigrafo
 ******************************************/
bool Grafo::verificaMultigrafo()
{
	return ehMultigrafo;
}

/*********************************************************
 * Copia todos os Nos (com seus IDs) para um novo Grafo,
 * sem levar as Arestas em conta
 *********************************************************/
Grafo* Grafo::copiarNosParaNovoGrafo()
{
	Grafo* g = new Grafo();		// Novo Grafo
	No* n = this->primeiroNo;	// No para iterar no Grafo original

	while(n != nullptr)
	{
		g->inserirNo(n->getId());
		n = n->getProx();
	}

	return g;
}

/*********************************
 * Imprime o Grafo Complementar
 *********************************/
void Grafo::mostrarGrafoComplementar()
{
	Grafo* g = this->copiarNosParaNovoGrafo();
	No* noOriginal = this->primeiroNo;		// No para iterar no Grafo original
	No* novoNoOrigem = g->primeiroNo;		// Usado para manter a referencia do id do No de origem no Novo No
	while(noOriginal != nullptr)
	{
		No* novoNoDestino = g->primeiroNo;		// No para iterar no novo Grafo
		int grauSaidaNo = noOriginal->getGrauSaida();
		int* idsDestinoOriginal = new int[grauSaidaNo];
		Aresta* a = noOriginal->getPrimAresta();
		while(a != nullptr)
		{
			for(int i = 0; i < grauSaidaNo; i++)
			{
				idsDestinoOriginal[i] = a->getIdNoDestino();
				a = a->getProx();
			}
		}

		while(novoNoDestino != nullptr)
		{
			if(grauSaidaNo == 0)
			{
				if((novoNoOrigem != novoNoDestino) && !(novoNoOrigem->existeAresta(novoNoDestino->getId())))
					g->inserirArestaGrafo(novoNoOrigem, novoNoDestino, 1);
			}
			else
			{
				bool noDestinoEstaNoArray = novoNoDestino->existeDentroDoVetor(idsDestinoOriginal, grauSaidaNo);

				if(!(noDestinoEstaNoArray) && (novoNoOrigem != novoNoDestino) && (!novoNoOrigem->existeAresta(novoNoDestino->getId())))
					g->inserirArestaGrafo(novoNoOrigem, novoNoDestino, 1);
			}

			novoNoDestino = novoNoDestino->getProx();
		}

		noOriginal = noOriginal->getProx();
		novoNoOrigem = novoNoOrigem->getProx();
		delete[] idsDestinoOriginal;
	}
	cout << "Grafo Complementar:" << endl;
	g->mostrarGrafo();
}

/************************************************
 * Mostra a sequencia de Graus dos Nos do Grafo
 ************************************************/
void Grafo::mostrarSequenciaDeGraus()
{
	No* n = this->primeiroNo;
	cout << "Sequencia de Graus: ";
	while(n->getProx() != nullptr)
	{
		cout << n->getGrau() << ", ";
		n = n->getProx();
	}
	cout << n->getGrau() << "." << endl;
}

/***********************************************************
 * Mostra o Sub-Grafo induzido pelos Nos de ids informados
 ***********************************************************/
void Grafo::mostrarSubGrafoInduzido(int idsNos[], int qtdNos)
{
	// Ordena o vetor para seguir o padrao de IDs
	int temp;
	for(int i = 0; i < qtdNos; i++)
	{
		for(int j = i + 1; j < qtdNos; j++)
		{
			if(idsNos[i] > idsNos[j])
			{
				temp = idsNos[i];
				idsNos[i] = idsNos[j];
				idsNos[j] = temp;
			}
		}
	}
	// Fim da ordenacao

	Grafo* g = new Grafo();

	// Insere Nos com ids iguais aos do Grafo original
	for(int i = 0; i < qtdNos; i++)
		g->inserirNo(idsNos[i]);

	No* n = this->primeiroNo;

	while(n != nullptr)
	{
		if(!(n->existeDentroDoVetor(idsNos, qtdNos)))
		{
			n = n->getProx();
			continue;
		}

		Aresta* a = n->getPrimAresta();
		while(a != nullptr)
		{
			No* noDestinoOriginal = a->getNoDestino();
			if(noDestinoOriginal->existeDentroDoVetor(idsNos, qtdNos))
			{
				No* noOrigemNovo = g->procurarNo(n->getId());
				No* noDestinoNovo = g->procurarNo(noDestinoOriginal->getId());
				inserirArestaGrafo(noOrigemNovo, noDestinoNovo, a->getPeso());
			}
			a = a->getProx();
		}
		n = n->getProx();
	}

	cout << "Sub-Grafo induzido pelo conjunto de Nos [";
	for (int i = 0; i < (qtdNos - 1); i++)
		cout << idsNos[i] << " - ";
	cout << idsNos[qtdNos - 1] << "]:" << endl;
	g->mostrarGrafo();

}

<<<<<<< HEAD
<<<<<<< HEAD
/***********************************************************
 * Verica a bipartição
 ***********************************************************/
bool Grafo::verificaBipartido()
{
	No* n = this->getPrimeiroNo();			// Variavel para percorrer a lista de Nos
	int vet[this->getOrdem()];
	bool aux;
	for (int i=0; i<this->getOrdem(); i++)
	{
		vet[i] = 0;
	}
	aux = auxVerificaBipartido(1, n, vet);

	return aux;
}
bool Grafo::auxVerificaBipartido(int ver, No* n, int* vet)
{

	for (int i=0; i<this->getOrdem(); i++)
	{
		Aresta* a = n->getAresta(n->getId());
		while(a!= nullptr)
		{
			if(vet[i] == 0 || vet[i] == ver)
			{
				vet[i] = ver;
				if(ver == 1)
				{
					return auxVerificaBipartido(2, n, vet);
				}
				if(ver == 2)
				{
					return auxVerificaBipartido(1, n, vet);
				}
			}
			else
			{
				return false;
			}

			a = a->getProx();
		}

		n = n->getProx();
	}
/***********************************************************
 * Verica se contém ciclo
 *************************************************************/

	bool Grafo::verificaSeContemCiclo(No* n)
	{
		int cont=0;
		while(n!= nullptr)
		{
			if(n->getGrau()>=2)
			{
				cont++;
			}

		}
		if(cont == this->getOrdem())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
=======
>>>>>>> a073f0634a5dc8e7b3bb129c571ad12fd845d6f9
=======
>>>>>>> a073f0634a5dc8e7b3bb129c571ad12fd845d6f9
/******************************************************
 * Retorna true se a primeira Aresta tiver menor Peso
 * que a segunda, e false se o contrario acontecer
 */
bool menorPesoAresta(Aresta *a, Aresta* b)
{
	return a->getPeso() < b->getPeso();
}

/***********************************************
 * Mostra a AGM (Arvore Geradora Minima) do Grafo
 */
void Grafo::mostrarArvoreGeradoraMinima()
{
	typedef struct	// 
	{				// 
		int idNo;	// Struct auxiliar utilizada na inserção de Arestas
		int val;	// 
	} NoAux;		// 

	Grafo* g = new Grafo();
	No* n = this->primeiroNo;
	int ordemGrafo = this->ordem;

	NoAux* vetNosAux = new NoAux[ordemGrafo];	// Vetor auxiliar para marcar os Nos
	int i = 0;
	int idNo;
	Aresta* a;
	vector<Aresta*> vetArestas;		// Vetor com todas as Arestas do Grafo original

	n = this->primeiroNo;
	while(n != nullptr)
	{
		idNo = n->getId();			//
		g->inserirNo(idNo);			// Preenche o vetor auxiliar com todos os Nos
		vetNosAux[i].idNo = idNo;	// do Grafo e marcando seu 'val' com o valor de seu 'id'
		vetNosAux[i].val = idNo;	//

		a = n->getPrimAresta();
		while(a != nullptr)
		{
			vetArestas.push_back(a);	// Preenche o vetor de Arestas
			a = a->getProx();			// com as Arestas do Grafo original
		}
		i++;
		n = n->getProx();
	}

	sort(vetArestas.begin(), vetArestas.end(), menorPesoAresta);	// Ordena as Arestas

	int j, menor, maior, contArestas = 0;							// Variáveis de controle
	int idNoOrigem, idNoDestino, valNoOrigem = 0, valNoDestino = 0;	//

	for(i = 0; contArestas < ordemGrafo - 1; i++)					// Enquanto não houverem (n-1) Arestas no Grafo...
	{
		idNoOrigem = vetArestas[i]->getIdNoOrigem();
		idNoDestino = vetArestas[i]->getIdNoDestino();

		for(j = 0; j < ordemGrafo; j++)						// Percorre todos os Nos
		{
			if(vetNosAux[j].idNo == idNoOrigem)
				valNoOrigem = vetNosAux[j].val;				// Obtém o 'val' do No de Origem da iteração atual
			if(vetNosAux[j].idNo == idNoDestino)
				valNoDestino = vetNosAux[j].val;			// Obtém o 'val' do No de Destino da iteração atual
			if((valNoOrigem != 0) && (valNoDestino != 0))
				break;										// Quando os dois forem não-nulos, sai do loop
		}

		if(valNoOrigem != valNoDestino)		// Se os 'val' de Origem e Destino forem diferentes... (garante a não-formação de ciclos)
		{
			g->inserirArestaGrafo(g->procurarNo(idNoOrigem),
			        g->procurarNo(idNoDestino), vetArestas[i]->getPeso());		// Insere a Aresta
			contArestas++;														// Incrementa o contador
			menor = valNoOrigem < valNoDestino ? valNoOrigem : valNoDestino;
			maior = valNoOrigem > valNoDestino ? valNoOrigem : valNoDestino;

			for(j = 0; j < ordemGrafo; j++)		//
				if(vetNosAux[j].val == maior)	// Normaliza os 'val' dos dois Nos para ser igual ao menor 'val'
					vetNosAux[j].val = menor;	//
		}

		valNoOrigem = valNoDestino = 0;		// Reseta o 'val' dos Nos
	}

	g->mostrarGrafo();

	delete [] vetNosAux;
}
