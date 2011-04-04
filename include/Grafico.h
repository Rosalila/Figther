#ifndef GRAFICO_H
#define GRAFICO_H

#include <stdlib.h>	// for itoa() call
#include <irrlicht.h>
using namespace irr;
#include "../include/MyEventReceiver.h"


class Grafico
{
    public:
    IrrlichtDevice *device;
    video::IVideoDriver* driver;
    gui::IGUIFont* font;

    Grafico(MyEventReceiver* receiver);
    void draw2DImage	(
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation , irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color ,
				 bool flipHorizontally,
				 bool flipVertically 	);

    //u32 time = device->getTimer()->getTime();
    //if(time/200 % 4==0)

};


#endif // GRAFICO_H
