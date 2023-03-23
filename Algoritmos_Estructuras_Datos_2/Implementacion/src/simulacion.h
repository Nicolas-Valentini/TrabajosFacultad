
#ifndef TP3_ALGO2LANDIA_SIMULACION_H
#define TP3_ALGO2LANDIA_SIMULACION_H

#include "Tipos.h"
#include "Mapa.h"
#include "Objetivo.h"

class simulacion{
public:

    /**
     * Pre:
     *  > inicio está en contenido en mapa
     *  > las coordenadas en objetos estan en mapa y no se repiten
     *  > las coordenadas en objetos no se solapan con la posición del agente
     */
    simulacion(const Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio);


    void mover(Direccion);

    void agregarObjetivo(const Objetivo&);

    const Mapa mapa() const;

    const string_map<Coordenada>& posObjetos() const;

    Coordenada posAgente() const;

    const list<Objetivo>& objetivosDisponibles() const;

    Nat movimientos() const;

    Nat objetivosResueltos() const;

    Coordenada posObjeto(const Color& c);

    vector<vector<Color>> mapaObjetos();

    bool cumpleObjetivo(const Color& o, const Color& r);

    void cambiaObjetivos(const Color& o, const Color& r);

    bool hayMovimiento(Coordenada c, Direccion d);

    bool hayObjeto(Coordenada c);

    bool esMovLegal(Direccion d);

    bool mueveObjetoLegal(Direccion d);

    Coordenada siguientePos(Coordenada c, Direccion d);

    void moverObjeto(const Color& o, Direccion d);

    void cambiarMovimientos(Nat n);

    void cambiarObjetivosCompletados(Nat n);

    const map<Color,Coordenada>& devolverAuxObjetos() const;

private:
    Nat _movimientos;
    Nat _objetivosCompletados;
    Coordenada _posAgente;
    Mapa _mapa;
    list<Objetivo> _objetivosDisponibles;
    string_map<string_map<_List_iterator<Objetivo>>> _objetivoAuxiliar;
    vector<vector<Color>> _mapaDeObjetos;
    string_map< Coordenada> _losObjetos;
    map<Color,Coordenada>_auxObjetos;

};



#endif //TP3_ALGO2LANDIA_SIMULACION_H

