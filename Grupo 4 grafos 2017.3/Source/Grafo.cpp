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
	cout << "Grafo vazio criado." << endl;
}

Grafo::Grafo(int n)
{
	ordem = 0;
	grau = 0;
	maiorIdNo = 0;
	maiorIdAresta = 0;
	direcionado = true;
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
	No* n = primeiroNo;					// Variavel para percorrer a lista de Nos
	No* del = nullptr; 					// No a ser deletado

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
	if(no1 != nullptr && no2 != nullptr)
	{
		maiorIdAresta++;
		no1->inserirArestaNo(maiorIdAresta, no2, pesoAresta);
		int grauNo1 = no1->getGrau();
		if(grauNo1 > this->grau)
			this->grau = grauNo1;

		if(this->ehDirecionado() == false)
		{
			maiorIdAresta++;
			no2->inserirArestaNo(maiorIdAresta, no1, pesoAresta);
			int grauNo2 = no2->getGrau();
			if(grauNo2 > this->grau)
				this->grau = grauNo2;
		}
	}
}

/*********************************************************
 * Exclui uma Aresta que liga o No de Origem e o No de
 * Destino e tenha o Peso informado
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

