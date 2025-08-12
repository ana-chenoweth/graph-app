/**
* \brief Implementaci�n de la clase Grafica con el algoritmo de Prim
* \file Grafica.hpp
* \author Chenoweth Galaz Ana Laura, Salcido Valenzuela Georgina
* \date 23/04/2024
*/

#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

/** \brief Clase Grafica
 *
 * Permite manipular una gr&aacute;fica, agregar elementos, eliminarlos, encontrar un arbol de expansi�n m&iacute;nimo, etc.
 *
 * \code
 #include <iostream>
#include "Grafica.hpp"

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
 * \endcode
 *
 * \verbatim
 Aristas del �rbol de expansi�n m�nima:
 Arista: C - 1
 Arista: B - 1
 Arista: E - 2
 Arista: H - 2
 Arista: G - 1
 Arista: I - 2
 Arista: F - 2
 Arista: D - 4
 Peso total del �rbol de expansi�n m�nima: 15
 * \endverbatim
 *
 */

class Grafica
{
private:
    int numNodos, numAristas;

    struct Nodo;

    struct Arista{
        Arista(Nodo *ady, int peso = 0, Arista *sig = nullptr, Arista *ant = nullptr, bool marca = false);

        Nodo* adyacente;
        Arista* siguiente, *anterior;

        int peso;
        bool marca;
    };

    struct Nodo{
        Nodo(char nom, Nodo *sig = nullptr, Nodo *ant = nullptr);

        void Agregar(Nodo *ady, int peso);
        void Eliminar(Nodo *ady);

        Arista * BuscarDir(Nodo *ady) const;

        bool EstaAislado() const;
        int Aislar();

        char nombre;
        int grado;
        bool marca;

        Arista *primera, *ultima;
        Nodo *siguiente, *anterior;
    } *primero, *ultimo;

    Nodo* BuscarDir(char nom) const;

public:
    /**
     * \brief Constructor de la clase Grafica
     */
    Grafica();
    /**
     * \brief Destructor de la clase Grafica
     */
    ~Grafica();
    /** \brief Operador de asignaci&oacute;n de la clase Grafica
     *
     * \param Gr&aacute;fica a asignar
     * \return Gr&aacute; asignada
     *
     */
    Grafica &operator=(const Grafica &g);
    /** \brief Constructor de copias de la clase Grafica
     *
     * \param Gr&aacute;fica a copiar
     * \return Copia de la gr&aacute;fica
     *
     */
    Grafica(const Grafica &g);
    /** \brief M&eacute;todo para agregar un nodo a la gr&aacute;fica
     *
     * \param Nombre del nodo
     * \return void
     *
     */
    void Agregar(char nom);
    /** \brief M&eacute;todo para agregar una arista a la gr&aacute;fica
     *
     * \param inicio Nodo inicial de la arista
     * \param fin Nodo final de la arista
     * \param peso Peso de la arista
     * \return void
     *
     */
    void Agregar(char inicio, char fin, int peso);
    /** \brief M&eacute;todo para eliminar un nodo de la gr&aacute;fica
     *
     * \param nom Nombre del nodo
     * \return void
     *
     */
    void Eliminar(char nom);
    /** \brief M&eacute;todo para eliminar una arista de la gr&aacute;fica
     *
     * \param inicio Nodo inicial de la arista
     * \param fin Nodo final de la arista
     * \return void
     *
     */
    void Eliminar(char inicio, char fin);
    /** \brief M&eacute;todo para buscar un nodo en la gr&aacute;fica
     *
     * \param nom Nombre del nodo
     * \return Verdadero si se encuentra el nodo en la gr&aacute;fica
     *
     */
    bool Buscar(char nom) const;
    /** \brief M&eacute;todo para buscar una arista en la gr&aacute;fica
     *
     * \param inicio Nodo inicial de la arista
     * \param fin Nodo final de la arista
     * \return Verdadero si se encuentra la arista en la gr@aacute;fica
     *
     */
    bool Buscar(char inicio, char fin) const;
    /** \brief M&eacute;todo para obtener el n&uacute;mero de nodos en la gr&aacute;fica
     *
     * \return int N&uacute;mero de nodos
     *
     */
    int ObtenerNumNodos() const;
    /** \brief M&eacute;todo para obtener el n&uacute;mero de aristas en la gr&aacute;fica
     *
     * \return int N&uacute;mero de aristas
     *
     */
    int ObtenerNumAristas() const;
    /** \brief M&eacute;todo para obtener el grado de un nodo
     *
     * \param nom Nombre del nodo
     * \return int Grado
     *
     */
    int ObtenerGrado(char nom) const;
    /** \brief M&eacute;todo para imprimir la gr&aacute;fica completa
     *
     * \return void
     *
     */
    void Imprimir() const;
    /** \brief M&eacute;todo para imprimir un nodo y toda la informaci&oacute;n adyacente.
     *
     * \param nom Nombre del nodo
     * \return void
     *
     */
    void Imprimir(char nom) const;
    /** \brief M&eacute;todo para vaciar una gr&aacute;fica
     *
     * \return void
     *
     */
    void Vaciar(); // Vaciar grafica
    /** \brief M&eacute;todo para aislar y vaciar un nodo
     *
     * \param nom char
     * \return void
     *
     */
    void Vaciar(char nom);// Vaciar nodo
    /** \brief M&eacute;todo para conocer si la gr&aacute;fica est&aacute; vac&iacute;a
     *
     * \return bool Verdadero si est&aacute; vac&iacute;A
     *
     */
    bool EstaVacia() const;
    
    // M�todos de Prim

    /** \brief M&eacute;todo para marcar un nodo
     *
     * \param nom Nombre del nodo
     * \return void
     *
     */
    void MarcarNodo(char nom);
    /** \brief M&eacute;todo para marcar una arista
     *
     * \param inicio Nodo inicial de la arista
     * \param fin Nodo final de la arista
     * \return void
     *
     */
    void MarcarArista(char inicio, char fin);
    /** \brief M&eacute;todo para obtener la arista con menor peso
     *
     * \param nombreVertice Nombre de la arista
     * \return Arista*
     *
     */
    Arista* ObtenerAristaMinima(char nombreVertice);
    /** \brief M&eacute;todo para encontrar un &aacute;rbol de expansi&oacute;n de peso m&iacute;nimo
     *
     * \return Verdadero si el arbol es convexo
     *
     */
    bool Prim();
};

#endif // GRAFICA_HPP_INCLUDED
