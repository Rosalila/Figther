#include "../include/irrKlang/irrKlang.h"
//using namespace System;
//using namespace System.IO;
using namespace irrklang;
#include <irrlicht.h>
using namespace irr;
#include <string>
#include <vector>

class Sonido
{
    ISoundEngine *engine;
    irr::core::map<std::string,irrklang::ISoundSource*> sonidos;
public:
    Sonido();
    void drop();
    void agregarSonido(std::string variable,const ik_c8* valor);
    void reproducirSonido(std::string variable);
};
