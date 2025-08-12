#include <iostream>
#include "Grafica/Grafica.hpp"

int main() {
    // Crear una instancia de la clase Grafica
    Grafica grafica;

    // Agregar nodos
    grafica.Agregar('A');
    grafica.Agregar('B');
    grafica.Agregar('C');
    grafica.Agregar('D');
    grafica.Agregar('E');
    grafica.Agregar('F');
    grafica.Agregar('G');
    grafica.Agregar('H');
    grafica.Agregar('I');

    // Agregar aristas
    grafica.Agregar('A', 'B', 3);
    grafica.Agregar('A', 'C', 1);
    grafica.Agregar('A', 'D', 6);

    grafica.Agregar('B', 'C', 1);
    grafica.Agregar('B', 'E', 2);
    grafica.Agregar('B', 'G', 7);

    grafica.Agregar('C', 'E', 6);

    grafica.Agregar('F', 'E', 3);
    grafica.Agregar('F', 'D', 4);
    grafica.Agregar('F', 'I', 2);

    grafica.Agregar('E', 'H', 2);
    grafica.Agregar('I', 'H', 3);
    grafica.Agregar('G', 'H', 1);
    grafica.Agregar('G', 'I', 2);

    grafica.Agregar('D', 'I', 5);

    // Ejecutar el algoritmo de Prim para encontrar el �rbol de expansi�n m�nima
    grafica.Prim();
    return 0;
}
