// ==== Tablero.cpp ====
#include "Tablero.h"

Tablero::Tablero() : grid(FILAS, std::vector<Casilla>(COLUMNAS, Casilla::VACIA)) {}

void Tablero::dibujar(sf::RenderWindow& ventana) {
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS; ++col) {
            sf::CircleShape ficha(RADIO - 5);
            ficha.setPosition(col * 100 + 10, fila * 100 + 10);
            ficha.setFillColor(sf::Color::White);

            if (grid[fila][col] == Casilla::JUGADOR)
                ficha.setFillColor(sf::Color::Red);
            else if (grid[fila][col] == Casilla::MAQUINA)
                ficha.setFillColor(sf::Color::Yellow);

            ventana.draw(ficha);
        }
    }
}

bool Tablero::insertarFicha(int columna, Casilla jugador) {
    if (columna < 0 || columna >= COLUMNAS)
        return false;
    for (int fila = FILAS - 1; fila >= 0; --fila) {
        if (grid[fila][columna] == Casilla::VACIA) {
            grid[fila][columna] = jugador;
            return true;
        }
    }
    return false;
}

bool Tablero::comprobarDireccion(int fila, int col, int df, int dc, Casilla jugador) const {
    int conteo = 0;
    for (int i = 0; i < 4; ++i) {
        int r = fila + i * df;
        int c = col + i * dc;
        if (r >= 0 && r < FILAS && c >= 0 && c < COLUMNAS && grid[r][c] == jugador) {
            conteo++;
        }
        else {
            break;
        }
    }
    return conteo == 4;
}

bool Tablero::hayVictoria(Casilla jugador) const {
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS; ++col) {
            if (grid[fila][col] != jugador) continue;
            if (comprobarDireccion(fila, col, 0, 1, jugador) ||  // Horizontal
                comprobarDireccion(fila, col, 1, 0, jugador) ||  // Vertical
                comprobarDireccion(fila, col, 1, 1, jugador) ||  // Diagonal 
                comprobarDireccion(fila, col, 1, -1, jugador))   // Diagonal 
                return true;
        }
    }
    return false;
}

const std::vector<std::vector<Casilla>>& Tablero::obtenerEstado() const {
    return grid;
}