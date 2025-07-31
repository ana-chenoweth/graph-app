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
// M�todo para eliminar un nodo de la gr�fica
void Grafica::Eliminar(char nom)
{
    Nodo *porBorrar  = BuscarDir(nom);
    if(porBorrar == nullptr) return;

    // actualiza el n�mero de aristas
    numAristas -= porBorrar->Aislar();

    // actualiza los punteros primero y �ltimo si es necesario
    if (porBorrar == primero) primero = porBorrar->siguiente;
    if (porBorrar == ultimo) ultimo = porBorrar->anterior;

    // reconecta los nodos vecinos
    if (porBorrar->anterior != nullptr) porBorrar->anterior->siguiente = porBorrar->siguiente;
    if (porBorrar->siguiente != nullptr) porBorrar->siguiente->anterior = porBorrar->anterior;

    // elimina el nodo y diminuye el n�mero de nodos
    delete porBorrar;
    numNodos--;
}
//***********************************************************************************

// M�todo para eliminar una arista entre dos nodos
void Grafica::Eliminar(char inicio, char fin)
{
    Nodo *ptrInicio  = BuscarDir(inicio);
    if(ptrInicio == nullptr) return;

    Nodo *ptrFin  = BuscarDir(fin);
    if(ptrFin == nullptr) return;

    ptrInicio->Eliminar(ptrFin); // elimina el fin del inicio
    ptrFin->Eliminar(ptrInicio); // elimina el inicio del fin

    // disminuye el n�mero de aristas
    numAristas--;
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

//***********************************************************************************

// M�todo para obtener el n�mero de nodos en la gr�fica
int Grafica::ObtenerNumNodos() const
{
    return numNodos;
}

//***********************************************************************************

// M�todo para obtener el n�mero de aristas en la gr�fica
int Grafica::ObtenerNumAristas() const
{
    return numAristas;
}