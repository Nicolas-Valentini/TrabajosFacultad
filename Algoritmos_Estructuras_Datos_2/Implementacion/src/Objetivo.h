#ifndef OBJETIVO_H
#define OBJETIVO_H

#include "Tipos.h"

class Objetivo {
  public:
    
    Objetivo(): _colorDestino(""), _colorObjeto("") { }

    Objetivo(const Color& objeto, const Color& receptaculo): _colorDestino(receptaculo), _colorObjeto(objeto){ }

    const Color& objeto() const;
    
    const Color& receptaculo() const;
  
  private:
    //completar
    Color _colorObjeto;
    Color _colorDestino;
};

#endif
