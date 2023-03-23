#include "aed2_mapa.h"

#include <utility>

aed2_Mapa ::aed2_Mapa() {
    Mapa res;
    *this = aed2_Mapa(res);
}

aed2_Mapa ::aed2_Mapa(Nat ancho, Nat alto, const set<Coordenada>& elevaciones, const map<Color, Coordenada>& receptaculos) {
    Mapa res = Mapa(ancho,alto,receptaculos);
    for (Coordenada  c: elevaciones) {
        res.agregarPared(c);
    }
    *this = aed2_Mapa(res);
}

void aed2_Mapa::agregarRampa(Coordenada c){
    _mapa.agregarRampa(c);
}

Nat  aed2_Mapa :: ancho()const{
    return this->_mapa.ancho();
}
Nat  aed2_Mapa :: alto()const{
    return this->_mapa.alto();
}
TipoCasillero  aed2_Mapa :: tipoCasillero(Coordenada c) const{
    TipoCasillero res = _mapa.alturas()[c.first][c.second];
    return res;
}
const map<Color, Coordenada>& aed2_Mapa :: receptaculos() const{
    return _mapa.recpCambiados();
}
Coordenada aed2_Mapa::receptaculo(const Color& c) {
    return _mapa.receptaculos().at(c);
}

aed2_Mapa::aed2_Mapa(Mapa m) {
    this->_mapa = m;
}
Mapa aed2_Mapa::mapa() const {
    return _mapa;
}
