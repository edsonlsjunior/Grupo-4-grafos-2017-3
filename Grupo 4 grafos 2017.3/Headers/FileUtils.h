//
// Created by edson on 01/09/2017.
//

#ifndef GRUPO_4_GRAFOS_2017_3_FILEUTILS_H
#define GRUPO_4_GRAFOS_2017_3_FILEUTILS_H

#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

class FileUtils
{
public:
    FileUtils (char **argv);
    Grafo* retornarGrafo ();
    void salvarGrafo (Grafo *g);
private:
    char **argv;
};


#endif //GRUPO_4_GRAFOS_2017_3_FILEUTILS_H
