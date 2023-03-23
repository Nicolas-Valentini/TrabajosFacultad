#ifndef AED2_SIMULACION_H
#define AED2_SIMULACION_H

#include "Tipos.h"
#include "aed2_mapa.h"
#include "Objetivo.h"
#include "simulacion.h"

using simulacion = simulacion;

class aed2_Simulacion {
public:

    /**
     * Pre:
     *  > inicio está en contenido en mapa
     *  > las coordenadas en objetos estan en mapa y no se repiten
     *  > las coordenadas en objetos no se solapan con la posición del agente
     */
    aed2_Simulacion(const aed2_Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio);

    void mover(Direccion);

    void agregarObjetivo(Objetivo o);

    const aed2_Mapa mapa() const;

    const map<Color, Coordenada>& posObjetos() const;

    Coordenada posAgente() const;

    const list<Objetivo>& objetivosDisponibles() const;

    Nat movimientos() const;
    
    Nat objetivosResueltos() const;

    aed2_Simulacion(const simulacion& s);

    simulacion simulacionPase() const;


private:
    simulacion _simulacion;
};

#endif // AED2_SIMULACION_H
