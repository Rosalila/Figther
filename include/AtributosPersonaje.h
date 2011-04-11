#include <vector>
#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include "../include/Grafico.h"
#include "../include/Sonido.h"

class Personaje;

class Barra
{
public:
    int valor_maximo;
    int valor_actual;
    int modificador_periodico;
    int periodo;
    video::SColor color;
    core::rect<s32> posicion;
    irr::video::ITexture* imagenes[];

    Barra(int valor_maximo,int valor_actual,int modificador_periodico,int periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[]);
    Barra();
};

class HitBox
{
public:
    int p1x,p1y,p2x,p2y;

    HitBox (int p1x,int p1y,int p2x,int p2y);
};

class Imagen
{
public:
    int dimension_x,dimension_y,alineacion_x,alineacion_y;
    video::ITexture* imagen;

    Imagen(video::ITexture* imagen,int dimension_x,int dimension_y,int alineacion_x,int alineacion_y);
    Imagen();
};

class Modificador
{
    public:
    //info
    bool aplicar_a_contrario;
    std::string tipo;
    Personaje* personaje;
    std::string variable;
    bool relativo;
    //modificadores
    Imagen modificador_imagen;
    int modificador_entero;
    Barra modificador_barra;
    vector <HitBox> modificador_hitbox;
    std::string modificador_string;
};

class ModificadorImagen : public Modificador
{
    public:
    ModificadorImagen(Imagen modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
};

class ModificadorEntero : public Modificador
{
    public:
    ModificadorEntero(int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario);
};

class ModificadorBarra : public Modificador
{
    public:
    ModificadorBarra(Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
};

class ModificadorHitboxes : public Modificador
{
    public:
    ModificadorHitboxes(vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
};

class ModificadorString : public Modificador
{
    public:
    ModificadorString(std::string modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
};

class Frame
{
    public:
    vector <Modificador> modificadores;
    int duracion;
    Frame(int duracion);
    //modificadores
    void agregarModificador(Imagen modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
};

class Movimiento
{
    public:
    int frame_actual;
    vector <Frame> frames;
    vector <std::string> cancels;
    Movimiento();
    Frame getFrameActual();
    void agregarFrame(int duracion);
};
