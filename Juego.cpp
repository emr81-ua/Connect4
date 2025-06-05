#include "Juego.h"
#include <iostream>

Juego::Juego() : ventana(sf::VideoMode(700, 600), "4 en Raya"), turnoJugador(true), juegoTerminado(false) {
    ventana.setFramerateLimit(60);
}

void Juego::buclePrincipal() {
    while (ventana.isOpen()) {
        manejarEventos();
        actualizar();
        dibujar();
    }
}

void Juego::manejarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed)
            ventana.close();

        if (!juegoTerminado && turnoJugador && evento.type == sf::Event::MouseButtonPressed) {
            int columna = evento.mouseButton.x / (ventana.getSize().x / COLUMNAS);
            if (tablero.insertarFicha(columna, Casilla::JUGADOR)) {
                if (tablero.hayVictoria(Casilla::JUGADOR)) {
                    juegoTerminado = true;
                    std::cout << "¡Has ganado!\n";
                }
                else {
                    turnoJugador = false;
                }
            }
        }
    }
}

void Juego::actualizar() {
    if (!turnoJugador && !juegoTerminado) {
        int columnaIA = ia.elegirColumna(tablero);
        if (tablero.insertarFicha(columnaIA, Casilla::MAQUINA)) {
            if (tablero.hayVictoria(Casilla::MAQUINA)) {
                juegoTerminado = true;
                std::cout << "¡La máquina ha ganado!\n";
            }
            else {
                turnoJugador = true;
            }
        }
    }
}

void Juego::dibujar() {
    ventana.clear(sf::Color::Blue);
    tablero.dibujar(ventana);
    ventana.display();
}

void Juego::reiniciar() {
    tablero = Tablero();
    juegoTerminado = false;
    turnoJugador = true;
}
