#include "../include/Personaje.h"

Personaje::Personaje(Barra hp,int px,int py,int a,char orientacion,Grafico* grafico)
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
void Personaje::agregarModificador(std::string movimiento,int frame,video::ITexture* modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable,relativo,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable,aplicar_a_contrario);
}
void Personaje::agregarModificador(std::string movimiento,int frame,vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    ((Movimiento*)movimientos[movimiento])->frames[frame].agregarModificador(modificador,personaje,variable,aplicar_a_contrario);
}

//Logica
bool Personaje::getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
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

bool Personaje::getColisionHitBoxes(Personaje *atacante,Personaje* atacado)
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
bool Personaje::ejectuarCancel(std::string input)
{
            if(input=="7")
                input="saltando_atras7";
            if(input=="8")
                input="saltando8";
            if(input=="9")
                input="saltando_adelante9";
            if(input=="2")
                input="agachado2";
    int cancel_size=((Movimiento*)movimientos[input])->cancels.size();
    for(int i=0;i<cancel_size;i++)
        if(((Movimiento*)movimientos[input])->cancels[i]==movimiento_actual)
        {
            if(frame_actual_saltando==0 || (estado_posicion=="agachado" && input=="agachado5") || (estado_posicion=="agachado" && input=="5"))
                estado_posicion="";
            getMovimientoActual()->frame_actual=0;
            movimiento_actual=input;
            if(input=="saltando_atras7")
                estado_posicion="saltando_atras";
            if(input=="saltando8")
                estado_posicion="saltando";
            if(input=="saltando_adelante9")
                estado_posicion="saltando_adelante";
            if(input=="agachado2")
                estado_posicion="agachado";
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
                if(mod_imagen->aplicar_a_contrario)
                {
                    if(getColisionHitBoxes(this,personaje_contrario))
                    {
                        mod_imagen->personaje->personaje_contrario->setImagen(mod_imagen->variable,mod_imagen->modificador_imagen);
                    }
                }
                else
                    mod_imagen->personaje->setImagen(mod_imagen->variable,mod_imagen->modificador_imagen);
            }
            if(modificador.tipo=="entero")
            {
                ModificadorEntero* mod_entero=(ModificadorEntero*)&modificador;
                if(mod_entero->relativo)
                    if(mod_entero->aplicar_a_contrario)
                        mod_entero->personaje->personaje_contrario->setEntero(mod_entero->variable,mod_entero->modificador_entero+getEntero(mod_entero->variable));
                    else
                        mod_entero->personaje->setEntero(mod_entero->variable,mod_entero->modificador_entero+getEntero(mod_entero->variable));
                else
                    if(mod_entero->aplicar_a_contrario)
                        mod_entero->personaje->personaje_contrario->setEntero(mod_entero->variable,mod_entero->modificador_entero);
                    else
                        mod_entero->personaje->setEntero(mod_entero->variable,mod_entero->modificador_entero);
            }
            if(modificador.tipo=="hitboxes")
            {
                ModificadorHitboxes* mod_hitboxes=(ModificadorHitboxes*)&modificador;
                if(mod_hitboxes->aplicar_a_contrario)
                    mod_hitboxes->personaje->personaje_contrario->setHitBoxes(mod_hitboxes->variable,mod_hitboxes->modificador_hitbox);
                else
                    mod_hitboxes->personaje->setHitBoxes(mod_hitboxes->variable,mod_hitboxes->modificador_hitbox);
            }
        }
        getMovimientoActual()->frame_actual++;
        tiempo_transcurrido=0;
        return true;
    }
    if(estado_posicion=="saltando")
    {
        if(frame_actual_saltando==12)
        {
            frame_actual_saltando=0;
            estado_posicion="";
        }
        int desplazamiento=-1;
        if(frame_actual_saltando>=6)
            desplazamiento=1;
        setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        frame_actual_saltando++;
    }
    if(estado_posicion=="saltando_adelante")
    {
        if(frame_actual_saltando==13)
        {
            frame_actual_saltando=0;
            estado_posicion="";
        }
        int desplazamiento=-1;
        if(frame_actual_saltando>=6)
            desplazamiento=1;
        if(frame_actual_saltando!=6)
            setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        setEntero("posicion_x",20+getEntero("posicion_x"));
        frame_actual_saltando++;
    }
    if(estado_posicion=="saltando_atras")
    {
        if(frame_actual_saltando==13)
        {
            frame_actual_saltando=0;
            estado_posicion="";
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
