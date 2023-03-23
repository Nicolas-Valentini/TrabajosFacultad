
#include "simulacion.h"

simulacion ::simulacion(const Mapa &mapa, const map<Color, Coordenada> &objetos, Coordenada inicio) {
    this->_mapa = mapa;
    this->_posAgente = inicio;
    this->_movimientos = 0;
    this->_objetivosCompletados = 0;
    list<Objetivo> vacio;
    this->_objetivosDisponibles = vacio;
    string_map<string_map<_List_iterator<Objetivo>>> nuevo;
    this->_objetivoAuxiliar = nuevo;

    vector<Color> nuevosColores;
    for (int i = 0; i < _mapa.alto(); ++i) {
        nuevosColores.push_back("");
    }
    vector<vector<Color>> nuevoMapaObjetos;
    for (int i = 0; i < _mapa.ancho(); ++i) {
        nuevoMapaObjetos.push_back(nuevosColores);
    }
    for (pair<Color, Coordenada> c : objetos) {
        nuevoMapaObjetos[c.second.first][c.second.second] = c.first;
        this-> _losObjetos.insert(c);
    }
    this->_mapaDeObjetos= nuevoMapaObjetos;
    this->_auxObjetos = objetos;
}

void simulacion :: agregarObjetivo( const Objetivo& o){
    _List_iterator<Objetivo> n = _objetivosDisponibles.insert(_objetivosDisponibles.cend(),o);
    if (_objetivoAuxiliar.count(o.objeto()) == 0){
        string_map<_List_iterator<Objetivo>> aux;
        _objetivoAuxiliar.insert(make_pair(o.objeto(),aux));
    }
    string_map<_List_iterator<Objetivo>> aux = _objetivoAuxiliar.at(o.objeto());
    aux.insert(make_pair(o.receptaculo(), n));
    _objetivoAuxiliar.insert(make_pair(o.objeto(), aux));
    if (cumpleObjetivo(o.objeto(), o.receptaculo())) {
        _objetivosCompletados ++;
        cambiaObjetivos(o.objeto(), o.receptaculo());
    }
}

bool simulacion:: cumpleObjetivo(const Color& objeto, const Color& receptaculo){
    bool res = false;
    if (this->_objetivoAuxiliar.count(objeto) == 1){
        if(this->_objetivoAuxiliar.at(objeto).count(receptaculo) == 1){
            res = (this->_losObjetos.at(objeto) == _mapa.receptaculos().at(receptaculo));
        }
    }
    return res;
}

void simulacion:: cambiaObjetivos(const Color& objeto, const Color& receptaculo){
    _List_iterator<Objetivo> aEliminar = _objetivoAuxiliar.at(objeto).at(receptaculo);
    _objetivosDisponibles.erase(aEliminar);
    _objetivoAuxiliar.at(objeto).erase(receptaculo);
    if(this->_objetivoAuxiliar.at(objeto).empty()){
        this->_objetivoAuxiliar.erase(objeto);
    }
}

void simulacion:: mover(Direccion d){
    if(_mapa.enRango(siguientePos(_posAgente,d))){
        _movimientos ++ ;
        if(esMovLegal(d)){
            _posAgente = siguientePos(_posAgente,d);
            if(mueveObjetoLegal(d)){
                Color objeto = _mapaDeObjetos[_posAgente.first][_posAgente.second];
                moverObjeto(objeto,d);
                Coordenada aux = siguientePos(_posAgente, d);
                Color recep = _mapa.mapaReceptaculos()[aux.first][aux.second];
                if(cumpleObjetivo(objeto,recep)){
                    cambiaObjetivos(objeto,recep);
                    _objetivosCompletados ++;
                }
            }
        }
    }


}

bool simulacion:: hayMovimiento(Coordenada c, Direccion d){
    bool res = false;
    if(_mapa.enRango(siguientePos(c,d))){
        if(_mapa.esPared(siguientePos(c,d))){
            return _mapa.esRampa(c);
        }
        else{
            res = true;
        }
    }
    return res;
}

bool simulacion :: esMovLegal(Direccion d){
    bool res = false;
    if(hayMovimiento(_posAgente, d)){
        if(hayObjeto(siguientePos(_posAgente, d))){
            if(hayMovimiento(siguientePos(_posAgente,d), d)){
                return !(hayObjeto(siguientePos(siguientePos(_posAgente,d),d)));
            }
        }
        else{
            res = true;
        }
    }
    return res;
}

bool simulacion::mueveObjetoLegal(Direccion d){
    bool res = false;
    bool resAux = hayObjeto(_posAgente) && hayMovimiento(_posAgente, d);
    if(resAux){
        res = !hayObjeto(siguientePos(_posAgente,d));
    }
    return res;
}

Coordenada simulacion:: siguientePos(Coordenada c, Direccion d){
    if(d ==ARRIBA){
        c.second ++;
    }
    else if(d == ABAJO){
        c.second --;
    }
    else if(d == DERECHA){
        c.first ++;
    }
    else if(d == IZQUIERDA){
        c.first --;
    }
    return c;
}

bool simulacion::hayObjeto(Coordenada c) {
    bool aux = _mapaDeObjetos[c.first][c.second] != "";
    return aux;
}


void simulacion:: moverObjeto(const Color& objeto, Direccion d){
    Coordenada c = _losObjetos.at(objeto);
    _mapaDeObjetos[c.first][c.second] = "";
    _losObjetos.insert(make_pair(objeto, siguientePos(c,d)));
    c = _losObjetos.at(objeto);
    _mapaDeObjetos[c.first][c.second] = objeto;
    _auxObjetos.erase(objeto);    //auxObjetos se utiliza solo para devolverlo en Aed2_simulacion
    _auxObjetos.insert(make_pair(objeto,c));
}

Coordenada simulacion::posObjeto(const Color& c) {
    return _losObjetos.at(c);
}


const Mapa simulacion::mapa() const {
    return this-> _mapa;
}
const string_map<Coordenada>& simulacion::posObjetos() const {
    return this->_losObjetos;
}
Coordenada simulacion::posAgente() const {
    return this-> _posAgente;
}
Nat simulacion::movimientos() const {
    return this -> _movimientos;
}
Nat simulacion::objetivosResueltos() const {
    return this->_objetivosCompletados;
}
const list<Objetivo>& simulacion::objetivosDisponibles() const {
    return this-> _objetivosDisponibles;
}

vector<vector<Color>> simulacion::mapaObjetos() {
    return this -> _mapaDeObjetos;
}
void simulacion::cambiarMovimientos(Nat n) {
    this-> _movimientos= n;
}
void simulacion ::cambiarObjetivosCompletados(Nat n) {
    this -> _objetivosCompletados=n;
}

const map<Color,Coordenada>& simulacion ::devolverAuxObjetos() const{
    return this-> _auxObjetos;
}

