#include "../include/Fighter.h"
Fighter::Fighter(Stage* stage,Personaje*pa,Personaje*pb,Input *receiver,Grafico *grafico,Sonido *sonido)
{
    //Engines
    this->receiver=receiver;
    this->grafico=grafico;
    this->sonido=sonido;

    //Sets
    this->stage=stage;
    this->pa=pa;
    this->pb=pb;
    pa->personaje_contrario=pb;
    pb->personaje_contrario=pa;

    //sonido->agregarSonido("Fight!","resources/Stages/Sonidos/Fight1.wav");
    sonido->agregarSonido("Fondo","resources/Stages/Sonidos/Now.ogg");
    sonido->agregarSonido("Fondo2","resources/Stages/Sonidos/Something like this.mp3");

    //Menu
    //loopMenu();

    //Juego
    loopJuego();

    //Drops
    sonido->drop(); // delete engine
}

bool Fighter::getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    int x1r=hb_roja.p1x+atacante_x;
    int y1r=hb_roja.p1y+atacante_y;
    int x2r=hb_roja.p2x+atacante_x;
    int y2r=hb_roja.p2y+atacante_y;

    int x1a=hb_azul.p1x+atacado_x;
    int y1a=hb_azul.p1y+atacado_y;
    int x2a=hb_azul.p2x+atacado_x;
    int y2a=hb_azul.p2y+atacado_y;

    return (
            (x1r<=x1a && x1a<=x2r && x2r<=x2a) ||
            (x1r<=x1a && x1a<=x2a && x2a<=x2r) ||
            (x1a<=x1r && x1r<=x2r && x2r<=x2a) ||
            (x1a<=x1r && x1r<=x2a && x2a<=x2r)
            )&&(
            (y1r<=y1a && y1a<=y2r && y2r<=y2a) ||
            (y1r<=y1a && y1a<=y2a && y2a<=y2r) ||
            (y1a<=y1r && y1r<=y2r && y2r<=y2a) ||
            (y1a<=y1r && y1r<=y2a && y2a<=y2r)
            );
}


bool Fighter::getColisionHitBoxes(Personaje *atacante,Personaje* atacado)
{
    int ax=atacado->getEntero("posicion_x");
    int ay=atacado->getEntero("posicion_y");
    int rx=atacante->getEntero("posicion_x");
    int ry=atacante->getEntero("posicion_y");

    int hb_azul_size=atacado->getHitBoxes("azules").size();
    int hb_roja_size=atacante->getHitBoxes("rojas").size();
    for(int a=0;a<hb_azul_size;a++)
        for(int r=0;r<hb_roja_size;r++)
            if(getColisionHitBoxes(atacado->getHitBoxes("azules")[a],atacante->getHitBoxes("rojas")[r],ax,ay,rx,ry))
                return true;
    return false;
}


void Fighter::logica(Personaje* personaje,std::string input,int tiempo)
{
    input=personaje->getString("estado_posicion")+input;
    //avanzar tiempo ++
    personaje->setEntero("tiempo_transcurrido",personaje->getEntero("tiempo_transcurrido")+1);
    //si se termino
    personaje->verificarFinDeMovimiento();
    //si hay cancel, cambiar input
    personaje->ejectuarCancel(input);
    //modificadores
    personaje->aplicarModificadores();
}

void Fighter::loopJuego()
{
    //irrklang::ISoundSource* shootSound = engine_sonido->addSoundSourceFromFile("resources/Stages/Sonidos/Fight1.wav");
    //engine_sonido->play2D(shootSound);
    //sonido->reproducir("resources/Stages/Sonidos/Fight1.wav");
    //sonido->reproducirSonido("Fight!");
    sonido->reproducirSonido("Fondo");
	std::string input="5";
	std::string input2="5";
    f32 moveHorizontal = 0.f;
    f32 moveVertical = 0.f;
    int tiempo;
    bool tecla_arriba=false;
    bool tecla_arriba2=false;
	for (;;)
	{
        //render
        render(pa,pb,stage);
        //logica
        logica(pa,input2,tiempo);
        logica(pb,input,tiempo);
        tiempo = grafico->device->getTimer()->getTime();
        const SEvent::SJoystickEvent & joystickData = receiver->GetJoystickState();
        moveHorizontal =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
        moveVertical =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
        input="5";
        input2="5";

        //Player 1 - kb
        if(receiver->IsKeyDown(irr::KEY_KEY_S) && receiver->IsKeyDown(irr::KEY_KEY_A))
            input="1";
        else if(receiver->IsKeyDown(irr::KEY_KEY_S) && receiver->IsKeyDown(irr::KEY_KEY_D))
            input="3";
        else if(receiver->IsKeyDown(irr::KEY_KEY_W) && receiver->IsKeyDown(irr::KEY_KEY_A))
            input="7";
        else if(receiver->IsKeyDown(irr::KEY_KEY_W) && receiver->IsKeyDown(irr::KEY_KEY_D))
            input="9";
        else if(receiver->IsKeyDown(irr::KEY_KEY_S))
            input="2";
        else if(receiver->IsKeyDown(irr::KEY_KEY_A))
            input="4";
        else if(receiver->IsKeyDown(irr::KEY_KEY_D))
            input="6";
        else if(receiver->IsKeyDown(irr::KEY_KEY_W))
            input="8";
        if(tecla_arriba)
        {
            tecla_arriba=false;
            if(receiver->IsKeyDown(irr::KEY_KEY_U))
                input="a";
            else if(receiver->IsKeyDown(irr::KEY_KEY_I))
                input="b";
            else if(receiver->IsKeyDown(irr::KEY_KEY_O))
                input="c";
            else if(receiver->IsKeyDown(irr::KEY_KEY_J))
                input="d";
            else if(receiver->IsKeyDown(irr::KEY_KEY_K))
                input="e";
        }
        if(!receiver->IsKeyDown(irr::KEY_KEY_U) && !receiver->IsKeyDown(irr::KEY_KEY_I) && !receiver->IsKeyDown(irr::KEY_KEY_O) && !receiver->IsKeyDown(irr::KEY_KEY_J) && !receiver->IsKeyDown(irr::KEY_KEY_K) && !receiver->IsKeyDown(irr::KEY_KEY_L))
            tecla_arriba=true;


        //Player 2 - Joy
        if(moveHorizontal<0 && moveVertical<0)
            input2="1";
        else if(moveHorizontal>0 && moveVertical<0)
            input2="3";
        else if(moveHorizontal<0 && moveVertical>0)
            input2="7";
        else if(moveHorizontal>0 && moveVertical>0)
            input2="9";
        else if(moveVertical<0)
            input2="2";
        else if(moveHorizontal<0)
            input2="4";
        else if(moveHorizontal>0)
            input2="6";
        else if(moveVertical>0)
            input2="8";
        if(tecla_arriba2)
        {
            tecla_arriba2=false;
            if(joystickData.IsButtonPressed(0))
                input2="a";
            else if(joystickData.IsButtonPressed(1))
                input2="b";
            else if(joystickData.IsButtonPressed(2))
                input2="c";
            else if(joystickData.IsButtonPressed(3))
                input2="d";
            else if(joystickData.IsButtonPressed(4))
                input2="e";
        }
        if(!joystickData.IsButtonPressed(0) && !joystickData.IsButtonPressed(1) && !joystickData.IsButtonPressed(2) && !joystickData.IsButtonPressed(3) && !joystickData.IsButtonPressed(4) && !joystickData.IsButtonPressed(5))
            tecla_arriba2=true;

        if(receiver->IsKeyDown(irr::KEY_KEY_Q))
            exit(0);

	}
}


bool Fighter::render(Personaje* pa,Personaje* pb,Stage* stage)
{
    if (grafico->device->isWindowActive())
    {
        grafico->driver->beginScene(true, true, video::SColor(255,255,255,255));

        //Stage
        stage->dibujar();

        //Personaje
        pa->dibujar();
        pb->dibujar();

        //HP
        pa->dibujarBarra("hp");
        pb->dibujarBarra("hp");

        //Hit Boxes
        pa->dibujarHitBoxes("azules",video::SColor(100,0,0,255),pa->getString("orientacion")=="i");
        pb->dibujarHitBoxes("azules",video::SColor(100,0,0,255),pb->getString("orientacion")=="i");
        pa->dibujarHitBoxes("rojas",video::SColor(100,255,0,0),pa->getString("orientacion")=="i");
        pb->dibujarHitBoxes("rojas",video::SColor(100,255,0,0),pb->getString("orientacion")=="i");

        //FPS
        int lastFPS=-1;
        int fps = grafico->driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw str = L"Rosalila Fighter  [";
            str += grafico->driver->getName();
            str += "] FPS:";
            str += fps;
            grafico->device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }

        grafico->driver->endScene();
    }
    return grafico->device->run() && grafico->driver;
}


