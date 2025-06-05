#ifndef TABLERO_H
#define TABLERO_H

#include <SFML/Graphics.hpp>
#include <vector>

const int FILAS = 6;
const int COLUMNAS = 7;
const float RADIO = 40.f;

enum class Casilla {
    VACIA,
    JUGADOR,
    MAQUINA
};

class Tablero {
public:
    Tablero();
    void dibujar(sf::RenderWindow& ventana);
    bool insertarFicha(int columna, Casilla jugador);
    bool hayVictoria(Casilla jugador) const;
    const std::vector<std::vector<Casilla>>& obtenerEstado() const;

private:
    std::vector<std::vector<Casilla>> grid;
    bool comprobarDireccion(int fila, int col, int df, int dc, Casilla jugador) const;
};

#endif