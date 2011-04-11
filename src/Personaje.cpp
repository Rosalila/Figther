#include "../include/Personaje.h"

void flipHitBoxes(Personaje* personaje)
{
    int hitboxes_size=personaje->getHitBoxes("azules").size();
    for(int i=0;i<hitboxes_size;i++)
    {
        int a=personaje->getHitBoxes("azules")[i].p1x;
        int b=personaje->getHitBoxes("azules")[i].p2x;
        personaje->getHitBoxes("azules")[i].p1x=-b;
        personaje->getHitBoxes("azules")[i].p2x=-a;
    }
    hitboxes_size=personaje->getHitBoxes("rojas").size();
    for(int i=0;i<hitboxes_size;i++)
    {
        int a=personaje->getHitBoxes("rojas")[i].p1x;
        int b=personaje->getHitBoxes("rojas")[i].p2x;
        personaje->getHitBoxes("rojas")[i].p1x=-b;
        personaje->getHitBoxes("rojas")[i].p2x=-a;
    }
}

Personaje::Personaje(Barra hp,int px,int py,int a,std::string orientacion,Grafico* grafico)
{
    setImagen("imagen_personaje",Imagen(grafico->driver->getTexture("resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png"),100,100,100,100));
    this->grafico=grafico;
    strings["estado_posicion"]="";
    strings["movimiento_actual"]="";
    strings["orientacion"]="";
    enteros["tiempo_transcurrido"]=0;
    enteros["frame_actual_saltando"]=0;

    setString("estado_posicion","");
    setEntero("frame_actual_saltando",0);
    setEntero("tiempo_transcurrido",0);
    setString("orientacion",orientacion);
    setString("movimiento_actual","5");

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
    int dimension_x=getImagen("imagen_personaje").dimension_x;
    int dimension_y=getImagen("imagen_personaje").dimension_y;
    int alineacion_x=getImagen("imagen_personaje").alineacion_x;
    int alineacion_y=getImagen("imagen_personaje").alineacion_y;
    grafico->draw2DImage
    (   getImagen("imagen_personaje").imagen,
        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
        irr::core::position2d<irr::f32>(getEntero("posicion_x")-(dimension_x/2)+alineacion_x,getEntero("posicion_y")-(dimension_y/2)+alineacion_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (1,1),
        true,
        irr::video::SColor(255,255,255,255),
        getString("orientacion")=="i",
        false);
}
void Personaje::dibujarHitBoxes(std::string variable,video::SColor color,bool izquierda)
{
    vector <HitBox> hitbox=getHitBoxes(variable);
    if(izquierda)
    {
        int hitboxes_size=hitbox.size();
        for(int i=0;i<hitboxes_size;i++)
        {
            int a=hitbox[i].p1x;
            int b=hitbox[i].p2x;
            hitbox[i].p1x=-b;
            hitbox[i].p2x=-a;
        }
    }
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
    return movimientos[getString("movimiento_actual")];
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
Imagen Personaje::getImagen(std::string variable)
{
    return imagenes[variable];
}
std::string Personaje::getString(std::string variable)
{
    return strings[variable];
}
//SETS variables
void Personaje::setImagen(std::string variable,Imagen valor)
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
void Personaje::setString(std::string variable,std::string valor)
{
    strings[variable]=valor;
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
void Personaje::agregarModificador(std::string movimiento,int frame,Imagen modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
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
void Personaje::agregarModificador(std::string movimiento,int frame,std::string modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
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

    vector <HitBox> hb_azules=atacado->getHitBoxes("azules");
    vector <HitBox> hb_rojas=atacante->getHitBoxes("rojas");

    if(atacado->getString("orientacion")=="i")
    {
        int hitboxes_size=hb_azules.size();
        for(int i=0;i<hitboxes_size;i++)
        {
            int a=hb_azules[i].p1x;
            int b=hb_azules[i].p2x;
            hb_azules[i].p1x=-b;
            hb_azules[i].p2x=-a;
        }
    }
    if(atacante->getString("orientacion")=="i")
    {
        int hitboxes_size=hb_rojas.size();
        for(int i=0;i<hitboxes_size;i++)
        {
            int a=hb_rojas[i].p1x;
            int b=hb_rojas[i].p2x;
            hb_rojas[i].p1x=-b;
            hb_rojas[i].p2x=-a;
        }
    }

    int hb_azul_size=hb_azules.size();
    int hb_roja_size=hb_rojas.size();
    for(int a=0;a<hb_azul_size;a++)
        for(int r=0;r<hb_roja_size;r++)
            if(getColisionHitBoxes(hb_azules[a],hb_rojas[r],ax,ay,rx,ry))
                return true;
    return false;
}

bool Personaje::verificarFinDeMovimiento()
{
    int frames_size=getMovimientoActual()->frames.size();
    if(frames_size==getMovimientoActual()->frame_actual)
    {
        getMovimientoActual()->frame_actual=0;
        setString("movimiento_actual","5");
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
        if(((Movimiento*)movimientos[input])->cancels[i]==getString("movimiento_actual"))
        {
            if(getEntero("frame_actual_saltando")==0 || (getString("estado_posicion")=="agachado" && input=="agachado5") || (getString("estado_posicion")=="agachado" && input=="5"))
                setString("estado_posicion","");
            getMovimientoActual()->frame_actual=0;
            setString("movimiento_actual",input);
            if(input=="saltando_atras7")
                setString("estado_posicion","saltando_atras");
            if(input=="saltando8")
                setString("estado_posicion","saltando");
            if(input=="saltando_adelante9")
                setString("estado_posicion","saltando_adelante");
            if(input=="agachado2")
                setString("estado_posicion","agachado");
            return true;
        }
    return false;
}
bool Personaje::aplicarModificadores()
{
    if(getEntero("tiempo_transcurrido")>getFrameActual().duracion)
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
                        Barra barra=mod_imagen->personaje->personaje_contrario->getBarra("hp");
                        barra.valor_actual-=10;
                        mod_imagen->personaje->personaje_contrario->setBarra("hp",barra);
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
            if(modificador.tipo=="string")
            {
                ModificadorString* mod_string=(ModificadorString*)&modificador;
                if(mod_string->aplicar_a_contrario)
                    mod_string->personaje->personaje_contrario->setString(mod_string->variable,mod_string->modificador_string);
                else
                    mod_string->personaje->setString(mod_string->variable,mod_string->modificador_string);
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
        setEntero("tiempo_transcurrido",0);
        return true;
    }
    if(getString("estado_posicion")=="saltando")
    {
        if(getEntero("frame_actual_saltando")==12)
        {
            setEntero("frame_actual_saltando",0);
            setString("estado_posicion","");
        }
        int desplazamiento=-1;
        if(getEntero("frame_actual_saltando")>=6)
            desplazamiento=1;
        setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        setEntero("frame_actual_saltando",getEntero("frame_actual_saltando")+1);
    }
    if(getString("estado_posicion")=="saltando_adelante")
    {
        if(getEntero("frame_actual_saltando")==13)
        {
            setEntero("frame_actual_saltando",0);
            setString("estado_posicion","");
        }
        int desplazamiento=-1;
        if(getEntero("frame_actual_saltando")>=6)
            desplazamiento=1;
        if(getEntero("frame_actual_saltando")!=6)
            setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        setEntero("posicion_x",20+getEntero("posicion_x"));
        setEntero("frame_actual_saltando",getEntero("frame_actual_saltando")+1);
    }
    if(getString("estado_posicion")=="saltando_atras")
    {
        if(getEntero("frame_actual_saltando")==13)
        {
            setEntero("frame_actual_saltando",0);
            setString("estado_posicion","");
        }
        int desplazamiento=-1;
        if(getEntero("frame_actual_saltando")>=6)
            desplazamiento=1;
        if(getEntero("frame_actual_saltando")!=6)
            setEntero("posicion_y",desplazamiento*20+getEntero("posicion_y"));
        setEntero("posicion_x",-20+getEntero("posicion_x"));
        setEntero("frame_actual_saltando",getEntero("frame_actual_saltando")+1);
    }
    return false;
}
