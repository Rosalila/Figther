#include "../include/Grafico.h"

class Stage
{
    public:
    video::ITexture *imagen_fondo,*imagen_barra;
    Grafico* grafico;
    Stage(video::ITexture* imagen_fondo,video::ITexture* imagen_barra,Grafico* grafico);
    void dibujar();
};
