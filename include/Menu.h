#include "../include/Stage.h"
#include "../include/Grafico.h"
#include "../include/irrKlang/irrKlang.h"
using namespace irrklang;
#include "../include/Personaje.h"

class Menu
{
    Stage* stage;
    Personaje *pa;
    Personaje *pb;
    //Engines
    ISoundEngine* engine_sonido;
    Grafico* grafico;
    MyEventReceiver* receiver;

    Menu(Stage* stage,Personaje *pa,Personaje *pb,ISoundEngine* engine_sonido,Grafico* grafico,MyEventReceiver* receiver);
    void loopMenu();
    bool dibujarImagen(video::ITexture* imagen);
    bool dibujarMenu(video::ITexture* imagen,int opcion,int opcion_stage);
};
