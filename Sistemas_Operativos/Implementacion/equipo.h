#ifndef EQUIPO_H
#define EQUIPO_H

#include <semaphore.h>
#include <vector>
#include <thread>
#include "definiciones.h"
#include "gameMaster.h"

using namespace std;

class Equipo {
	private:
		// Atributos Privados 
		gameMaster *belcebu; 
		color contrario, equipo, bandera_contraria;
		estrategia strat;
		int cant_jugadores, quantum, quantum_restante;
		vector<thread> jugadores;
		coordenadas pos_bandera_contraria;
		int jugador_mas_cercano;
        sem_t bandera_contraria_encontrada;
		

		// Métodos privados 
		direccion apuntar_a(coordenadas pos2, coordenadas pos1);
		void jugador(int nro_jugador);
		void buscar_bandera_contraria(int i);
		void buscar_jugador_mas_cercano();
		int distancia(coordenadas pos1, coordenadas pos2);
		void inicializar_prioridades();
        int buscar_jugador_prioritario();


	public:
		Equipo(gameMaster *belcebu, color equipo, estrategia strat, int cant_jugadores, int quantum, vector<coordenadas> posiciones);
		void comenzar();
		void terminar();
        bool encontrado = false;

};
#endif // EQUIPO_H