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

// Metodo para imprimir la informacion de un nodo especifico
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
//***********************************************************************************

// Metodo para vaciar un nodo y aislarlo
void Grafica::Vaciar(char nom)
{
    Nodo *nodo = BuscarDir(nom);
    if (nodo != nullptr) {
        numAristas -= nodo->Aislar();

        if (nodo == primero)
            primero = nodo->siguiente;

        if (nodo == ultimo)
            ultimo = nodo->anterior;

        delete nodo;
        numNodos--;
    }
}
//***********************************************************************************

// Metodo para verificar si la grafica esta vacia
bool Grafica::EstaVacia() const
{
    return numNodos == 0;
}

//***********************************************************************************

// Implementacion de la estructura interna Nodo
Grafica::Nodo::Nodo(char nom, Nodo *sig, Nodo *ant) : nombre(nom), grado(0), marca(false),
                    primera(nullptr), ultima(nullptr), siguiente(sig), anterior(ant)
{

}

//***********************************************************************************

// Implementacion de la estructura interna Arista
Grafica::Arista::Arista(Nodo *ady, int peso, Arista *sig, Arista *ant, bool marca) : adyacente(ady),
                        peso(peso), siguiente(sig), anterior(ant), marca(marca)
{

}
//***********************************************************************************
// Metodo para agregar una arista a un nodo
void Grafica::Nodo::Agregar(Nodo *ady, int peso)
{
    Arista *nueva = new Arista(ady, peso);
    (EstaAislado() ? primera : ultima->siguiente) = nueva;
    ultima = nueva;
    ++grado;
    Arista *aristaAdyacente = ady->BuscarDir(this); // Busca la arista que conecta al nodo adyacente con el actual
    if (aristaAdyacente) {
        aristaAdyacente->peso = peso; // Actualiza el peso de la arista en el nodo adyacente
    } else {
        ady->Agregar(this, peso); // Si no existe la arista en el nodo adyacente, agregala con el mismo peso
    }
}
//***********************************************************************************

// Metodo para eliminar una arista de un nodo
void Grafica::Nodo::Eliminar(Nodo *ady)
{
    Arista *porBorrar = BuscarDir(ady);
    if(porBorrar == nullptr) return;

    (porBorrar == primera ? primera : porBorrar->anterior->siguiente) = porBorrar->siguiente;
    (porBorrar == ultima ? ultima : porBorrar->siguiente->anterior) = porBorrar->anterior;

    delete porBorrar;
    --grado;
}
//***********************************************************************************

// Metodo para buscar la direccion de una arista por el nodo adyacente
Grafica::Arista * Grafica::Nodo::BuscarDir(Nodo *ady) const
{
    Arista *actual = primera;

    while (actual != nullptr && actual->adyacente != ady)
        actual = actual->siguiente;

    return actual;
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

// Metodo para verificar si un nodo esta aislado (sin aristas)
bool Grafica::Nodo::EstaAislado() const
{
    return grado == 0;
}
//***********************************************************************************

// Metodo para aislar un nodo eliminando todas sus aristas y devolviendo su grado previo
int Grafica::Nodo::Aislar()
{
    int numAristas = grado;
    while(!EstaAislado()){
        primera->adyacente->Eliminar(this);
        Eliminar(primera->adyacente);
    }
    return numAristas;
}
//***********************************************************************************
//********************************* METODOS DE PRIM *********************************
//***********************************************************************************

// MEtodo para marcar un nodo
void Grafica::MarcarNodo(char nom)
{
    Nodo *nodo = BuscarDir(nom);

    if (nodo != nullptr) {
        nodo->marca = true;
    }
}
//***********************************************************************************

//MEtodo para marcar la arista
void Grafica::MarcarArista(char inicio, char fin)
{
    // Verificar si la arista existe entre los nodos inicio y fin
    if (!Buscar(inicio, fin)) {
        std::cout << "No se encontr/242 la arista correspondiente entre los nodos " << inicio << " y " << fin << std::endl;
        return; //excepcion
    }

    // Encontrar el nodo correspondiente al nombre de inicio
    Nodo* nodoInicio = BuscarDir(inicio);

    if (nodoInicio == nullptr) {
        std::cout << "El nodo " << inicio << " no existe en la grafica." << std::endl;
        return; //excepcion
    }

    // Buscar la arista que conecta el nodo de inicio con el nodo de fin
    Arista* arista = nodoInicio->BuscarDir(BuscarDir(fin));

    if (arista == nullptr) {
        std::cout << "No se encontro la arista entre los nodos " << inicio << " y " << fin << std::endl;
        return; //excepcion
    }

    // Marcar la arista
    arista->marca = true;
}
//***********************************************************************************

// Metodo para obtener la arista minima de un vertice
Grafica::Arista* Grafica::ObtenerAristaMinima(char nombreVertice)
{
    // Buscar el nodo correspondiente al nombre dado
    Nodo* nodo = BuscarDir(nombreVertice);

    if (nodo == nullptr) {
        std::cout << "El vertice " << nombreVertice << " no existe en la grafica." << std::endl;
        return nullptr; //excepcion
    }

    // Inicializar la arista minima como nula y el peso minimo como el maximo posible
    Arista* aristaMinima = nullptr;
    int pesoMinimo = std::numeric_limits<int>::max();

    // Iterar sobre todas las aristas del vertice y encontrar la arista con el menor peso
    Arista* aristaActual = nodo->primera;

    while (aristaActual != nullptr) {
        // Verificar si la arista lleva a un nodo no marcado
        if (!aristaActual->adyacente->marca && aristaActual->peso < pesoMinimo && !aristaActual->marca) {
            aristaMinima = aristaActual;
            pesoMinimo = aristaActual->peso;
        }

        aristaActual = aristaActual->siguiente;
    }

    // Devolver la arista minima encontrada
    return aristaMinima;
}

//***********************************************************************************

// Metodo para encontrar el arbol de expansion minima utilizando el algoritmo de Prim
bool Grafica::Prim()
{
    // Verificar si la grafica esta vacia
    if (EstaVacia()) {
        std::cout << "La grafica esta vacia." << std::endl;
        return false;
    }

    // Marcar el primer nodo como visitado
    MarcarNodo(primero->nombre);

    // Inicializar arreglos para almacenar los nodos visitados y las aristas del arbol de expansion minima
    char visitados[numNodos];
    Arista* arbolExpMin[numNodos - 1]; // El numero maximo de aristas en un arbol de expansion minima es numNodos - 1

    // Inicializar el numero de nodos visitados
    int numVisitados = 1;
    visitados[0] = primero->nombre;

    // Mientras haya nodos por visitar
    while (numVisitados < numNodos) {
        // Inicializar una arista minima
        Arista* aristaMinima = nullptr;
        int pesoMinimo = std::numeric_limits<int>::max();

        // Iterar sobre los nodos visitados para encontrar la arista minima que conecta un nodo visitado con uno no visitado
        for (int i = 0; i < numVisitados; ++i) {
            // Obtener la arista minima para el nodo actual
            Arista* arista = ObtenerAristaMinima(visitados[i]);
            if (arista && arista->peso < pesoMinimo && !arista->adyacente->marca) {
                aristaMinima = arista;
                pesoMinimo = arista->peso;
            }
        }

        // Verificar si se encontro una arista minima
        if (aristaMinima) {
            // Marcar el nodo adyacente como visitado
            MarcarNodo(aristaMinima->adyacente->nombre);
            visitados[numVisitados++] = aristaMinima->adyacente->nombre;

            // Agregar la arista minima al arbol de expansion minima
            arbolExpMin[numVisitados - 2] = aristaMinima;
        } else {
            // Si no se encontro una arista minima, la grafica no es conexa
            std::cout << "La grafica no es conexa." << std::endl;
            return false;
        }
    }

    // Imprimir el arbol de expansion minima y el peso total del arbol
    int pesoTotal = 0;
    std::cout << "Aristas del arbol de expansion minima:" << std::endl;

    for (int i = 0; i < numNodos - 1; ++i) {
        std::cout << "Arista: " << arbolExpMin[i]->adyacente->nombre << " - " << arbolExpMin[i]->peso << std::endl;
        pesoTotal += arbolExpMin[i]->peso;
    }

    std::cout << "Peso total del arbol de expansion minima: " << pesoTotal << std::endl;
    return true;
}
