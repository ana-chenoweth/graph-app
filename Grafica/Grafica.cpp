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

// M�todo para agregar un nodo a la gr�fica
void Grafica::Agregar(char nom)
{
    // comprueba si el nodo ya est� en la gr�fica
    if(Buscar(nom)) return;

    //crear un nuevo nodo y lo agrega a la gr�fica
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

// M�todo para buscar un nodo por su nombre
bool Grafica::Buscar(char nom) const
{
    return BuscarDir(nom) != nullptr;
}


//***********************************************************************************

// M�todo para buscar la direcci�n de un nodo por su nombre
Grafica::Nodo * Grafica::BuscarDir(char nom) const
{
    Nodo *actual = primero;

    while(actual != nullptr && actual -> nombre != nom){
        actual = actual -> siguiente;
    }

    return actual;
}
