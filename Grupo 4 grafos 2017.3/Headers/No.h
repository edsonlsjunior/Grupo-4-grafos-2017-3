#ifndef HEADERS_NO_H_
#define HEADERS_NO_H_

#include <iostream>

using namespace std;

class Aresta;
class No
{
    public:
        No(int id);
        ~No();
        void setProx(No *proxNo);
        No* getProx();
        int getId();
        void inserirArestaNo(No* no2,int pesoAresta);
    private:
        int id;
        No *proximo;
        Aresta *primAresta;
        Aresta *ultAresta;
};



#endif /* HEADERS_NO_H_ */
