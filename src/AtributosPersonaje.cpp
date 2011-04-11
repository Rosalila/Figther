#include "../include/AtributosPersonaje.h"

Barra::Barra(int valor_maximo,int valor_actual,int modificador_periodico,int periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[])
{
    this->valor_maximo=valor_maximo;
    this->valor_actual=valor_actual;
    this->modificador_periodico=modificador_periodico;
    this->periodo=periodo;
    this->color=color;
    this->posicion=posicion;
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
}

Imagen::Imagen(video::ITexture* imagen,int dimension_x,int dimension_y,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->dimension_x=dimension_x;
    this->dimension_y=dimension_y;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}
Imagen::Imagen()
{

}

ModificadorImagen::ModificadorImagen(Imagen modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    tipo="imagen";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_imagen=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}

ModificadorEntero::ModificadorEntero(int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario)
{
    tipo="entero";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_entero=modificador;
    this->relativo=relativo;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorBarra::ModificadorBarra(Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    tipo="barra";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_barra=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorHitboxes::ModificadorHitboxes(vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    tipo="hitboxes";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_hitbox=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
ModificadorString::ModificadorString(std::string modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    tipo="string";
    this->personaje=personaje;
    this->variable=variable;
    this->modificador_string=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}

Frame::Frame(int duracion)
{
    this->modificadores=vector<Modificador>();
    this->duracion=duracion;
}
void Frame::agregarModificador(Imagen modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorImagen(modificador,personaje,variable,aplicar_a_contrario));
}
void Frame::agregarModificador(int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorEntero(modificador,personaje,variable,relativo,aplicar_a_contrario));
}
void Frame::agregarModificador(Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorBarra(modificador,personaje,variable,aplicar_a_contrario));
}
void Frame::agregarModificador(vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorHitboxes(modificador,personaje,variable,aplicar_a_contrario));
}
void Frame::agregarModificador(std::string modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorString(modificador,personaje,variable,aplicar_a_contrario));
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
