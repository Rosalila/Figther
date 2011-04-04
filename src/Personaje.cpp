#include "../include/Personaje.h"

Personaje::Personaje(Barra hp,int px,int py,int a,char orientacion,Grafico* grafico)
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

}
Personaje::Personaje()
{

}
//DIBUJAR
void Personaje::dibujar()
{
    int aliniacion_ax=-500;
    int aliniacion_ay=-300;
    grafico->draw2DImage
    (
        getImagen("imagen_personaje"),
        irr::core::dimension2d<irr::f32> (1000,600),
        irr::core::rect<irr::f32>(0,0,1000,600),
        irr::core::position2d<irr::f32>(getEntero("posicion_x")+aliniacion_ax,getEntero("posicion_y")+aliniacion_ay),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (1,1),
        true,
        irr::video::SColor(255,255,255,255),
        orientacion=='i',
        false);
}
void Personaje::dibujarHitBoxes(std::string variable,video::SColor color)
{
    vector <HitBox> hitbox=getHitBoxes(variable);
    int hb_size=hitbox.size();
    for(int i=0;i<hb_size;i++)
        grafico->driver->draw2DRectangle(color,core::rect<s32>(getEntero("posicion_x")+hitbox[i].p1x,getEntero("posicion_y")+hitbox[i].p1y,getEntero("posicion_x")+hitbox[i].p2x,getEntero("posicion_y")+hitbox[i].p2y));
}
void Personaje::dibujarBarra(std::string variable)
{
    Barra barra=getBarra(variable);
    position2d<s32>prueba= barra.posicion.UpperLeftCorner;
    position2d<s32>prueba2= barra.posicion.LowerRightCorner;
    int l=prueba2.X-prueba.X;
    int bx2=(barra.valor_maximo/l)*barra.valor_actual;
    grafico->driver->draw2DRectangle(barra.color,core::rect<s32>(prueba.X,prueba.Y,prueba.X+bx2,prueba2.Y));
}
//GETS shortcuts
Movimiento* Personaje::getMovimientoActual()
{
    return movimientos[movimiento_actual];
}
Frame Personaje::getFrameActual()
{
    return getMovimientoActual()->getFrameActual();
}

//GETS variables
int Personaje::getEntero(std::string variable)
{
    return enteros[variable];
}
Barra Personaje::getBarra(std::string variable)
{
    return barras[variable];
}
vector<HitBox> Personaje::getHitBoxes(std::string variable)
{
    return hitboxes[variable];
}
video::ITexture* Personaje::getImagen(std::string variable)
{
    return imagenes[variable];
}
//SETS variables
void Personaje::setImagen(std::string variable,video::ITexture* valor)
{
    imagenes[variable]=valor;
}
void Personaje::setEntero(std::string variable,int valor)
{
    enteros[variable]=valor;
}
void Personaje::setBarra(std::string variable,Barra valor)
{
    barras[variable]=valor;
}
void Personaje::setHitBoxes(std::string variable,vector<HitBox> valor)
{
    hitboxes[variable]=valor;
}

//Agregares
void Personaje::agregarCancel(std::string cancelador,std::string cancelado)
{
    ((Movimiento*)movimientos[cancelador])->cancels.push_back(cancelado);
}
void Personaje::agregarMovimiento(std::string movimiento)
{
    movimientos[movimiento]=new Movimiento();
}
void Personaje::agregarFrame(std::string movimiento, int duracion)
{
    ((Movimiento*)movimientos[movimiento])->agregarFrame(duracion);
}
void Personaje::agregarModificador(std::string movimiento,int frame,video::ITexture* modificador,Personaje* personaje,std::string variable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable);
}
void Personaje::agregarModificador(std::string movimiento,int frame,int modificador,Personaje* personaje,std::string variable,bool relativo)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable,relativo);
}
void Personaje::agregarModificador(std::string movimiento,int frame,Barra modificador,Personaje* personaje,std::string variable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable);
}
void Personaje::agregarModificador(std::string movimiento,int frame,vector <HitBox> modificador,Personaje* personaje,std::string variable)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable);
}

//Logica
bool Personaje::ejectuarCancel(std::string input)
{
    int cancel_size=((Movimiento*)movimientos[input])->cancels.size();
    for(int i=0;i<cancel_size;i++)
        if(((Movimiento*)movimientos[input])->cancels[i]==movimiento_actual)
        {
            getMovimientoActual()->frame_actual=0;
            movimiento_actual=input;
            if(input=="7")
                saltando_atras=true;
            if(input=="8")
                saltando=true;
            if(input=="9")
                saltando_adelante=true;
            return true;
        }
    return false;
}
bool Personaje::verificarFinDeMovimiento()
{
    int frames_size=getMovimientoActual()->frames.size();
    if(frames_size==getMovimientoActual()->frame_actual)
    {
        getMovimientoActual()->frame_actual=0;
        movimiento_actual="5";
        return true;
    }
    return false;
}
bool Personaje::aplicarModificadores()
{
    if(tiempo_transcurrido>getFrameActual().duracion)
    {
        Frame frame=getFrameActual();
        int frame_modificadores_size=frame.modificadores.size();
        for(int i=0;i<frame_modificadores_size;i++)
        {
            Modificador modificador=frame.modificadores[i];
            if(modificador.tipo=="imagen")
            {
                ModificadorImagen* mod_imagen=(ModificadorImagen*)&modificador;
                mod_imagen->personaje->setImagen(mod_imagen->variable,mod_imagen->modificador_imagen);
            }
            if(modificador.tipo=="entero")
            {
                ModificadorEntero* mod_entero=(ModificadorEntero*)&modificador;
                if(mod_entero->relativo)
                    mod_entero->personaje->setEntero(mod_entero->variable,mod_entero->modificador_entero+getEntero(mod_entero->variable));
                else
                    mod_entero->personaje->setEntero(mod_entero->variable,mod_entero->modificador_entero);
            }
            if(modificador.tipo=="hitboxes")
            {
                ModificadorHitboxes* mod_hitboxes=(ModificadorHitboxes*)&modificador;
                mod_hitboxes->personaje->setHitBoxes(mod_hitboxes->variable,mod_hitboxes->modificador_hitbox);
            }
        }
        getMovimientoActual()->frame_actual++;
        tiempo_transcurrido=0;
        return true;
    }
    if(saltando)
    {
        if(frame_actual_saltando==12)
        {
            frame_actual_saltando=0;
            saltando=false;
        }
        int desplazamiento=-1;
        if(frame_actual_saltando>=6)
            desplazamiento=1;
        setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        frame_actual_saltando++;
    }
    if(saltando_adelante)
    {
        if(frame_actual_saltando==13)
        {
            frame_actual_saltando=0;
            saltando_adelante=false;
        }
        int desplazamiento=-1;
        if(frame_actual_saltando>=6)
            desplazamiento=1;
        if(frame_actual_saltando!=6)
            setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        setEntero("posicion_x",20+getEntero("posicion_x"));
        frame_actual_saltando++;
    }
    if(saltando_atras)
    {
        if(frame_actual_saltando==13)
        {
            frame_actual_saltando=0;
            saltando_atras=false;
        }
        int desplazamiento=-1;
        if(frame_actual_saltando>=6)
            desplazamiento=1;
        if(frame_actual_saltando!=6)
            setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        setEntero("posicion_x",-20+getEntero("posicion_x"));
        frame_actual_saltando++;
    }
    return false;
}
