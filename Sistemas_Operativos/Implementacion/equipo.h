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
		vector<coordenadas> posiciones;
		coordenadas pos_bandera_contraria;
		int jugador_mas_cercano;
		//
		// ...
		//

        sem_t bandera_contraria_encontrada;

		// Métodos privados 
		direccion apuntar_a(coordenadas pos2, coordenadas pos1);
		void jugador(int nro_jugador);
		void buscar_bandera_contraria(int i);
		mutex mi_turno;
		bool esta_mas_cerca(int i, int mejor, coordenadas bandera_contraria);
		//
		// ...
		//
	public:
		Equipo(gameMaster *belcebu, color equipo, 
				estrategia strat, int cant_jugadores, int quantum, vector<coordenadas> posiciones);
		void comenzar();
		void terminar();
		// crear jugadores
        bool encontrado = false;

};
#endif // EQUIPO_H
