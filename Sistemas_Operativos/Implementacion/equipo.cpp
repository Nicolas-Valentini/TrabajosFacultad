#include "equipo.h"
#include <assert.h> 


Equipo::Equipo(gameMaster *belcebu, color equipo, estrategia strat, int cant_jugadores, int quantum, vector<coordenadas> posiciones) {
	this->belcebu = belcebu;
	this->equipo = equipo;
	this->contrario = (equipo == ROJO)? AZUL : ROJO;
	this->bandera_contraria = (equipo==ROJO)? BANDERA_AZUL : BANDERA_ROJA;
	this->strat = strat;
	this->quantum = quantum;
	this->quantum_restante = quantum;
	this->cant_jugadores = cant_jugadores;
	
	// Para que no empiecen a jugar antes de encontrar la bandera contraria
    sem_init(&(this->bandera_contraria_encontrada), 0, 0);
	if (this->equipo == ROJO) printf("\033[0;33mEl equipo rojo fue inicializado con exito\033[0;37m\n");
	else printf("\033[0;33mEl equipo azul fue inicializado con exito\033[0;37m\n");
}

direccion Equipo::apuntar_a(coordenadas pos1, coordenadas pos2) {
	if (pos1.first > pos2.first){
        return ARRIBA;
    }
	if (pos1.first < pos2.first) {
        return ABAJO;
	}
	if (pos1.second > pos2.second) {
        return IZQUIERDA;
	}
	else {
        return DERECHA;
    }
}

void Equipo::jugador(int nro_jugador){
    if (this->equipo == ROJO){
        printf("\033[0;31mJugador %d entró a la función jugador\033[0;37m\n", nro_jugador);
    } else {
        printf("\033[0;34mJugador %d entró a la función jugador\033[0;37m\n", nro_jugador);
    }

    direccion dir;

    while(!this->belcebu->termino_juego()){
        //Cada jugador espera su turno dentro de cada ronda y, de no haber terminado la partida, determina a donde
        //moverse.
        if (this->equipo == ROJO){
            sem_wait(&(this->belcebu->limitador_movimientos_rojo)[nro_jugador]);
            if (!this->belcebu->termino_juego()){
                dir = apuntar_a(this->belcebu->pos_jugadores_rojos[nro_jugador], this->pos_bandera_contraria);
                printf("\033[0;31mJugador %d se movió hacia %s desde (%d, %d) porque la bandera enemiga está en (%d, %d)\033[0;37m\n", nro_jugador, this->belcebu->enum_a_string(dir).c_str(), this->belcebu->pos_jugadores_rojos[nro_jugador].first, this->belcebu->pos_jugadores_rojos[nro_jugador].second, this->pos_bandera_contraria.first, this->pos_bandera_contraria.second);
            }
        } else {
            sem_wait(&(this->belcebu->limitador_movimientos_azul)[nro_jugador]);
            if (!this->belcebu->termino_juego()){
                dir = apuntar_a(this->belcebu->pos_jugadores_azules[nro_jugador], this->pos_bandera_contraria);
                printf("\033[0;34mJugador %d se movió hacia %s desde (%d, %d) porque la bandera enemiga está en (%d, %d)\033[0;37m\n", nro_jugador, this->belcebu->enum_a_string(dir).c_str(), this->belcebu->pos_jugadores_azules[nro_jugador].first, this->belcebu->pos_jugadores_azules[nro_jugador].second, this->pos_bandera_contraria.first, this->pos_bandera_contraria.second);
            }
        }

        this->belcebu->mutex_movimiento.lock();

        if (!this->belcebu->termino_juego()){
            this->belcebu->mover_jugador(dir, nro_jugador);
        }
        this->belcebu->movimientos_restantes_equipo--;


        //En RR un equipo debe, tras mover un jugador, hacer post del jugador siguiente si sigue teniendo movimientos
        //restantes. Las otras estrategias no necesitan hacer nada más después de moverse; todos los posts ya fueron
        //hechos al principio de la ronda.
        if(strat == RR && this->belcebu->movimientos_restantes_equipo > 0){
            if(this->belcebu->turno == ROJO){
                sem_post(&(this->belcebu->limitador_movimientos_rojo)[(nro_jugador + 1) % this->belcebu->jugadores_por_equipos]);
            } else {
                sem_post(&(this->belcebu->limitador_movimientos_azul)[(nro_jugador + 1) % this->belcebu->jugadores_por_equipos]);
            }
			
        }

        //En nuestra propia estrategia, un equipo debe actualizar las prioridades de cada jugador, e identificar el
        //nuevo jugador prioritario
		if(strat == USTEDES ){
			for(int i=0; i < this->cant_jugadores; i++){
				if (this->equipo == ROJO){
					this->belcebu->prioridad_jugadores_rojos[i]++;
				} else {
					this->belcebu->prioridad_jugadores_azules[i]++;
				}
			}
			if (this->equipo == ROJO){
				this->belcebu->prioridad_jugadores_rojos[nro_jugador] -= 10;
			} else {
				this->belcebu->prioridad_jugadores_azules[nro_jugador] -= 10;
			}

			int mas_prioritario = buscar_jugador_prioritario();
			if (this->equipo == ROJO){
				this->belcebu->mas_prioritario_rojo = mas_prioritario;
			} else {
				this->belcebu->mas_prioritario_azul = mas_prioritario;
			}
		}

        //En cualquier caso, terminamos la ronda cuando el equipo en turno se haya quedado sin movimientos
        if (this->belcebu->movimientos_restantes_equipo == 0 && !this->belcebu->termino_juego()){
            this->belcebu->termino_ronda(this->belcebu->turno);
        }

        this->belcebu->mutex_movimiento.unlock();
	}
}


//Para USTEDES
int Equipo::buscar_jugador_prioritario(){
    int mas_prioritario = 0;
    int max_prioridad = 0;
    for (int i = 0; i < this->cant_jugadores; i++){
        if (this->equipo == ROJO){
            if (this->belcebu->prioridad_jugadores_rojos[i] > max_prioridad){
                max_prioridad = this->belcebu->prioridad_jugadores_rojos[i];
                mas_prioritario = i;
            }
        } else {
            if (this->belcebu->prioridad_jugadores_azules[i] > max_prioridad){
                max_prioridad = this->belcebu->prioridad_jugadores_azules[i];
                mas_prioritario = i;
            }
        }
    }
    return mas_prioritario;
}

//Para SHORTEST
void Equipo::buscar_jugador_mas_cercano(){
	printf("Buscando jugador más cercano\n");
	int min_dist = 1e9;
	int jugador_mas_cercano = -1;
	int dist;
	if (this->equipo == ROJO){
		for (int i = 0; i < this->cant_jugadores; i++){
			dist = this->distancia(this->belcebu->pos_jugadores_rojos[i], this->pos_bandera_contraria);
			if (dist < min_dist){
				min_dist = dist;
				jugador_mas_cercano = i;
			}
		}
	} else {
		for (int i = 0; i < this->cant_jugadores; i++){
			dist = this->distancia(this->belcebu->pos_jugadores_azules[i], this->pos_bandera_contraria);
			if (dist < min_dist){
				min_dist = dist;
				jugador_mas_cercano = i;
			}
		}
	}
	this->jugador_mas_cercano = jugador_mas_cercano;

    //Implementamos el punto de encuentro, donde ambos equipos esperan a que ambos hayan encontrado su jugador más
    //cercano a la bandera contraria
	if (this->equipo == ROJO){

        sem_post(&(this->belcebu->jugador_mas_cercano_rojo_encontrado));
        sem_wait(&(this->belcebu->jugador_mas_cercano_azul_encontrado));

		printf("\033[0;31mEl jugador más cercano a la bandera enemiga es el jugador %d, que está a distancia %d \033[0;37m\n", this->jugador_mas_cercano, min_dist);
		this->belcebu->mas_cercano_rojo = this->jugador_mas_cercano;
		sem_post(&(this->belcebu->limitador_movimientos_rojo)[this->jugador_mas_cercano]);
	} else {

        sem_post(&(this->belcebu->jugador_mas_cercano_azul_encontrado));
        sem_wait(&(this->belcebu->jugador_mas_cercano_rojo_encontrado));

		printf("\033[0;34mEl jugador más cercano a la bandera enemiga es el jugador %d, que está a distancia %d \033[0;37m\n", this->jugador_mas_cercano, min_dist);
		this->belcebu->mas_cercano_azul = this->jugador_mas_cercano;
	}
}

void Equipo::buscar_bandera_contraria(int i) {
	if (this->equipo == ROJO){
		printf("\033[0;31mJugador %d buscando bandera contraria\033[0;37m\n", i);
	} else {
		printf("\033[0;34mJugador %d buscando bandera contraria\033[0;37m\n", i);
	}
    int tam = (this->belcebu->x) * (this->belcebu->y);
    int mov_restantes = tam / (this->belcebu->jugadores_por_equipos);
    int celda = mov_restantes * i;
    coordenadas pos = {celda / this->belcebu->x, celda % this->belcebu->x};
    color color_pos;
    while(mov_restantes > 0 && !(this->encontrado)){
        pos.second++;
        if (pos.second > this->belcebu->y-1){
            pos.second = 0;
            pos.first++;
			if (pos.first == this->belcebu->x){
				break;
			}
        }
		color_pos = this->belcebu->obtener_coordenadas(pos);
		if (this->equipo == ROJO){
			if (color_pos == BANDERA_AZUL) {
				printf("\033[0;33mEl equipo rojo encontró la bandera en (%d, %d)\033[0;37m\n", pos.first, pos.second);
				this->pos_bandera_contraria = pos;
				if(this->strat == SHORTEST) this->buscar_jugador_mas_cercano();
				if(this->strat == USTEDES) this->inicializar_prioridades();
				this->encontrado = true;
				for(int i = 0; i < this->cant_jugadores; i++){
					sem_post(&(this->bandera_contraria_encontrada));
				}
				break;
			}
		} else {
			if (color_pos == BANDERA_ROJA) {
				printf("\033[0;33mEl equipo azul encontró la bandera en (%d, %d)\033[0;37m\n", pos.first, pos.second);
				this->pos_bandera_contraria = pos;
				if(this->strat == SHORTEST) this->buscar_jugador_mas_cercano();
				if(this->strat == USTEDES) this->inicializar_prioridades();
				this->encontrado = true;
				for(int i = 0; i < this->cant_jugadores; i++){
					sem_post(&(this->bandera_contraria_encontrada));
				}
				break;
			}
		}
		mov_restantes--;
    }
    sem_wait(&(this->bandera_contraria_encontrada));
    this->jugador(i);
}

//Para USTEDES
void Equipo::inicializar_prioridades(){
	int dist_max = 0;
	int jugador_mas_lejano = 0;
	int dist_aux;
	for(int i=0; i<this->cant_jugadores; i++){
		if(this->equipo == ROJO){
			dist_aux = this->distancia(this->belcebu->pos_jugadores_rojos[i], this->pos_bandera_contraria);			
		}
		if(this->equipo == AZUL){
			dist_aux = this->distancia(this->belcebu->pos_jugadores_azules[i], this->pos_bandera_contraria);
		}
		if(dist_aux > dist_max){
			jugador_mas_lejano = i;
			dist_max = dist_aux;
		}
	}
	int jugador_prioritario = 0;
	int max_prioridad = 0;
	for(int i=0; i<this->cant_jugadores; i++){
		if(this->equipo == ROJO){
			dist_aux = this->distancia(this->belcebu->pos_jugadores_rojos[i], this->pos_bandera_contraria);	
			this->belcebu->prioridad_jugadores_rojos[i] = dist_max - dist_aux;
			if (dist_max - dist_aux > max_prioridad){
				max_prioridad = dist_max - dist_aux;
				jugador_prioritario = i;
			}
		}
		if(this->equipo == AZUL){
			dist_aux = this->distancia(this->belcebu->pos_jugadores_azules[i], this->pos_bandera_contraria);
			this->belcebu->prioridad_jugadores_azules[i] = dist_max - dist_aux;
			if (dist_max - dist_aux > max_prioridad){
				max_prioridad = dist_max - dist_aux;
				jugador_prioritario = i;
			}
		}
	}
	if(this->equipo == ROJO){
		this->belcebu->mas_prioritario_rojo = jugador_prioritario;
		sem_post(&(this->belcebu->jugador_prioritario_rojo_encontrado));
        sem_wait(&(this->belcebu->jugador_prioritario_azul_encontrado));
	} else {
		this->belcebu->mas_prioritario_azul = jugador_prioritario;
		sem_post(&(this->belcebu->jugador_prioritario_azul_encontrado));
        sem_wait(&(this->belcebu->jugador_prioritario_rojo_encontrado));
	}
	if (this->equipo == AZUL){
        sem_post(&(this->belcebu->limitador_movimientos_rojo[this->belcebu->mas_prioritario_rojo]));
    }
}

void Equipo::comenzar() {
	for(int i = 0; i < cant_jugadores; i++) {
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

int Equipo::distancia(coordenadas a, coordenadas b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}