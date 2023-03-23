//
// Created by fedet on 8/11/2021.
//

#ifndef TP3_ALGO2LANDIA_STRING_MAP_HPP
#define TP3_ALGO2LANDIA_STRING_MAP_HPP

#include "string_map.h"

template <typename T>
string_map<T>::string_map(){
    _raiz= nullptr;
    _size=0;
}



template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
    this->~string_map();
    this->_size = d.size();
    this->_raiz = copiaRaiz(d._raiz);
    return *this;
}

template <typename T>
typename :: string_map<T>::Nodo* :: string_map<T>:: copiaRaiz(Nodo* n){
    if(n == nullptr){
        return nullptr;
    }
    else{
        Nodo* res = new Nodo();
        if(n->definicion != nullptr){
            res->definicion = new T(*n->definicion);
        }
        for (int i = 0; i < n->siguientes.size(); ++i) {
            res->siguientes[i] = copiaRaiz(n->siguientes[i]);
        }
        return res;
    }
}


template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
    _raiz->destruir(_raiz);
}


template <typename T>
void :: string_map<T> :: Nodo :: destruir(Nodo* n){
    if(n != nullptr){
        for (int i = 0; i < n->siguientes.size(); ++i) {
            if(n->siguientes[i] != nullptr){
                destruir(n->siguientes[i]);
            }
        }
        if(n->definicion != nullptr){
            delete(n->definicion);
        }
        delete(n);
    }
    else{
        delete(n);
    }
}


template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    // COMPLETAR
    if(_size==0){
        return 0;
    }

    Nodo* x =_raiz;
    for (char c : clave) {
        if(x->siguientes[c] != nullptr){
            x = x->siguientes[c];
        }
        else{
            return 0;
        }
    }
    if(x->definicion != nullptr){
        return 1;
    }
    return 0;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& claveValor) {
    // COMPLETA


    if(_raiz == nullptr){
        _raiz = new Nodo();
    }
    Nodo* x = _raiz;
    if(count(claveValor.first) == 1){
        for (char c : claveValor.first) {
            x = x->siguientes[c];
        }
    }
    else{
        _size ++;
        for (char c : claveValor.first) {
            if(x->siguientes[c] == nullptr){
                x->siguientes[c] = new Nodo();
            }
            x= x->siguientes[c];
        }
    }
    if(x->definicion != nullptr){
        delete(x->definicion);
    }
    x->definicion = new T(claveValor.second);
}


template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
    Nodo* x =_raiz;
    for (char c : clave) {
        x = x->siguientes[c];
    }
    return *(x->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
    Nodo* x =_raiz;
    for (char c : clave) {
        x = x->siguientes[c];
    }
    return *(x->definicion);
}



template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
    _size --;
    Nodo* first = _raiz;
    Nodo* last = _raiz;
    int ultindex = -1;
    for (char c: clave){
        for(int i = 0; i < first->siguientes.size(); i++){
            if(first->siguientes[i] != nullptr){
                last = first;
                ultindex = c;
            }
        }
        first = first->siguientes[c];
    }
    for(int i = 0; i < first->siguientes.size(); i++){
        if(first->siguientes[i] != nullptr){
            last = first;
        }
    }
    delete first->definicion;
    first->definicion= nullptr;
    if (last != first ){
        last->destruir(last->siguientes[ultindex]);
        last->siguientes[ultindex] = nullptr;
    }

}

template <typename T>
int string_map<T>::size() const{
    return this->_size;
}

template <typename T>
bool string_map<T>::empty() const{
    bool res = _size == 0;
    return res;
}


#endif //TP3_ALGO2LANDIA_STRING_MAP_HPP
