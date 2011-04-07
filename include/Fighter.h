#include "../include/Menu.h"
class Fighter
{
public:
    //Logica
    Stage* stage;
    Personaje *pa;
    Personaje *pb;
    //Engines
    ISoundEngine* engine_sonido;
    Grafico* grafico;
    Input* receiver;
    Fighter(Stage* stage,Personaje*pa,Personaje*pb,Input *receiver,Grafico *grafico,ISoundEngine *engine_sonido);
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,Personaje* atacado);
    void logica(Personaje*personaje,std::string input,int tiempo);
    void loopJuego();
    bool render(Personaje* pa,Personaje* pb,Stage* stage);
};
