#include <iostream>
#include "Headers/Grafo.h"
#include <fstream>

using namespace std;

/********************************************************
 ********************************************************/

int main(int argc, char *argv[])
{
    ifstream myfile;
    myfile.open(argv[1]);           //precisa configurar o arg na IDE pra funcionar o "myfile >> n"
    cout << myfile.is_open();
    int n, no1, no2, peso;
    myfile >> n;
    Grafo g(n);
    while(myfile >> no1 >> no2 >> peso)
    {
        g.inserirArestaGrafo(no1, no2, peso);
    }
    g.mostrarGrafo();

    cout << "Teste" << endl;
    return 0;
}