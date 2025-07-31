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
// Metodo para eliminar un nodo de la grafica
void Grafica::Eliminar(char nom)
{
    Nodo *porBorrar  = BuscarDir(nom);
    if(porBorrar == nullptr) return;

    // actualiza el numero de aristas
    numAristas -= porBorrar->Aislar();

    // actualiza los punteros primero y ultimo si es necesario
    if (porBorrar == primero) primero = porBorrar->siguiente;
    if (porBorrar == ultimo) ultimo = porBorrar->anterior;

    // reconecta los nodos vecinos
    if (porBorrar->anterior != nullptr) porBorrar->anterior->siguiente = porBorrar->siguiente;
    if (porBorrar->siguiente != nullptr) porBorrar->siguiente->anterior = porBorrar->anterior;

    // elimina el nodo y diminuye el numero de nodos
    delete porBorrar;
    numNodos--;
}
//***********************************************************************************

// Metodo para eliminar una arista entre dos nodos
void Grafica::Eliminar(char inicio, char fin)
{
    Nodo *ptrInicio  = BuscarDir(inicio);
    if(ptrInicio == nullptr) return;

    Nodo *ptrFin  = BuscarDir(fin);
    if(ptrFin == nullptr) return;

    ptrInicio->Eliminar(ptrFin); // elimina el fin del inicio
    ptrFin->Eliminar(ptrInicio); // elimina el inicio del fin

    // disminuye el numero de aristas
    numAristas--;
}


//***********************************************************************************

// Metodo para buscar un nodo por su nombre
bool Grafica::Buscar(char nom) const
{
    return BuscarDir(nom) != nullptr;
}
//***********************************************************************************

// Metodo para buscar una arista entre dos nodos
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

// Metodo para obtener el numero de nodos en la grafica
int Grafica::ObtenerNumNodos() const
{
    return numNodos;
}

//***********************************************************************************

// Metodo para obtener el numero de aristas en la grafica
int Grafica::ObtenerNumAristas() const
{
    return numAristas;
}
//***********************************************************************************

// Metodo para obtener el grado de un nodo dado su nombre
int Grafica::ObtenerGrado(char nom) const
{
    Nodo *nodo = BuscarDir(nom);

    if (nodo != nullptr)
        return nodo->grado;

    return 0; // si el nodo no existe, su grado es 0. //excepcion
}
//***********************************************************************************

// Metodo para imprimir toda la grafica
void Grafica::Imprimir() const
{
    Nodo *nodoActual = primero;
    while (nodoActual != nullptr) {
        std::cout << "Nodo: " << nodoActual->nombre << ", Grado: " << nodoActual->grado << std::endl;
        Arista *aristaActual = nodoActual->primera;
        while (aristaActual != nullptr) {
            std::cout << "  -> Arista hacia nodo: " << aristaActual->adyacente->nombre << std::endl;
            aristaActual = aristaActual->siguiente;
        }
        nodoActual = nodoActual->siguiente;
    }
}
//***********************************************************************************

// M�todo para imprimir la informacion de un nodo especifico
void Grafica::Imprimir(char nom) const
{
    Nodo *nodo = BuscarDir(nom);

    if (nodo != nullptr) {
        std::cout << "Nodo: " << nodo->nombre << ", Grado: " << nodo->grado << std::endl;
        Arista *aristaActual = nodo->primera;

        while (aristaActual != nullptr) {
            std::cout << "  -> Arista hacia nodo: " << aristaActual->adyacente->nombre << std::endl;
            aristaActual = aristaActual->siguiente;
        }

    } else {
        std::cout << "El nodo " << nom << " no existe en la grafica." << std::endl;
    }
}
//***********************************************************************************

void Grafica::Vaciar()
{
    while (primero != nullptr) {
        Nodo *temp = primero;
        primero = primero->siguiente;

        // Eliminar todas las aristas del nodo
        while (temp->primera != nullptr) {
            Arista *tempArista = temp->primera;
            temp->primera = temp->primera->siguiente;
            delete tempArista;
        }

        delete temp;
    }

    numNodos = 0;
    numAristas = 0;
}
