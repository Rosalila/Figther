#include "../include/Sonido.h"

Sonido::Sonido()
{
    engine=createIrrKlangDevice();
}
void Sonido::drop()
{
    engine->drop();
}
void Sonido::agregarSonido(std::string variable,const ik_c8* valor)
{

    sonidos[variable]=engine->addSoundSourceFromFile(valor);;
}
void Sonido::reproducirSonido(std::string variable)
{
    engine->play2D(sonidos[variable]);
}
