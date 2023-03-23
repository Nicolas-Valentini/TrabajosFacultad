
#include "Mapa.h"

Mapa::Mapa() {
    _alto = 0;
    _ancho= 0;
    vector<vector<TipoCasillero>> nuevoMapaAlturas;
    vector<vector<Color>> nuevoMapaColores;
    string_map<Coordenada> recep;
    this-> _alturas = nuevoMapaAlturas;
    this-> _receptaculos = recep;
    this-> _mapaReceptaculos = nuevoMapaColores;
}

Mapa::Mapa(Nat ancho, Nat alto, const map<Color, Coordenada>& receptaculos) {
    this->_alto = alto;
    this->_ancho = ancho;
    vector<TipoCasillero> nuevaAltura;
    for (int i = 0; i < alto; ++i) {
        nuevaAltura.push_back(PISO);
    }
    vector<vector<TipoCasillero>> nuevoMapaAlturas;
    for (int i = 0; i < ancho; ++i) {
        nuevoMapaAlturas.push_back(nuevaAltura);
    }
    this->_alturas = nuevoMapaAlturas;
    vector<Color> nuevosColores;
    for (int i = 0; i < alto; ++i) {
        nuevosColores.push_back("");
    }
    vector<vector<Color>> nuevoMapaColores;
    for (int i = 0; i < ancho; ++i) {
        nuevoMapaColores.push_back(nuevosColores);
    }
    for (pair<Color, Coordenada> c : receptaculos) {
        nuevoMapaColores[c.second.first][c.second.second] = c.first;
        this-> _receptaculos.insert(c);
    }
    this->_auxRecep = receptaculos;
    this->_mapaReceptaculos = nuevoMapaColores;
}

void Mapa::agregarRampa(Coordenada c){
    this->_alturas[c.first][c.second] = RAMPA;
}

void Mapa::agregarPared(Coordenada c){
    this->_alturas[c.first][c.second] = ELEVACION;
}

Nat  Mapa :: ancho()const{
    return this->_ancho;
}
Nat  Mapa:: alto()const{
    return this->_alto;
}
bool Mapa:: esPiso(Coordenada c) const{
    bool res = _alturas[c.first][c.second] == PISO;
    return res;
}
bool Mapa:: esRampa(Coordenada c) const{
    bool res = _alturas[c.first][c.second] == RAMPA;
    return res;
}
bool Mapa:: esPared(Coordenada c) const{
    bool res = _alturas[c.first][c.second] == ELEVACION;
    return res;
}
const string_map<Coordenada>& Mapa :: receptaculos() const{
    return this-> _receptaculos;
}

bool Mapa::enRango(Coordenada c) {
    bool res = 0 <= c.first && c.first< _alto && 0 <= c.second && c.second < _ancho;
    return res;
}
vector<vector<TipoCasillero>> Mapa ::alturas() const {
    return this->_alturas;
}
vector<vector<Color>> Mapa ::mapaReceptaculos() const {
    return this-> _mapaReceptaculos;
}
Nat Mapa::dist(Coordenada c1, Coordenada c2) {
    Nat res = (c1.first- c2.first) + (c1.second - c2.second);
    return res;
}
const map<Color, Coordenada>& Mapa:: recpCambiados() const{
    return this-> _auxRecep; //Esto es solo para la conversion a Aed2_mapa
}
