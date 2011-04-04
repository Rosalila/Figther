#include "../include/Menu.h"
Menu::Menu(Stage* stage,Personaje *pa,Personaje *pb,ISoundEngine* engine_sonido,Grafico* grafico,MyEventReceiver* receiver)
{
    this->stage=stage;
    this->pa=pa;
    this->pb=pb;
    this->engine_sonido=engine_sonido;
    this->grafico=grafico;
    this->receiver=receiver;
}

void Menu::loopMenu()
{
    const SEvent::SJoystickEvent & joystickData = receiver->GetJoystickState();
    int moveHorizontal =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    int moveVertical =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
    //Joystick
    irrklang::ISoundSource* shootSound = engine_sonido->addSoundSourceFromFile("resources/Menu/Sonido/intro.ogg");
    engine_sonido->play2D(shootSound);
    bool flag_boton_arriba;
    for(int i=0;i<190;i++)
    {
        dibujarImagen(grafico->driver->getTexture("/home/userr/CodeblocksProjects/fighter/resources/Menu/intro_rosalila.png"));
        if(receiver->IsKeyDown(irr::KEY_KEY_Y)||joystickData.IsButtonPressed(0))
            break;
    }
    flag_boton_arriba=false;
    for(int i=0;i<190;i++)
    {
        dibujarImagen(grafico->driver->getTexture("/home/userr/CodeblocksProjects/fighter/resources/Menu/intro_cria.jpg"));
        if(!receiver->IsKeyDown(irr::KEY_KEY_Y)&&!joystickData.IsButtonPressed(0))
            flag_boton_arriba=true;
        else if((receiver->IsKeyDown(irr::KEY_KEY_Y)||joystickData.IsButtonPressed(0)) && flag_boton_arriba)
            break;
    }
    flag_boton_arriba=false;
    int opcion=1;
    int opcion_stage=1;
    for(;;)
    {
        dibujarMenu(grafico->driver->getTexture("/home/userr/CodeblocksProjects/fighter/resources/Menu/menu_principal.jpg"),opcion,opcion_stage);
        moveHorizontal =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
        moveVertical =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
        if(!receiver->IsKeyDown(irr::KEY_KEY_Y)&&!joystickData.IsButtonPressed(0)&&moveVertical==0&&moveHorizontal==0)
            flag_boton_arriba=true;
        else if((receiver->IsKeyDown(irr::KEY_KEY_Y)||joystickData.IsButtonPressed(0)) && flag_boton_arriba)
            break;
        if(moveVertical>0 && flag_boton_arriba)
        {
            opcion--;
            flag_boton_arriba=false;
        }
        if(moveVertical<0 && flag_boton_arriba)
        {
            opcion++;
            flag_boton_arriba=false;
        }
        if(moveHorizontal>0 && flag_boton_arriba)
        {
            opcion_stage++;
            flag_boton_arriba=false;
        }
        if(moveHorizontal<0 && flag_boton_arriba)
        {
            opcion_stage--;
            flag_boton_arriba=false;
        }
    }
    if(opcion_stage==1)
        stage->imagen_fondo=grafico->driver->getTexture("/home/userr/CodeblocksProjects/fighter/resources/Stages/Stage01.jpg");
    if(opcion_stage==2)
        stage->imagen_fondo=grafico->driver->getTexture("/home/userr/CodeblocksProjects/fighter/resources/Stages/Stage02.jpg");
}


bool Menu::dibujarImagen(video::ITexture* imagen)
{
    if (grafico->device->isWindowActive())
    {
        grafico->driver->beginScene(true, true, video::SColor(255,255,255,255));
    grafico->draw2DImage
    (
        imagen,
        irr::core::dimension2d<irr::f32> (1024,600),
        irr::core::rect<irr::f32>(0,0,1024,600),
        irr::core::position2d<irr::f32>(0,0),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (1,1),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);

        grafico->driver->endScene();
    }
    return grafico->device->run() && grafico->driver;
}

bool Menu::dibujarMenu(video::ITexture* imagen,int opcion,int opcion_stage)
{
    if (grafico->device->isWindowActive())
    {
        grafico->driver->beginScene(true, true, video::SColor(255,255,255,255));

        //Fondo
        grafico->draw2DImage
        (
            imagen,
            irr::core::dimension2d<irr::f32> (1024,600),
            irr::core::rect<irr::f32>(0,0,1024,600),
            irr::core::position2d<irr::f32>(0,0),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        //Opcion
        int o1=1,o2=1,o3=1,o4=1;
        if(opcion==1)o1=0;
        if(opcion==2)o2=0;
        if(opcion==3)o3=0;
        if(opcion==4)o4=0;
        grafico->font->draw(L"Menu",
                    core::rect<s32>(130,10,300,50),
                    video::SColor(255,255,255,255));
        grafico->font->draw(L"Personaje1",
                    core::rect<s32>(130,100,300,150),
                    video::SColor(255,255*o1,255*o1,255));
        grafico->font->draw(L"Personaje2",
                    core::rect<s32>(130,150,300,200),
                    video::SColor(255,255*o2,255*o2,255));
        grafico->font->draw(L"Stage",
                    core::rect<s32>(130,200,300,250),
                    video::SColor(255,255*o3,255*o3,255));
        grafico->font->draw(L"Iniciar",
                    core::rect<s32>(130,250,300,300),
                    video::SColor(255,255*o4,255*o4,255));

        //Stage
        video::ITexture* imagen_stage_menu=grafico->driver->getTexture("resources/Stages/Stage01.jpg");
        if(opcion_stage%2==0)
            imagen_stage_menu=grafico->driver->getTexture("resources/Stages/Stage02.jpg");
        grafico->draw2DImage
        (
            imagen_stage_menu,
            irr::core::dimension2d<irr::f32> (1024,600),
            irr::core::rect<irr::f32>(0,0,1024,600),
            irr::core::position2d<irr::f32>(0,0),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0.25,0.25),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);

        grafico->driver->endScene();
    }
    return grafico->device->run() && grafico->driver;
}

