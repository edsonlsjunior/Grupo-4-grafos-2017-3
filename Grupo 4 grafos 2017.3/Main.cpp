#include <iostream>
#include "Headers/Grafo.h"
#include <fstream>

using namespace std;

/********************************************************
 ********************************************************/

int main(int argc, char *argv[])
{
    ifstream myfile;
    myfile.open(argv[1]);
    cout << myfile.is_open();
    int n;
    myfile >> n;
    Grafo g(n);
    /*while(myfile >> no1 >> no2 >> peso)
    {
    }*/
    g.mostrarGrafo();
    return 0;
}
