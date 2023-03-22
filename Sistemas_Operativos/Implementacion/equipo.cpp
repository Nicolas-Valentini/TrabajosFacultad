#include "equipo.h"
#include <assert.h> 

direccion Equipo::apuntar_a(coordenadas pos1, coordenadas pos2) {
	if (pos2.first > pos1.first) return ABAJO;
	if (pos2.first < pos1.first) return ARRIBA;
	if (pos2.second > pos1.second) 
		return DERECHA;
	else
		return IZQUIERDA;
}


void Equipo::jugador(int nro_jugador) {
	if (this->equipo == ROJO){
		printf("\033[0;31mJugador %d entró a la función jugador\033[0;37m\n", nro_jugador);
	} else {

		printf("\033[0;34mJugador %d entró a la función jugador\033[0;37m\n", nro_jugador);
	}
	while(!this->belcebu->termino_juego()) {
		direccion dir = apuntar_a((this->posiciones)[nro_jugador], this->pos_bandera_contraria);
		
        switch(this->strat) {
			case(SECUENCIAL):
				// mantener una barrera para cada jugador, que limita la cantidad de movimientos por turno
				// se baja al mover una vez y se levanta cuando haya un cambio de turno
				if (this->equipo == ROJO){
					sem_wait(&(this->belcebu->limitador_movimientos_rojo)[nro_jugador]);
					printf("\033[0;31mJugador %d se movio hacia %d desde (%d, %d)\033[0;37m\n", nro_jugador, dir, this->posiciones[nro_jugador].first, this->posiciones[nro_jugador].second);
				} else {
					sem_wait(&(this->belcebu->limitador_movimientos_azul)[nro_jugador]);
					printf("\033[0;34mJugador %d se movio hacia %d desde (%d, %d)\033[0;37m\n", nro_jugador, dir, this->posiciones[nro_jugador].first, this->posiciones[nro_jugador].second);
				}
				this->belcebu->mover_jugador(dir, nro_jugador);
				this->posiciones[nro_jugador] = this->belcebu->proxima_posicion(this->posiciones[nro_jugador], dir);
				break;
			
			case(RR):
				if (this->equipo == ROJO){
					sem_wait(&(this->belcebu->limitador_movimientos_rojo)[nro_jugador]);
				} else {
					sem_wait(&(this->belcebu->limitador_movimientos_azul)[nro_jugador]);
				}
				for(auto &t:jugadores){
					t.join();
				}	
				this->belcebu->mover_jugador(dir,nro_jugador);
				break;

			case(SHORTEST):
				if (this->equipo == ROJO){
					sem_wait(&(this->belcebu->limitador_movimientos_rojo)[nro_jugador]);
				} else {
					sem_wait(&(this->belcebu->limitador_movimientos_azul)[nro_jugador]);
				}
				if(nro_jugador == jugador_mas_cercano){
					this->belcebu->mover_jugador(dir,nro_jugador);
				}
				break;

			case(USTEDES):
				//
				// ...
				//
				break;
			default:
				break;
		}	
		// Termino ronda ? Recordar llamar a belcebu...
		// OJO. Esto lo termina un jugador... 
	}
	
}

Equipo::Equipo(gameMaster *belcebu, color equipo, estrategia strat, int cant_jugadores, int quantum, vector<coordenadas> posiciones) {
	this->belcebu = belcebu;
	this->equipo = equipo;
	this->contrario = (equipo == ROJO)? AZUL: ROJO;
	this->bandera_contraria = (equipo==ROJO)? BANDERA_AZUL: BANDERA_ROJA;
	this->strat = strat;
	this->quantum = quantum;
	this->quantum_restante = quantum;
	this->cant_jugadores = cant_jugadores;
	this->posiciones = posiciones;
    sem_init(&(this->bandera_contraria_encontrada), 0, 0);
	printf("Creando equipo %d \n", equipo);
}

bool Equipo::esta_mas_cerca(int i, int mejor, coordenadas bandera_contraria){
	int dist_i = abs((this->posiciones)[i].first - bandera_contraria.first) + abs((this->posiciones)[i].second - bandera_contraria.second);
	int dist_mejor = abs((this->posiciones)[mejor].first - bandera_contraria.first) + abs((this->posiciones)[mejor].second - bandera_contraria.second);
	bool res = false;
	if(dist_i <= dist_mejor){
		res = true;
	}
	return res;

}

void Equipo::buscar_bandera_contraria(int i) {
	if (this->equipo == ROJO){
		printf("\033[0;31mJugador %d buscando bandera contraria\033[0;37m\n", i);
	} else {
		printf("\033[0;34mJugador %d buscando bandera contraria\033[0;37m\n", i);
	}
    int tam = (this->belcebu->x) * (this->belcebu->y);
    int div = tam / (this->belcebu->jugadores_por_equipos);
    int celda = div * i;
    coordenadas pos = {celda / this->belcebu->x, celda % this->belcebu->x};
    color color_pos;
    //printf("Jugador %d buscando bandera contraria en (%d, %d)\n", i, pos.first, pos.second);
    while(div > 0 && !(this->encontrado)){
        pos.second++;
        if (pos.second > this->belcebu->y-1){
            pos.second = 0;
            pos.first++;
			if (pos.first == this->belcebu->x){
				break;
			}
        }
		assert(this->belcebu->es_posicion_valida(pos));
		color_pos = this->belcebu->obtener_coordenadas(pos);
		if (this->equipo == ROJO){
			if (color_pos == BANDERA_AZUL) {
				this->pos_bandera_contraria = pos;
				printf("\033[0;33mEl equipo rojo encontró la bandera en (%d, %d)\033[0;37m\n", pos.first, pos.second);
				this->encontrado = true;
				for(int i=0; i < this->cant_jugadores; i++){
					sem_post(&(this->bandera_contraria_encontrada));
				}
				break;
			}
		} else {
			if (color_pos == BANDERA_ROJA) {
				this->pos_bandera_contraria = pos;
				printf("\033[0;33mEl equipo azul encontró la bandera en (%d, %d)\033[0;37m\n", pos.first, pos.second);
				this->encontrado = true;
				for(int i=0; i < this->cant_jugadores; i++){
					sem_post(&(this->bandera_contraria_encontrada));
				}
				break;
			}
		}
		div--;
    }
    sem_wait(&(this->bandera_contraria_encontrada));
    this->jugador(i);
}

void Equipo::comenzar() {
	for(int i=0; i < cant_jugadores; i++) {
		if (this->equipo == ROJO){
			printf("\033[0;31mCreando jugador %d\033[0;37m\n", i);
		} else {
			printf("\033[0;34mCreando jugador %d\033[0;37m\n", i);
		}
        jugadores.emplace_back(thread(&Equipo::buscar_bandera_contraria, this, i));
    }
}

void Equipo::terminar() {
	for(auto &t:jugadores){
		t.join();
	}	
}