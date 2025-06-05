#include "IA.h"
#include <algorithm>
#include <limits>

IA::IA() {}

int IA::elegirColumna(const Tablero& tablero) {
    int mejorValor = std::numeric_limits<int>::min();
    int mejorColumna = 3; // centro por defecto

    for (int col : obtenerColumnasValidas(tablero)) {
        Tablero copia = tablero;
        copia.insertarFicha(col, Casilla::MAQUINA);
        int valor = minimax(copia, 5, false);
        if (valor > mejorValor) {
            mejorValor = valor;
            mejorColumna = col;
        }
    }

    return mejorColumna;
}

int IA::minimax(Tablero tablero, int profundidad, bool esMaximizando) {
    if (tablero.hayVictoria(Casilla::MAQUINA)) return 1000;
    if (tablero.hayVictoria(Casilla::JUGADOR)) return -1000;
    if (profundidad == 0) return evaluarTablero(tablero);

    std::vector<int> columnas = obtenerColumnasValidas(tablero);

    if (esMaximizando) {
        int mejorValor = std::numeric_limits<int>::min();
        for (int col : columnas) {
            Tablero copia = tablero;
            copia.insertarFicha(col, Casilla::MAQUINA);
            int valor = minimax(copia, profundidad - 1, false);
            mejorValor = std::max(mejorValor, valor);
        }
        return mejorValor;
    }
    else {
        int peorValor = std::numeric_limits<int>::max();
        for (int col : columnas) {
            Tablero copia = tablero;
            copia.insertarFicha(col, Casilla::JUGADOR);
            int valor = minimax(copia, profundidad - 1, true);
            peorValor = std::min(peorValor, valor);
        }
        return peorValor;
    }
}

std::vector<int> IA::obtenerColumnasValidas(const Tablero& tablero) {
    std::vector<int> columnas;
    const auto& estado = tablero.obtenerEstado();
    for (int col = 0; col < COLUMNAS; ++col) {
        if (estado[0][col] == Casilla::VACIA)
            columnas.push_back(col);
    }
    return columnas;
}

// Función de evaluación simple
int IA::evaluarTablero(const Tablero& tablero) {
    const auto& estado = tablero.obtenerEstado();
    int score = 0;

    // 1. Favorecer el centro del tablero
    int centroCol = COLUMNAS / 2;
    int centroScore = 0;
    for (int fila = 0; fila < FILAS; ++fila) {
        if (estado[fila][centroCol] == Casilla::MAQUINA) centroScore += 3;
        else if (estado[fila][centroCol] == Casilla::JUGADOR) centroScore -= 3;
    }
    score += centroScore;

    // 2. Verificar ventanas de 4 celdas en todas las direcciones
    auto evaluarVentana = [](std::vector<Casilla> ventana, Casilla jugador) {
        int score = 0;
        int propias = std::count(ventana.begin(), ventana.end(), jugador);
        int vacias = std::count(ventana.begin(), ventana.end(), Casilla::VACIA);
        Casilla rival = (jugador == Casilla::MAQUINA) ? Casilla::JUGADOR : Casilla::MAQUINA;

        if (propias == 4) score += 100;
        else if (propias == 3 && vacias == 1) score += 10;
        else if (propias == 2 && vacias == 2) score += 5;

        // Penaliza si el rival tiene 3 en línea y una vacía
        int rivalCount = std::count(ventana.begin(), ventana.end(), rival);
        if (rivalCount == 3 && vacias == 1) score -= 80;

        return score;
        };

    // 3. Horizontal
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS - 3; ++col) {
            std::vector<Casilla> ventana = {
                estado[fila][col],
                estado[fila][col + 1],
                estado[fila][col + 2],
                estado[fila][col + 3]
            };
            score += evaluarVentana(ventana, Casilla::MAQUINA);
        }
    }

    // 4. Vertical
    for (int col = 0; col < COLUMNAS; ++col) {
        for (int fila = 0; fila < FILAS - 3; ++fila) {
            std::vector<Casilla> ventana = {
                estado[fila][col],
                estado[fila + 1][col],
                estado[fila + 2][col],
                estado[fila + 3][col]
            };
            score += evaluarVentana(ventana, Casilla::MAQUINA);
        }
    }

    // 5. Diagonal positiva (/)
    for (int fila = 3; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS - 3; ++col) {
            std::vector<Casilla> ventana = {
                estado[fila][col],
                estado[fila - 1][col + 1],
                estado[fila - 2][col + 2],
                estado[fila - 3][col + 3]
            };
            score += evaluarVentana(ventana, Casilla::MAQUINA);
        }
    }

    // 6. Diagonal negativa (\)
    for (int fila = 0; fila < FILAS - 3; ++fila) {
        for (int col = 0; col < COLUMNAS - 3; ++col) {
            std::vector<Casilla> ventana = {
                estado[fila][col],
                estado[fila + 1][col + 1],
                estado[fila + 2][col + 2],
                estado[fila + 3][col + 3]
            };
            score += evaluarVentana(ventana, Casilla::MAQUINA);
        }
    }

    return score;
}

