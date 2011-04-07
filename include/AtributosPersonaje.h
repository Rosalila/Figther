#include <vector>
#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include "../include/Grafico.h"

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
    HitBox* siguiente;

    HitBox (int p1x,int p1y,int p2x,int p2y);
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
    video::ITexture* modificador_imagen;
    int modificador_entero;
    Barra modificador_barra;
    vector <HitBox> modificador_hitbox;
};

class ModificadorImagen : public Modificador
{
    public:
    ModificadorImagen(video::ITexture* modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
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

class Frame
{
    public:
    vector <Modificador> modificadores;
    int duracion;
    Frame(int duracion);
    //modificadores
    void agregarModificador(video::ITexture* modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
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
