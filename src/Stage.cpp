#include "../include/Stage.h"

Stage::Stage(video::ITexture* imagen_fondo,video::ITexture* imagen_barra,Grafico* grafico)
{
    this->imagen_fondo=imagen_fondo;
    this->imagen_barra=imagen_barra;
    this->grafico=grafico;
}
void Stage::dibujar()
{
    //fondo
    grafico->driver->draw2DImage(imagen_fondo, core::position2d<s32>(0,0),
                            core::rect<s32>(0,0,1024,600), 0,
                            video::SColor(255,255,255,255), true);
    //Barra
    grafico->driver->draw2DImage(imagen_barra, core::position2d<s32>(0,0),
                        core::rect<s32>(0,0,1024,600), 0,
                        video::SColor(255,255,255,255), true);
}
