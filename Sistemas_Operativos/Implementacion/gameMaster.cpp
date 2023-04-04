#include <sys/unistd.h>
#include <assert.h>     /* assert */
#include "gameMaster.h"

gameMaster::gameMaster(Config config, estrategia strategy, const int quantum) {
    this->strat = strategy;
	// Chequeo que el tamaño del tablero sea válido
	assert(config.x>0); 
	assert(config.y>0); 
	this->x = config.x;
	this->y = config.y;

	assert(quantum > 0);
	this->quantum = quantum;
	
	// Chequeo si las banderas estan en posiciones válidas
	assert(es_posicion_valida(config.bandera_roja)); 
	assert(es_posicion_valida(config.bandera_azul));
	assert(config.bandera_roja != config.bandera_azul);
	this->pos_bandera_roja = config.bandera_roja;
	this->pos_bandera_azul = config.bandera_azul;
	// Chequeo si la cantidad de posiciones es igual a la cantidad de jugadores
	assert(config.pos_rojo.size() == config.cantidad_jugadores);
	assert(config.pos_azul.size() == config.cantidad_jugadores);
	this->jugadores_por_equipos = config.cantidad_jugadores;
    this->pos_jugadores_rojos = config.pos_rojo;
    this->pos_jugadores_azules = config.pos_azul;
    this->jugadores_rojos_trabados = vector<bool>(this->jugadores_por_equipos);
    this->jugadores_azules_trabados = vector<bool>(this->jugadores_por_equipos);
    this->limitador_movimientos_rojo = vector<sem_t>(this->jugadores_por_equipos);
    this->limitador_movimientos_azul = vector<sem_t>(this->jugadores_por_equipos);
	this->prioridad_jugadores_azules = vector<int>(this->jugadores_por_equipos);
	this->prioridad_jugadores_rojos = vector<int>(this->jugadores_por_equipos);
	// Seteo tablero en vacio
	tablero.resize(x);
    for (int i = 0; i < x; ++i) {
        tablero[i].resize(y);
        fill(tablero[i].begin(), tablero[i].end(), VACIO);
    }
	// Agrego los jugadores al tablero
    for(auto &coord : config.pos_rojo){
		// Chequeo que las posiciones sean validas y esten libres
		assert(es_posicion_valida(coord));
        assert(es_color_libre(tablero[coord.first][coord.second]));
        this->tablero[coord.first][coord.second] = ROJO;
    }
    for(auto &coord : config.pos_azul){
		// Chequeo que las posiciones sean validas y esten libres
		assert(es_posicion_valida(coord));
        assert(es_color_libre(tablero[coord.first][coord.second]));
        this->tablero[coord.first][coord.second] = AZUL;
    }
	// Agrego las banderas al tablero
    tablero[config.bandera_roja.first][config.bandera_roja.second] = BANDERA_ROJA;
    tablero[config.bandera_azul.first][config.bandera_azul.second] = BANDERA_AZUL;
	// Empieza el rojo
	this->turno = ROJO;
	sem_init(&turno_azul, 0, 0);
	switch (strat) {
		case SECUENCIAL:

		    sem_init(&turno_rojo, 0, this->jugadores_por_equipos);
            movimientos_restantes_equipo = this->jugadores_por_equipos;

			for (int i = 0; i < movimientos_restantes_equipo; i++){
				sem_init(&(this->limitador_movimientos_rojo[i]), 0, 1);
				sem_init(&(this->limitador_movimientos_azul[i]), 0, 0);
			}
			break;
		case RR:

            sem_init(&turno_rojo, 0, quantum);
            movimientos_restantes_equipo = quantum;

			for(int i = 0; i < this->jugadores_por_equipos; i++){
				sem_init(&(this->limitador_movimientos_rojo[i]), 0, 0);
				sem_init(&(this->limitador_movimientos_azul[i]), 0, 0);
			}
			sem_post(&(this->limitador_movimientos_azul[0]));
			break;
		case SHORTEST:

            sem_init(&turno_rojo, 0, 1);
            movimientos_restantes_equipo = 1;

            sem_init(&(this->jugador_mas_cercano_rojo_encontrado), 0, 0);
            sem_init(&(this->jugador_mas_cercano_azul_encontrado), 0, 0);

			for(int i = 0; i < this->jugadores_por_equipos; i++){
				sem_init(&(this->limitador_movimientos_rojo[i]), 0, 0);
				sem_init(&(this->limitador_movimientos_azul[i]), 0, 0);
			}
			break;
		case USTEDES:
			sem_init(&turno_rojo, 0, 1);
            movimientos_restantes_equipo = 1;

			sem_init(&(this->jugador_prioritario_rojo_encontrado), 0, 0);
            sem_init(&(this->jugador_prioritario_azul_encontrado), 0, 0);

			for(int i = 0; i < this->jugadores_por_equipos; i++){
				sem_init(&(this->limitador_movimientos_rojo[i]), 0, 0);
				sem_init(&(this->limitador_movimientos_azul[i]), 0, 0);
			}
	}
	printf("\033[0;33mEl gamemaster fue inicializado con exito\033[0;37m\n");
}

bool gameMaster::es_posicion_valida(coordenadas pos) {
	return (pos.first >= 0) && (pos.first < x) && (pos.second >= 0) && (pos.second < y);
}

bool gameMaster::es_color_libre(color color_tablero){
    return color_tablero == VACIO || color_tablero == INDEFINIDO;
}

bool gameMaster::es_bandera_contraria(coordenadas pos){
    return (this->turno == ROJO && this->tablero[pos.first][pos.second] == BANDERA_AZUL) ||
    (this->turno == AZUL && this->tablero[pos.first][pos.second] == BANDERA_ROJA);
}

color gameMaster::obtener_coordenadas(coordenadas coord) {
    return this->tablero[coord.first][coord.second];
}

int gameMaster::getTamx() {
	return x;
}

int gameMaster::getTamy() {
	return y;
}

int gameMaster::mover_jugador(direccion dir, int nro_jugador) {
	coordenadas pos_nueva, pos_anterior;
	if (this->turno == ROJO){
		pos_anterior = this->pos_jugadores_rojos[nro_jugador];
	} else {
		pos_anterior = this->pos_jugadores_azules[nro_jugador];
	}
	pos_nueva = proxima_posicion(pos_anterior, dir);
	assert(es_posicion_valida(pos_nueva));


	if (es_color_libre(this->tablero[pos_nueva.first][pos_nueva.second]) || es_bandera_contraria(pos_nueva)){
		//Si el movimiento es valido, actualizar tablero, posición del jugador, y booleano que indica si el jugador esta trabado
		this->tablero[pos_anterior.first][pos_anterior.second] = VACIO;
		this->tablero[pos_nueva.first][pos_nueva.second] = this->turno;
		if (this->turno == ROJO){
//			sem_wait(&turno_rojo);
            this->jugadores_rojos_trabados[nro_jugador] = false;
			this->pos_jugadores_rojos[nro_jugador] = pos_nueva;
            if (pos_nueva == pos_bandera_azul && this->ganador == INDEFINIDO){
				this->ganador = ROJO;
                //Asegurar que cualquier jugador que haya quedado esperando un semaforo pueda terminar su thread
				liberar_jugadores();
			}
		} else {
//			sem_wait(&turno_azul);
            this->jugadores_azules_trabados[nro_jugador] = false;
			this->pos_jugadores_azules[nro_jugador] = pos_nueva;
			if (pos_nueva == pos_bandera_roja && this->ganador == INDEFINIDO){
				this->ganador = AZUL;
                //Asegurar que cualquier jugador que haya quedado esperando un semaforo pueda terminar su thread
                liberar_jugadores();
			}
		}
	} else {
        //Si el movimiento no es valido, lo loggeamos por pantalla y seteamos el booleano que indica que
        //el jugador esta trabado
		if (this->turno == ROJO){
            this->jugadores_rojos_trabados[nro_jugador] = true;
			printf("El jugador rojo %d se quiere mover en dirección %s a una posicion ocupada\n", nro_jugador, enum_a_string(dir).c_str());
		} else {
            this->jugadores_azules_trabados[nro_jugador] = true;
			printf("El jugador azul %d se quiere mover en dirección %s a una posicion ocupada\n", nro_jugador, enum_a_string(dir).c_str());
		}
	}

	return nro_ronda;
}

void gameMaster::restaurar_movimientos_restantes(color equipo) {
	switch (strat) {
		case SECUENCIAL:
            movimientos_restantes_equipo = this->jugadores_por_equipos;
			if (equipo == ROJO){
				for(int i=0; i < movimientos_restantes_equipo; i++)
					sem_post(&(this->limitador_movimientos_azul)[i]);
			} else {
				for(int i=0; i < movimientos_restantes_equipo; i++)
					sem_post(&(this->limitador_movimientos_rojo)[i]);
			}
			break;
		case RR:
            movimientos_restantes_equipo = quantum;
			if (equipo == ROJO){
				sem_post(&limitador_movimientos_azul[0]);
			} else {
				sem_post(&limitador_movimientos_rojo[0]);
			}
			break;
		case SHORTEST:
            movimientos_restantes_equipo = 1;
			if (equipo == ROJO){
				sem_post(&limitador_movimientos_azul[this->mas_cercano_azul]);
			} else {
				sem_post(&limitador_movimientos_rojo[this->mas_cercano_rojo]);
			}
			break;
		case USTEDES:
			movimientos_restantes_equipo = 1;
			if (equipo == ROJO){
				sem_post(&limitador_movimientos_azul[this->mas_prioritario_azul]);
			} else {
				sem_post(&limitador_movimientos_rojo[this->mas_prioritario_rojo]);
			}
			break;
	}
}

void gameMaster::liberar_jugadores(){
    for (int i = 0; i < this->jugadores_por_equipos; i++){
        sem_post(&limitador_movimientos_azul[i]);
        sem_post(&limitador_movimientos_rojo[i]);
    }
}

void gameMaster::termino_ronda(color equipo) {

    if(equipo_entero_trabado(ROJO) && equipo_entero_trabado(AZUL)){
        printf("Ambos equipos trabados -- la partida terminó en empate\n");
        ganador = EMPATE;
		this->liberar_jugadores();
    }
	if (equipo == ROJO){
		printf("Terminó la ronda %d, ahora es turno del equipo azul\n", this->nro_ronda);
    } else {
		printf("Terminó la ronda %d, ahora es turno del equipo rojo\n", this->nro_ronda);
	}
	assert(equipo == this->turno);
	
	this->nro_ronda++;
	this->turno = (this->turno == ROJO) ? AZUL : ROJO;

    restaurar_movimientos_restantes(equipo);

    if (equipo == AZUL){
        for(int i = 0; i < movimientos_restantes_equipo; i++){
            sem_post(&turno_rojo);
        }
    } else {
        for(int i = 0; i < movimientos_restantes_equipo; i++){
            sem_post(&turno_azul);
        }
    }
}

bool gameMaster::equipo_entero_trabado(color equipo) {

	if(strat == SHORTEST) {
        //estrategia SHORTEST. solo nos importa ver si el jugador mas cercano (el unico del equipo que se va a mover en
        //toda la partida) esta trabado
        if(equipo == ROJO){
            return this->jugadores_rojos_trabados[mas_cercano_rojo];
        } else {
            return this->jugadores_rojos_trabados[mas_cercano_rojo];
        }

    } else {
        //en el resto de las estrategias, vemos si todos los jugadores de un cierto equipo están trabados
        if (equipo == ROJO) {
            for (bool trabado: this->jugadores_rojos_trabados) {
                if (!trabado) return false;
            }
            return true;
        } else {
            for (bool trabado: this->jugadores_azules_trabados) {
                if (!trabado) return false;
            }
            return true;
        }
	}
}

string gameMaster::enum_a_string(int dir){
    switch(dir){
        case ARRIBA:
            return "ARRIBA";
        case ABAJO:
            return "ABAJO";
        case IZQUIERDA:
            return "LA IZQUIERDA";
        case DERECHA:
            return "LA DERECHA";
    }
	return "";
}

bool gameMaster::termino_juego() {
	return ganador != INDEFINIDO;
}

coordenadas gameMaster::proxima_posicion(coordenadas anterior, direccion movimiento) {
	switch(movimiento) {
		case(ARRIBA):
			anterior.first--; 
			break;

		case(ABAJO):
			anterior.first++;
			break;

		case(IZQUIERDA)://turno_rojo = 

		case(DERECHA):
			anterior.second++;
			break;
	}
	return anterior;
}