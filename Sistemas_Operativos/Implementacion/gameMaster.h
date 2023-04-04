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
    coordenadas pos_bandera_roja, pos_bandera_azul;
    estrategia strat;


    //bitsets que indican, de cada equipo, cuales jugadores pueden moverse y cuales no
    vector<bool> jugadores_rojos_trabados;
    vector<bool> jugadores_azules_trabados;

    // Métodos privados
    void restaurar_movimientos_restantes(color equipo);
    bool es_posicion_valida(coordenadas pos);
    coordenadas proxima_posicion(coordenadas anterior, direccion movimiento); // Calcula la proxima posición a moverse==
    bool es_bandera_contraria(coordenadas pos);
    bool equipo_entero_trabado(color equipo);
    void liberar_jugadores();

public:
    // Atributos públicos
    int x, y, jugadores_por_equipos;
    int quantum;
    int movimientos_restantes_equipo;
    int mas_cercano_rojo, mas_cercano_azul;
    int mas_prioritario_azul, mas_prioritario_rojo;
    vector<coordenadas> pos_jugadores_azules, pos_jugadores_rojos;
    color ganador = INDEFINIDO;
    sem_t turno_rojo, turno_azul;
    vector<sem_t> limitador_movimientos_rojo;
    vector<sem_t> limitador_movimientos_azul;
    vector<int> prioridad_jugadores_rojos;
    vector<int> prioridad_jugadores_azules;

    //Dos semaforos extra para SHORTEST, donde ademas de pedir que el juego no empiece hasta que ambos equipos
    //encuentren la bandera contraria, debemos pedir que no empiece hasta que ambos equipos encuentren el jugador
    //mas cercano a dicha bandera. Se definen en gamemaster para que cada equipo pueda comunicarse con el del
    //equipo contrario
    sem_t jugador_mas_cercano_rojo_encontrado;
    sem_t jugador_mas_cercano_azul_encontrado;
    sem_t jugador_prioritario_rojo_encontrado;
    sem_t jugador_prioritario_azul_encontrado;

    // Métodos públicos
    gameMaster(Config config, estrategia strategy, const int quantum);
    int mover_jugador(direccion dir, int nro_jugador);
    void termino_ronda(color equipo); // Marca que un jugador terminó la ronda
    color obtener_coordenadas(coordenadas coord);
    bool es_color_libre(color color_tablero);
    bool termino_juego();
	int getTamx();
	int getTamy();
    string enum_a_string(int dir);

    color turno;
    mutex mutex_movimiento;
};

#endif // GAMEMASTER_H