#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

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

public:
    Grafica();
};

#endif // GRAFICA_HPP_INCLUDED
