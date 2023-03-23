#include "aed2_simulacion.h"

#include <utility>

aed2_Simulacion ::aed2_Simulacion(const aed2_Mapa &mapa, const map<Color, Coordenada> &objetos, Coordenada inicio) : _simulacion(mapa.mapa(),objetos,inicio) {

}
aed2_Simulacion ::aed2_Simulacion(const simulacion& s) : _simulacion(s){
}
simulacion aed2_Simulacion::simulacionPase() const {
    return _simulacion;
}
void aed2_Simulacion::mover(Direccion d) {
    _simulacion.mover(d);
}
void aed2_Simulacion::agregarObjetivo(Objetivo o) {
    _simulacion.agregarObjetivo(o);
}

const aed2_Mapa aed2_Simulacion::mapa() const {
    aed2_Mapa res = aed2_Mapa(_simulacion.mapa());
    return res;
}
const map<Color, Coordenada>& aed2_Simulacion::posObjetos() const {
    return this->_simulacion.devolverAuxObjetos();
}
Coordenada aed2_Simulacion::posAgente() const {
    return this-> _simulacion.posAgente();
}
Nat aed2_Simulacion::movimientos() const {
    return this -> _simulacion.movimientos();
}
Nat aed2_Simulacion::objetivosResueltos() const {
    return this->_simulacion.objetivosResueltos();
}
const list<Objetivo>& aed2_Simulacion::objetivosDisponibles() const {
    return this->_simulacion.objetivosDisponibles();
}
// completar