
#ifndef TP3_ALGO2LANDIA_MAPA_H
#define TP3_ALGO2LANDIA_MAPA_H
#include "Tipos.h"


using namespace std;

class Mapa {
public:
    Mapa();
    /**
     * Pre:
     *  Todas las elevaciones están en rango. Todas las coordenadas de receptáculos
     *  están en rango y no se repiten.
     */
    Mapa(Nat ancho, Nat alto, const map<Color, Coordenada>& receptaculos);

    /**
     * Pre:
     *  Existe c_1 adyacente a c que es piso y
     *  existe c_2 adyacente a c que es elevación.
     */
    void agregarPared(Coordenada c);

    void agregarRampa(Coordenada c);

    Nat ancho() const;

    Nat alto() const;

    bool enRango(Coordenada c);

    bool esPiso(Coordenada c) const;

    bool esPared(Coordenada c) const;

    bool esRampa(Coordenada c) const;

    const string_map<Coordenada>& receptaculos() const;

    vector<vector<TipoCasillero>> alturas() const;

    vector<vector<Color>> mapaReceptaculos() const;

    const map<Color, Coordenada>& recpCambiados() const;

    Nat dist(Coordenada c1, Coordenada c2);

private:
    Nat _alto;
    Nat _ancho;
    map<Color, Coordenada> _auxRecep;
    string_map<Coordenada> _receptaculos;
    vector<vector<TipoCasillero>> _alturas;
    vector<vector<Color>> _mapaReceptaculos;
};


#endif //TP3_ALGO2LANDIA_MAPA_H
