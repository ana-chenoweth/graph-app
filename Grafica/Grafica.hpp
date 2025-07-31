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

    Nodo* BuscarDir(char nom) const;

public:
    Grafica();
    ~Grafica();
    Grafica &operator=(const Grafica &g);
    Grafica(const Grafica &g);
    void Agregar(char nom);
    void Agregar(char inicio, char fin, int peso);
    void Eliminar(char nom);
    void Eliminar(char inicio, char fin);
    bool Buscar(char nom) const;
    bool Buscar(char inicio, char fin) const;
    int ObtenerNumNodos() const;
    int ObtenerNumAristas() const;
    int ObtenerGrado(char nom) const;
};

#endif // GRAFICA_HPP_INCLUDED
