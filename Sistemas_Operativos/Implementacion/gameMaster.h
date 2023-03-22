#ifndef GAMEMASTER_H
#define GAMEMASTER_H
#include <tuple>
#include <cstdio>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include "definiciones.h"
#include "config.h"

using namespace std;

class gameMaster {
private:
    // Atributos Privados
    int nro_ronda = 0;
    vector<vector<color>> tablero;
    vector<coordenadas> pos_jugadores_azules, pos_jugadores_rojos;
    coordenadas pos_bandera_roja, pos_bandera_azul;
    color turno;
    estrategia strat;

    mutex mutex_moverse;
	int valor_semaforo;
    //
    //...
    //

    // Métodos privados
    void mover_jugador_tablero(coordenadas pos_anterior, coordenadas pos_nueva, color colorEquipo);
    //
    //...
    //
    void hacer_signals(color equipo);

public:
    // Atributos públicos
    gameMaster(Config config);
    void termino_ronda(color equipo); // Marca que un jugador terminó la ronda
    int mover_jugador(direccion dir, int nro_jugador);
    color ganador = INDEFINIDO;
    //
    //...
    //
    int x, y, jugadores_por_equipos;
    color obtener_coordenadas(coordenadas coord);

    // Métodos públicos
    bool termino_juego();
	int getTamx();
	int getTamy();
    static int distancia(coordenadas pair1, coordenadas pair2);
    sem_t turno_rojo, turno_azul; // FIXME: Al principio necesito entrar como azul, luego puedo hacerlo por el método termino_ronda....

    vector<sem_t> limitador_movimientos_rojo;
    vector<sem_t> limitador_movimientos_azul;

    color en_posicion(coordenadas coord);
    bool es_posicion_valida(coordenadas pos);
    bool es_color_libre(color color_tablero);
	coordenadas proxima_posicion(coordenadas anterior, direccion movimiento); // Calcula la proxima posición a moverse	
    //
    //...
    //
    int quantum = 10;
};

#endif // GAMEMASTER_H