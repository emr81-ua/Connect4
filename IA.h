#ifndef IA_H
#define IA_H

#include "Tablero.h"
#include <random>

class IA {
public:
    IA();
    int elegirColumna(const Tablero& tablero);
private:
    int minimax(Tablero tablero, int profundidad, bool esMaximizando);
    int evaluarTablero(const Tablero& tablero);
    std::vector<int> obtenerColumnasValidas(const Tablero& tablero);
};


#endif
