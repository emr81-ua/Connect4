// ==== Juego.h ====
#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "Tablero.h"
#include "IA.h"

class Juego {
public:
    Juego();
    void buclePrincipal();

private:
    void manejarEventos();
    void actualizar();
    void dibujar();
    void reiniciar();

    sf::RenderWindow ventana;
    Tablero tablero;
    IA ia;
    bool turnoJugador;
    bool juegoTerminado;
};

#endif