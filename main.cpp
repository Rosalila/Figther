#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include "include/irrKlang/irrKlang.h"
using namespace irrklang;


#include "include/Input.h"
#include "include/Fighter.h"

void wizardMovimiento(Personaje* personaje,std::string movimiento,int cantidad_frames,int duracion_frame,irr::io::path carpeta_sprites,Grafico* grafico)
{
    personaje->agregarMovimiento(movimiento);
    int num1=0;
    for(int i=0;i<cantidad_frames;i++)
    {
        personaje->agregarFrame(movimiento,duracion_frame);

        if(movimiento=="a")
            personaje->agregarModificador(movimiento,i,grafico->driver->getTexture("resources/Personajes/Ryu/Sprites/recibir/arriba/01.png"),personaje,"imagen_personaje",true);
        personaje->agregarModificador(movimiento,i,grafico->driver->getTexture(carpeta_sprites),personaje,"imagen_personaje",false);
        //personaje->agregarModificador(movimiento,i,grafico->driver->getTexture("resources/Personajes/Ryu/Sprites/recibir/arriba/01.png"),personaje,"imagen_personaje",true);
        vector <HitBox> hb_roja;
        vector <HitBox> hb_azul;
        vector <HitBox> hb_roja2;
        vector <HitBox> hb_azul2;
        hb_azul.push_back(HitBox(50,80,60,120));
        hb_roja.push_back(HitBox(60,80,80,120));
        hb_roja2.push_back(HitBox(60,80,80,120));
        personaje->agregarModificador(movimiento,i,hb_azul,personaje,"azules",false);
        personaje->agregarModificador(movimiento,i,hb_roja,personaje,"rojas",false);

        num1++;
        if(num1==9)
        {
            num1=0;
            carpeta_sprites[carpeta_sprites.size()-6]++;
            carpeta_sprites[carpeta_sprites.size()-5]-=9;
        }else
        {
            carpeta_sprites[carpeta_sprites.size()-5]++;
        }
    }
}

void wizardAtaque(Personaje* personaje,std::string movimiento,int cantidad_frames,int duracion_frame,irr::io::path carpeta_sprites,Grafico* grafico)
{
    personaje->agregarMovimiento(movimiento);
    int num1=0;
    for(int i=0;i<cantidad_frames;i++)
    {
        personaje->agregarFrame(movimiento,duracion_frame);
        personaje->agregarModificador(movimiento,i,grafico->driver->getTexture(carpeta_sprites),personaje,"imagen_personaje",true);
    vector <HitBox> hb_roja;
    vector <HitBox> hb_azul;
    vector <HitBox> hb_roja2;
    vector <HitBox> hb_azul2;
    hb_azul.push_back(HitBox(50,80,60,120));
    hb_roja.push_back(HitBox(60,80,80,120));
    hb_roja2.push_back(HitBox(60,80,80,120));
        personaje->agregarModificador(movimiento,i,hb_azul,personaje,"azules",false);
        personaje->agregarModificador(movimiento,i,hb_roja,personaje,"rojas",false);

        num1++;
        if(num1==9)
        {
            num1=0;
            carpeta_sprites[carpeta_sprites.size()-6]++;
            carpeta_sprites[carpeta_sprites.size()-5]-=9;
        }else
        {
            carpeta_sprites[carpeta_sprites.size()-5]++;
        }
    }
}

class Ryu : Personaje
{
public:
Ryu(Barra hp,int px,int py,int a,char orientacion,Grafico* grafico,Personaje *personaje_contrario)
{
        setImagen("imagen_personaje",grafico->driver->getTexture("resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png"));
        this->grafico=grafico;
        estado_posicion="";
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
        agregarMovimiento("recibir");
        wizardMovimiento(this,"1",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
        wizardMovimiento(this,"2",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
        wizardMovimiento(this,"3",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
        wizardMovimiento(this,"4",11,1,"resources/Personajes/Ryu/Sprites/mover/caminar/atras/01.png",grafico);
        wizardMovimiento(this,"5",10,1,"resources/Personajes/Ryu/Sprites/respirar/01.png",grafico);
        wizardMovimiento(this,"6",12,1,"resources/Personajes/Ryu/Sprites/mover/caminar/adelante/01.png",grafico);
        agregarMovimiento("7");
        agregarMovimiento("8");
        agregarMovimiento("9");
        wizardMovimiento(this,"a",5,1,"resources/Personajes/Ryu/Sprites/atacar/ataque1/01.png",grafico);
        wizardMovimiento(this,"b",14,1,"resources/Personajes/Ryu/Sprites/atacar/agarre/01.png",grafico);
        wizardMovimiento(this,"c",7,1,"resources/Personajes/Ryu/Sprites/atacar/overhead/01.png",grafico);
        wizardMovimiento(this,"d",5,1,"resources/Personajes/Ryu/Sprites/atacar/ataque1/01.png",grafico);
        wizardMovimiento(this,"e",7,1,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/01.png",grafico);
        agregarMovimiento("f");

        wizardMovimiento(this,"agachado1",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
        wizardMovimiento(this,"agachado2",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
        wizardMovimiento(this,"agachado3",9,1,"resources/Personajes/Ryu/Sprites/mover/agachar/01.png",grafico);
        agregarMovimiento("agachado4");
        wizardMovimiento(this,"agachado5",10,1,"resources/Personajes/Ryu/Sprites/respirar/01.png",grafico);
        agregarMovimiento("agachado6");
        agregarMovimiento("agachado7");
        agregarMovimiento("agachado8");
        agregarMovimiento("agachado9");
        wizardMovimiento(this,"agachadoa",7,1,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/01.png",grafico);
        wizardMovimiento(this,"agachadob",7,1,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/01.png",grafico);
        wizardMovimiento(this,"agachadoc",7,1,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/01.png",grafico);
        wizardMovimiento(this,"agachadod",7,1,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/01.png",grafico);
        agregarMovimiento("agachadoe");
        agregarMovimiento("agachadof");

        agregarMovimiento("saltando_atras1");
        agregarMovimiento("saltando_atras2");
        agregarMovimiento("saltando_atras3");
        agregarMovimiento("saltando_atras4");
        wizardMovimiento(this,"saltando_atras5",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/atras/01.png",grafico);
        agregarMovimiento("saltando_atras6");
        wizardMovimiento(this,"saltando_atras7",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/atras/01.png",grafico);
        agregarMovimiento("saltando_atras8");
        agregarMovimiento("saltando_atras9");
        wizardMovimiento(this,"saltando_atrasa",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltando_atrasb",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltando_atrasc",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltando_atrasd",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        agregarMovimiento("saltando_atrase");
        agregarMovimiento("saltando_atrasf");

        agregarMovimiento("saltando1");
        agregarMovimiento("saltando2");
        agregarMovimiento("saltando3");
        agregarMovimiento("saltando4");
        wizardMovimiento(this,"saltando5",12,1,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png",grafico);
        agregarMovimiento("saltando6");
        agregarMovimiento("saltando7");
        wizardMovimiento(this,"saltando8",12,1,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png",grafico);
        agregarMovimiento("saltando9");
        wizardMovimiento(this,"saltandoa",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltandob",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltandoc",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltandod",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        agregarMovimiento("saltandoe");
        agregarMovimiento("saltandof");

        agregarMovimiento("saltando_adelante1");
        agregarMovimiento("saltando_adelante2");
        agregarMovimiento("saltando_adelante3");
        agregarMovimiento("saltando_adelante4");
        wizardMovimiento(this,"saltando_adelante5",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/adelante/01.png",grafico);
        agregarMovimiento("saltando_adelante6");
        agregarMovimiento("saltando_adelante7");
        agregarMovimiento("saltando_adelante8");
        wizardMovimiento(this,"saltando_adelante9",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/adelante/01.png",grafico);
        wizardMovimiento(this,"saltando_adelantea",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltando_adelanteb",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltando_adelantec",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        wizardMovimiento(this,"saltando_adelanted",6,1,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/01.png",grafico);
        agregarMovimiento("saltando_adelantee");
        agregarMovimiento("saltando_adelantef");


        for(int i=0;i<11;i++)
            agregarModificador("4",i,-10,this,"posicion_x",true,false);
        for(int i=0;i<12;i++)
            agregarModificador("6",i,10,this,"posicion_x",true,false);

        //cancels
        agregarCancel("a","5");
        agregarCancel("b","5");
        agregarCancel("c","5");
        agregarCancel("d","5");
        agregarCancel("agachado1","5");
        agregarCancel("agachado2","5");
        agregarCancel("agachado3","5");
        agregarCancel("4","5");
        agregarCancel("6","5");
        agregarCancel("saltando_atras7","5");
        agregarCancel("saltando8","5");
        agregarCancel("saltando_adelante9","5");

        agregarCancel("a","4");
        agregarCancel("b","4");
        agregarCancel("c","4");
        agregarCancel("d","4");
        agregarCancel("agachado1","4");
        agregarCancel("agachado2","4");
        agregarCancel("agachado3","4");
        agregarCancel("5","4");
        agregarCancel("6","4");
        agregarCancel("saltando_atras7","4");
        agregarCancel("saltando8","4");
        agregarCancel("saltando_adelante9","4");
        //
        agregarCancel("a","6");
        agregarCancel("b","6");
        agregarCancel("c","6");
        agregarCancel("d","6");
        agregarCancel("agachado1","6");
        agregarCancel("agachado2","6");
        agregarCancel("agachado3","6");
        agregarCancel("4","6");
        agregarCancel("5","6");
        agregarCancel("saltando_atras7","6");
        agregarCancel("saltando8","6");
        agregarCancel("saltando_adelante9","6");

        //saltar
        agregarCancel("saltando_atrasa","saltando_atras7");
        agregarCancel("saltandoa","saltando8");
        agregarCancel("saltando_adelantea","saltando_adelante9");

        agregarCancel("saltando_atrasb","saltando_atras7");
        agregarCancel("saltandob","saltando8");
        agregarCancel("saltando_adelanteb","saltando_adelante9");

        agregarCancel("saltando_atrasc","saltando_atras7");
        agregarCancel("saltandoc","saltando8");
        agregarCancel("saltando_adelantec","saltando_adelante9");

        agregarCancel("saltando_atrasd","saltando_atras7");
        agregarCancel("saltandod","saltando8");
        agregarCancel("saltando_adelanted","saltando_adelante9");
        //agachar
        agregarCancel("agachadoa","agachado1");
        agregarCancel("agachadob","agachado1");
        agregarCancel("agachadoc","agachado1");
        agregarCancel("agachadod","agachado1");
        agregarCancel("agachadoa","agachado2");
        agregarCancel("agachadob","agachado2");
        agregarCancel("agachadoc","agachado2");
        agregarCancel("agachadod","agachado2");
        agregarCancel("agachadoa","agachado3");
        agregarCancel("agachadob","agachado3");
        agregarCancel("agachadoc","agachado3");
        agregarCancel("agachadod","agachado13");
    }
};

int main()
{
    Input *receiver=new Input;
    Grafico *grafico=new Grafico(receiver);
    ISoundEngine *sonido = createIrrKlangDevice();

    Stage *stage=new Stage(grafico->driver->getTexture("resources/Stages/Stage02.png"),grafico->driver->getTexture("resources/Stages/Barra_Vida.png"),grafico);
    Personaje *pb=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(250,0,450,50),NULL),800,300,3,'i',grafico,NULL);
    Personaje *pa=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(0,0,200,50),NULL),50,300,2,'d',grafico,pb);



    Fighter fighter(stage,pa,pb,receiver,grafico,sonido);
    return 0;
}
