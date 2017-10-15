#include "../Headers/Grafo.h"
#include "../Headers/FileUtils.h"
#include "../Headers/Aresta.h"
#include <iomanip>
#include <sstream>

using std::cout;
using std::setw;

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
	No *p = new No(maiorIdNo, this);
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
 * apenas a primeira encontrada será excluida
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
		p->imprimirNosAdjacentes();
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
	No* p = nullptr;		// No auxiliar
	Aresta* aresta = nullptr;	// Arestas saindo de n
	if(noCentral != nullptr)
	{
		aresta = noCentral->getPrimAresta();
		while(aresta != nullptr)
		{
			int idNoTemp = aresta->getIdNoDestino();
			p = new No(idNoTemp, g);
			if(g->ordem == 1)
			{
				g->primeiroNo = p;
				g->ultimoNo = p;
			}
			else
			{
				g->ultimoNo->setProx(p);
				g->ultimoNo = p;
			}
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
	No* p = nullptr;		// No auxiliar
	Aresta* a = nullptr;	// Arestas saindo de n
	if(noCentral != nullptr)
	{
		g->ultimoNo = g->primeiroNo = new No(noCentral->getId(), g);
		a = noCentral->getPrimAresta();
		while(a != nullptr)
		{
			int idNoTemp = a->getIdNoDestino();
			p = new No(idNoTemp, g);
			g->ultimoNo->setProx(p);
			g->ultimoNo = p;

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
	No* p = nullptr;			// No para iterar no novo Grafo

	if(n != nullptr)
	{
		p = new No(n->getId(), g);
		g->ultimoNo = g->primeiroNo = p;
		n = n->getProx();
	}

	while(n != nullptr)
	{
		p = new No(n->getId(), g);
		g->ultimoNo->setProx(p);
		g->ultimoNo = p;
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
		int *idsDestinoOriginal = new int[grauSaidaNo];
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
				if((novoNoOrigem != novoNoDestino)
				        && !(novoNoOrigem->existeAresta(novoNoDestino->getId())))
					g->inserirArestaGrafo(novoNoOrigem, novoNoDestino, 1);
			}
			else
			{
				bool noDestinoEstaNoArray = false;

				// Checando se o novo No de Destino esta na lista de Nos Adjacentes do No Original
				for(int i = 0; i < grauSaidaNo; i++)
					if(novoNoDestino->getId() == idsDestinoOriginal[i])
						noDestinoEstaNoArray = true;

				if(!(noDestinoEstaNoArray) && (novoNoOrigem != novoNoDestino) && (!novoNoOrigem->existeAresta(novoNoDestino->getId())))
						g->inserirArestaGrafo(novoNoOrigem, novoNoDestino, 1);
			}

			novoNoDestino = novoNoDestino->getProx();
		}

		noOriginal = noOriginal->getProx();
		novoNoOrigem = novoNoOrigem->getProx();
		delete[] idsDestinoOriginal;
	}
	g->mostrarGrafo();
}

