#include <iostream>
#include <thread>
#include <sys/unistd.h>
#include <vector>
#include <mutex>
#include "gameMaster.h"
#include "equipo.h"
#include "definiciones.h"
#include "config.h"

using namespace std;

const estrategia strat = RR;
const int quantum = 10;

int main(){
    Config config = *(new Config());

    gameMaster belcebu = gameMaster(config, strat, quantum);

    // Creo equipos (lanza procesos)
    Equipo rojo(&belcebu, ROJO, strat, config.cantidad_jugadores, quantum, config.pos_rojo);
    Equipo azul(&belcebu, AZUL, strat, config.cantidad_jugadores, quantum, config.pos_azul);

    rojo.comenzar();
    azul.comenzar();
    rojo.terminar();
    azul.terminar();

    if(belcebu.ganador == AZUL){
        printf("\033[0;33mEl equipo azul ganó la partida\033[0;37m\n");
    } else {
        printf("\033[0;33mEl equipo rojo ganó la partida\033[0;37m\n");
    }

    return 0;
}