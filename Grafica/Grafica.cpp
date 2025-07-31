#include <iostream>
#include <limits>

#include "Grafica.hpp"

// Constructor por defecto de la clase Grafica
Grafica::Grafica(): numNodos(0), numAristas(0), primero(nullptr), ultimo(nullptr)
{

}
//***********************************************************************************

// Destructor de la clase Grafica
Grafica::~Grafica()
{
    Vaciar();
}

//***********************************************************************************

// Constructor de copia de la clase Grafica
Grafica::Grafica(const Grafica &g): numNodos(0), numAristas(0), primero(nullptr), ultimo(nullptr)
{
    *this = g;
}
