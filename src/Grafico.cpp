#include "../include/Grafico.h"

Grafico::Grafico(MyEventReceiver* receiver)
{
    video::E_DRIVER_TYPE driverType;
    driverType = video::EDT_OPENGL;
    //driverType = video::EDT_SOFTWARE;
    device = createDevice(driverType,core::dimension2d<u32>(1024, 600),true ,false, false, false, receiver);
    if (device == 0)
        return; // could not create selected driver.
    core::array<SJoystickInfo> joystickInfo;
    device->activateJoysticks(joystickInfo);
    device->setWindowCaption(L"Fighter");
    driver = device->getVideoDriver();

    //init fonts
    font = device->getGUIEnvironment()->getFont("resources/Menu/Font/bigfont.png");
}

void Grafico::draw2DImage
                (
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation , irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color ,
				 bool flipHorizontally,
				 bool flipVertically 	)
{
   if(!texture)
	   return;

   irr::video::SMaterial material;

   irr::core::vector2df corner[4];

   corner[0] = irr::core::vector2df(position.X,position.Y);
   corner[1] = irr::core::vector2df(position.X+size.Width*scale.X,position.Y);
   corner[2] = irr::core::vector2df(position.X,position.Y+size.Height*scale.Y);
   corner[3] = irr::core::vector2df(position.X+size.Width*scale.X,position.Y+size.Height*scale.Y);


   if (rotation != 0.0f)
      for (int x = 0; x < 4; x++)
         corner[x].rotateBy(rotation,irr::core::vector2df(rotationPoint.X, rotationPoint.Y));


   //TODO: ver como mejorar esto
   irr::core::vector2df uvCorner[4];

   if(!flipVertically && !flipHorizontally)
   {
	   uvCorner[0] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[1] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[2] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[3] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }
   else if(!flipVertically && flipHorizontally)
   {
	   uvCorner[1] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[0] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[3] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[2] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }
   else if(flipVertically && !flipHorizontally)
   {
	   uvCorner[2] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[3] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[0] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[1] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }
   else
   {
	   uvCorner[3] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[2] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[1] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[0] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }


   for (int x = 0; x < 4; x++) {
      float uvX = uvCorner[x].X/(float)texture->getSize().Width;
      float uvY = uvCorner[x].Y/(float)texture->getSize().Height;
      uvCorner[x] = irr::core::vector2df(uvX,uvY);
   }


   irr::video::S3DVertex vertices[4];
   irr::u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };


   float screenWidth = (float)driver->getScreenSize().Width;
   float screenHeight = (float)driver->getScreenSize().Height;
   for (int x = 0; x < 4; x++) {
      float screenPosX = ((corner[x].X/screenWidth)-0.5f)*2.0f;
      float screenPosY = ((corner[x].Y/screenHeight)-0.5f)*-2.0f;
      vertices[x].Pos = irr::core::vector3df(screenPosX,screenPosY,1);
      vertices[x].TCoords = uvCorner[x];
      vertices[x].Color = color;
   }
   material.Lighting = false;
   material.ZWriteEnable = false;
   material.TextureLayer[0].Texture = texture;

   if (useAlphaChannel)
      material.MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
   else
      material.MaterialType = irr::video::EMT_SOLID;


   driver->setMaterial(material);
   driver->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);
   //driver->drawPixel(100,100,color);
}
