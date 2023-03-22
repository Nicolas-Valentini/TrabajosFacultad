#include <sys/unistd.h>
#include <assert.h>     /* assert */
#include "gameMaster.h"

bool gameMaster::es_posicion_valida(coordenadas pos) {
	return (pos.first >= 0) && (pos.first < x) && (pos.second >= 0) && (pos.second < y);
}

bool gameMaster::es_color_libre(color color_tablero){
    return color_tablero == VACIO || color_tablero == INDEFINIDO;
}

color gameMaster::en_posicion(coordenadas coord) {
	return tablero[coord.first][coord.second];
}

int gameMaster::getTamx() {
	return x;
}

int gameMaster::getTamy() {
	return y;
}

int gameMaster::distancia(coordenadas c1, coordenadas c2) {
    return abs(c1.first-c2.first)+abs(c1.second-c2.second);
}

gameMaster::gameMaster(Config config) {
	assert(config.x>0); 
	assert(config.y>0); // Tamaño adecuado del tablero

    this->x = config.x;
	this->y = config.y;

	assert((config.bandera_roja.first == 1)); // Bandera roja en la primera columna
	assert(es_posicion_valida(config.bandera_roja)); // Bandera roja en algún lugar razonable

	assert((config.bandera_azul.first == x-1)); // Bandera azul en la primera columna
	assert(es_posicion_valida(config.bandera_azul)); // Bandera roja en algún lugar razonable

	assert(config.pos_rojo.size() == config.cantidad_jugadores);
	assert(config.pos_azul.size() == config.cantidad_jugadores);
	for(auto &coord : config.pos_rojo) {
		assert(es_posicion_valida(coord)); // Posiciones validas rojas
	}		

	for(auto &coord : config.pos_azul) {
		assert(es_posicion_valida(coord)); // Posiciones validas rojas
	}		

	
	this->jugadores_por_equipos = config.cantidad_jugadores;
	this->pos_bandera_roja = config.bandera_roja;
	this->pos_bandera_azul = config.bandera_azul;
    this->pos_jugadores_rojos = config.pos_rojo;
    this->pos_jugadores_azules = config.pos_azul;

	// Seteo tablero en vacio
	tablero.resize(x);
    for (int i = 0; i < x; ++i) {
        tablero[i].resize(y);
        fill(tablero[i].begin(), tablero[i].end(), VACIO);
    }

	// Agrego los jugadores
    for(auto &coord : config.pos_rojo){
        assert(es_color_libre(tablero[coord.first][coord.second])); // Compruebo que no haya otro jugador en esa posicion
        tablero[coord.first][coord.second] = ROJO; // Lo agrego al tablero
    }
    for(auto &coord : config.pos_azul){
        assert(es_color_libre(tablero[coord.first][coord.second]));
        tablero[coord.first][coord.second] = AZUL;
    }

    tablero[config.bandera_roja.first][config.bandera_roja.second] = BANDERA_ROJA;
    tablero[config.bandera_azul.first][config.bandera_azul.second] = BANDERA_AZUL;

	this->turno = ROJO;
	sem_init(&turno_azul, 0, 0);
	switch (strat) {
		case SECUENCIAL:
		    sem_init(&turno_rojo, 0, this->jugadores_por_equipos);
			valor_semaforo = this->jugadores_por_equipos;
			this->limitador_movimientos_rojo = vector<sem_t>(this->jugadores_por_equipos);
			this->limitador_movimientos_azul = vector<sem_t>(this->jugadores_por_equipos);
			for (int i = 0; i < valor_semaforo; i++){
				sem_init(&(this->limitador_movimientos_rojo[i]), 0, 1);
				sem_init(&(this->limitador_movimientos_azul[i]), 0, 0);
			}
			break;
		case RR:
            sem_init(&turno_rojo, 0, quantum);
			valor_semaforo = quantum;
			this->limitador_movimientos_rojo = vector<sem_t>(this->jugadores_por_equipos); //asumimos que se inicializan. chequear despues
			for(int i = 0; i< quantum; i++){
				sem_post(&limitador_movimientos_rojo[i%(this->jugadores_por_equipos)]);
			}
			this->limitador_movimientos_azul = vector<sem_t>(this->jugadores_por_equipos); //asumimos que se inicializan. chequear despues
			break;
		case SHORTEST:
            sem_init(&turno_rojo, 0, 1);
			//turno_rojo = sem(1);
			this->limitador_movimientos_rojo = vector<sem_t>(this->jugadores_por_equipos);
			this->limitador_movimientos_azul = vector<sem_t>(this->jugadores_por_equipos);
			valor_semaforo = 1;
			break;
		case USTEDES:
			//turno_rojo = 
			break;
	}
	printf("\033[0;33mEl gamemaster fue inicializado con exito\033[0;37m\n");
}

void gameMaster::mover_jugador_tablero(coordenadas pos_anterior, coordenadas pos_nueva, color colorEquipo){
    assert(es_color_libre(tablero[pos_nueva.first][pos_nueva.second]));
    tablero[pos_anterior.first][pos_anterior.second] = VACIO; 
    tablero[pos_nueva.first][pos_nueva.second] = colorEquipo;
}


int gameMaster::mover_jugador(direccion dir, int nro_jugador) {
	// Chequear que la movida sea valida
	coordenadas pos_nueva, pos_anterior;
	if (this->turno == ROJO){
		pos_anterior = this->pos_jugadores_rojos[nro_jugador];
	} else {
		pos_anterior = this->pos_jugadores_azules[nro_jugador];
	}

	pos_nueva = proxima_posicion(pos_anterior, dir);
	if (!es_posicion_valida(pos_nueva)){
		printf("No se puede mover a la posicion (%d, %d)\n", pos_nueva.first, pos_nueva.second);
	}
	assert(es_posicion_valida(pos_nueva));
	// assert(es_color_libre(this->tablero[pos_nueva.first][pos_nueva.second]));

	mutex_moverse.lock();
	if (es_color_libre(this->tablero[pos_nueva.first][pos_nueva.second])){
		
		if (this->turno == ROJO){
			sem_wait(&turno_rojo);
			this->tablero[pos_anterior.first][pos_anterior.second] = VACIO;
			this->tablero[pos_nueva.first][pos_nueva.second] = ROJO;
			this->pos_jugadores_rojos[nro_jugador] = pos_nueva;
			if (pos_nueva == pos_bandera_azul) return 0;
		} else {
			sem_wait(&turno_azul);
			this->tablero[pos_anterior.first][pos_anterior.second] = VACIO;
			this->tablero[pos_nueva.first][pos_nueva.second] = AZUL;
			this->pos_jugadores_azules[nro_jugador] = pos_nueva;
			if (pos_nueva == pos_bandera_roja) return 0;
		}
		
	} else {
		if (this->turno == ROJO){
			printf("El jugador rojo %d se quiere mover a una posicion ocupada\n", nro_jugador);
		} else {
			printf("El jugador azul %d se quiere mover a una posicion ocupada\n", nro_jugador);
		}
	}
	valor_semaforo--;
	if (valor_semaforo == 0){
		termino_ronda(this->turno);
	}
	mutex_moverse.unlock();


	return nro_ronda;
}

void gameMaster::hacer_signals(color equipo) {
	switch (this->strat) {
		case SECUENCIAL:
			valor_semaforo = this->jugadores_por_equipos;
			if (equipo == ROJO){
			for(int i=0; i<valor_semaforo; i++) sem_post(&(this->limitador_movimientos_azul)[i]);
			} else {
			for(int i=0; i<valor_semaforo; i++) sem_post(&(this->limitador_movimientos_rojo)[i]);
			}
			break;
		case RR:
			valor_semaforo = quantum;
			if (equipo == ROJO){
				for(int i = 0; i< quantum; i++){
					sem_post(&limitador_movimientos_azul[i%(this->jugadores_por_equipos)]);
				}
			} else {
				for(int i = 0; i< quantum; i++){
					sem_post(&limitador_movimientos_rojo[i%(this->jugadores_por_equipos)]);
				}
			}
			break;
		case SHORTEST:
			valor_semaforo = 1;
			if (equipo == ROJO){
				for(int i=0; i<valor_semaforo; i++) sem_post(&(this->limitador_movimientos_azul)[i]);
			} else {
				for(int i=0; i<valor_semaforo; i++) sem_post(&(this->limitador_movimientos_rojo)[i]);
			}
			break;
		case USTEDES:
			//turno_rojo = 
			break;
	}
	if (equipo == AZUL){
		for(int i=0; i<valor_semaforo; i++) sem_post(&turno_rojo);
	} else {
        for(int i=0; i<valor_semaforo; i++) sem_post(&turno_azul);
		// turno_azul.signal(valor_semaforo);
	}
}

void gameMaster::termino_ronda(color equipo) {
	if (equipo == ROJO){
		printf("\033[0;33mTerminó el turno del equipo rojo\033[0;37m\n");
	} else {
		printf("\033[0;33mTerminó el turno del equipo azul\033[0;37m\n");
	}
	assert(equipo == this->turno);
	assert(valor_semaforo == 0);
	hacer_signals(equipo);
	this->nro_ronda++;
	if (equipo == ROJO){
        this->turno = AZUL;
    } else {
        this->turno = ROJO;
    }
}

bool gameMaster::termino_juego() {
	return ganador != INDEFINIDO;
}

coordenadas gameMaster::proxima_posicion(coordenadas anterior, direccion movimiento) {
	// Calcula la proxima posición a moverse (es una copia) 
	switch(movimiento) {
		case(ARRIBA):
			anterior.first--; 
			break;

		case(ABAJO):
			anterior.first++;
			break;

		case(IZQUIERDA):
			anterior.second--;
			break;

		case(DERECHA):
			anterior.second++;
			break;
	}
	return anterior; // está haciendo una copia por constructor
}

color gameMaster::obtener_coordenadas(coordenadas coord) {
    return this->tablero[coord.first][coord.second];
}

