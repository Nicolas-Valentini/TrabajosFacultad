#ifndef AED2_MAPA_H
#define AED2_MAPA_H

#include "Tipos.h"
#include "Mapa.h"


using namespace std;

using Mapa = Mapa;

class aed2_Mapa {
public:

	aed2_Mapa();
	/**
     * Pre:
     *  Todas las elevaciones están en rango. Todas las coordenadas de receptáculos
     *  están en rango y no se repiten.
     */
    aed2_Mapa(Nat ancho, Nat alto, const set<Coordenada>& elevaciones, const map<Color, Coordenada>& receptaculos);

    /**
     * Pre: 
     *  Existe c_1 adyacente a c que es piso y 
     *  existe c_2 adyacente a c que es elevación.
     */
    void agregarRampa(Coordenada c);

    Nat ancho() const;

    Nat alto() const;

    TipoCasillero tipoCasillero(Coordenada c) const;

    const map<Color, Coordenada>& receptaculos() const;

    Coordenada receptaculo(const Color& c);

	// Conversiones
    
    // Esta función sirve para convertir del Mapa implementado por ustedes
    // a la clase Mapa de la cátedra
    aed2_Mapa(Mapa m);

    // Esta función sirve para convertir del Mapa de la cátedra (aed2_Mapa)
    // a la clase Mapa definida por ustedes
    Mapa mapa() const;


private:
    Mapa _mapa;
};

#endif // AED2_MAPA_H