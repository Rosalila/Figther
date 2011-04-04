#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include "include/MyEventReceiver.h"
#include "include/Fighter.h"

void wizardMovimiento(Personaje* personaje,std::string movimiento,int cantidad_frames,int duracion_frame,irr::io::path carpieta_sprites,Grafico* grafico)
{
    personaje->agregarMovimiento(movimiento);
    int num1=0;
    for(int i=0;i<cantidad_frames;i++)
    {
        personaje->agregarFrame(movimiento,duracion_frame);
        personaje->agregarModificador(movimiento,i,grafico->driver->getTexture(carpieta_sprites),personaje,"imagen_personaje");
    vector <HitBox> hb_roja;
    vector <HitBox> hb_azul;
    vector <HitBox> hb_roja2;
    vector <HitBox> hb_azul2;
    hb_azul.push_back(HitBox(50,80,60,120));
    hb_roja.push_back(HitBox(60,80,80,120));
    hb_roja2.push_back(HitBox(60,80,80,120));
        personaje->agregarModificador(movimiento,i,hb_azul,personaje,"azules");
        personaje->agregarModificador(movimiento,i,hb_roja,personaje,"rojas");

        num1++;
        if(num1==9)
        {
            num1=0;
            carpieta_sprites[carpieta_sprites.size()-6]++;
            carpieta_sprites[carpieta_sprites.size()-5]-=9;
        }else
        {
            carpieta_sprites[carpieta_sprites.size()-5]++;
        }
    }
}

class Ryu : Personaje
{
public:
Ryu(Barra hp,int px,int py,int a,char orientacion,Grafico* grafico)
{
    setImagen("imagen_personaje",grafico->driver->getTexture("resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png"));
    this->grafico=grafico;
    saltando=false;
    saltando_adelante=false;
    saltando_atras=false;
    frame_actual_saltando=0;
    tiempo_transcurrido=0;
    this->orientacion=orientacion;
    movimiento_actual="5";

    enteros["posicion_x"]=px;
    enteros["posicion_y"]=py;

    barras["hp"]=hp;

    vector<HitBox> hb_vacia;
    hitboxes["azules"]=hb_vacia;
    hitboxes["rojas"]=hb_vacia;




    //Creacion de movimientos
    wizardMovimiento(this,"1",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
    wizardMovimiento(this,"2",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
    wizardMovimiento(this,"3",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
    wizardMovimiento(this,"4",11,1,"resources/Personajes/Ryu/Sprites/mover/caminar/atras/01.png",grafico);
    wizardMovimiento(this,"5",10,1,"resources/Personajes/Ryu/Sprites/respirar/01.png",grafico);
    wizardMovimiento(this,"6",12,1,"resources/Personajes/Ryu/Sprites/mover/caminar/adelante/01.png",grafico);
    wizardMovimiento(this,"7",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/atras/01.png",grafico);
    wizardMovimiento(this,"8",12,1,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png",grafico);
    wizardMovimiento(this,"9",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/adelante/01.png",grafico);

    wizardMovimiento(this,"a",5,1,"resources/Personajes/Ryu/Sprites/atacar/ataque1/01.png",grafico);
    wizardMovimiento(this,"b",14,1,"resources/Personajes/Ryu/Sprites/atacar/agarre/01.png",grafico);
    wizardMovimiento(this,"c",7,1,"resources/Personajes/Ryu/Sprites/atacar/overhead/01.png",grafico);

    wizardMovimiento(this,"e",7,1,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/01.png",grafico);
    wizardMovimiento(this,"d",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);

    for(int i=0;i<11;i++)
        agregarModificador("4",i,-10,this,"posicion_x",true);
    for(int i=0;i<12;i++)
        agregarModificador("6",i,10,this,"posicion_x",true);

    //cancels
    agregarCancel("a","5");
    agregarCancel("b","5");
    agregarCancel("c","5");
    agregarCancel("1","5");
    agregarCancel("2","5");
    agregarCancel("3","5");
    agregarCancel("4","5");
    agregarCancel("6","5");
    agregarCancel("7","5");
    agregarCancel("8","5");
    agregarCancel("9","5");

    agregarCancel("a","4");
    agregarCancel("b","4");
    agregarCancel("c","4");
    agregarCancel("1","4");
    agregarCancel("2","4");
    agregarCancel("3","4");
    agregarCancel("5","4");
    agregarCancel("6","4");
    agregarCancel("7","4");
    agregarCancel("8","4");
    agregarCancel("9","4");
    //
    agregarCancel("a","6");
    agregarCancel("b","6");
    agregarCancel("c","6");
    agregarCancel("1","6");
    agregarCancel("2","6");
    agregarCancel("3","6");
    agregarCancel("4","6");
    agregarCancel("5","6");
    agregarCancel("7","6");
    agregarCancel("8","6");
    agregarCancel("9","6");

    //saltar
    agregarCancel("d","7");
    agregarCancel("d","8");
    agregarCancel("d","9");
    //agachar
    agregarCancel("e","1");
    agregarCancel("e","2");
    agregarCancel("e","3");
    //otros
    agregarCancel("a","c");
}
};

int main()
{
    MyEventReceiver *receiver=new MyEventReceiver;
    Grafico *grafico=new Grafico(receiver);
    ISoundEngine *engine_sonido = createIrrKlangDevice();
    Stage *stage=new Stage(grafico->driver->getTexture("resources/Stages/Stage02.png"),grafico->driver->getTexture("resources/Stages/Barra_Vida.png"),grafico);
    Personaje *pa=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(0,0,200,50),NULL),50,300,2,'d',grafico);
    Personaje *pb=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(250,0,450,50),NULL),800,300,3,'i',grafico);
    Fighter fighter(stage,pa,pb,receiver,grafico,engine_sonido);
    return 0;
}
