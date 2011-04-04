#include "../include/AtributosPersonaje.h"

Barra::Barra(int valor_maximo,int valor_actual,int modificador_periodico,int periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[])
{
    this->valor_maximo=valor_maximo;
    this->valor_actual=valor_actual;
    this->modificador_periodico=modificador_periodico;
    this->periodo=periodo;
    this->color=color;
    this->posicion=posicion;
    //this->imagenes=&imagenes;
}
Barra::Barra()
{

}

HitBox::HitBox (int p1x,int p1y,int p2x,int p2y)
{
    this->p1x=p1x;
    this->p1y=p1y;
    this->p2x=p2x;
    this->p2y=p2y;
    this->siguiente=siguiente;
}

ModificadorImagen::ModificadorImagen(video::ITexture* modificador,Personaje* personaje,std::string variable)
{
    tipo="imagen";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_imagen=modificador;
}

ModificadorEntero::ModificadorEntero(int modificador,Personaje* personaje,std::string variable,bool relativo)
{
    tipo="entero";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_entero=modificador;
    this->relativo=relativo;
}
ModificadorBarra::ModificadorBarra(Barra modificador,Personaje* personaje,std::string variable)
{
    tipo="barra";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_barra=modificador;
}
ModificadorHitboxes::ModificadorHitboxes(vector <HitBox> modificador,Personaje* personaje,std::string variable)
{
    tipo="hitboxes";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_hitbox=modificador;
}

Frame::Frame(int duracion)
{
    this->modificadores=vector<Modificador>();
    this->duracion=duracion;
}
void Frame::agregarModificador(video::ITexture* modificador,Personaje* personaje,std::string variable)
{
    modificadores.push_back(ModificadorImagen(modificador,personaje,variable));
}
void Frame::agregarModificador(int modificador,Personaje* personaje,std::string variable,bool relativo)
{
    modificadores.push_back(ModificadorEntero(modificador,personaje,variable,relativo));
}
void Frame::agregarModificador(Barra modificador,Personaje* personaje,std::string variable)
{
    modificadores.push_back(ModificadorBarra(modificador,personaje,variable));
}
void Frame::agregarModificador(vector <HitBox> modificador,Personaje* personaje,std::string variable)
{
    modificadores.push_back(ModificadorHitboxes(modificador,personaje,variable));
}

Movimiento::Movimiento()
{
    frame_actual=0;
}
Frame Movimiento::getFrameActual()
{
    return frames[frame_actual];
}
void Movimiento::agregarFrame(int duracion)
{
    frames.push_back(Frame(duracion));
}
