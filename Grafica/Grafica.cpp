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
//***********************************************************************************

// Metodo para agregar un nodo a la grafica
void Grafica::Agregar(char nom)
{
    // comprueba si el nodo ya esta en la grafica
    if(Buscar(nom)) return;

    //crear un nuevo nodo y lo agrega a la grafica
    Nodo *nuevoNodo = new Nodo(nom);
    if (primero == nullptr) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
    } else {
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        ultimo = nuevoNodo;
    }
    numNodos++;
}
//***********************************************************************************

// Metodo para agregar una arista entre dos nodos
void Grafica::Agregar(char inicio, char fin, int peso)
{
    // Obtiene los punteros a los nodos correspondientes a los nombres inicio y fin
    Nodo *ptrInicio = BuscarDir(inicio);
    if(ptrInicio == nullptr) return;    // nodo inicio no esta

    Nodo *ptrFin = BuscarDir(fin);
    if(ptrFin == nullptr) return;    // nodo fin no esta

    // comprueba si la arista ya existe
    if(Buscar(inicio, fin)) return;

    // crea las aristas y las agrega a los nodos
    ptrInicio->Agregar(ptrFin, peso);
    ptrFin->Agregar(ptrInicio, peso);

    // aumenta el numero de aristas
    numAristas++;
}

//***********************************************************************************

// Metodo para buscar un nodo por su nombre
bool Grafica::Buscar(char nom) const
{
    return BuscarDir(nom) != nullptr;
}
//***********************************************************************************

// M�todo para buscar una arista entre dos nodos
bool Grafica::Buscar(char inicio, char fin) const
{
    Nodo *ptrInicio = BuscarDir(inicio);
    Nodo *ptrFin = BuscarDir(fin);

    if (ptrInicio == nullptr || ptrFin == nullptr)
        return false;

    Arista *aristaActual = ptrInicio->primera;

    while (aristaActual != nullptr) {
        if (aristaActual->adyacente->nombre == fin)
            return true;

        aristaActual = aristaActual->siguiente;
    }
    return false;
}

//***********************************************************************************

// Metodo para buscar la direccion de un nodo por su nombre
Grafica::Nodo * Grafica::BuscarDir(char nom) const
{
    Nodo *actual = primero;

    while(actual != nullptr && actual -> nombre != nom){
        actual = actual -> siguiente;
    }

    return actual;
}
