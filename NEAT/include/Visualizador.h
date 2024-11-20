#pragma once
#include "Rede.h"
#include <SDL2/SDL.h>

namespace NEAT {

class Visualizador {
public:
    struct Configuracao {
        int largura = 200;
        int altura = 300;
        int raioNo = 5;
        bool mostrarPesos = true;
        bool mostrarBordas = true;
        SDL_Color corFundo = {0, 0, 0, 128};
        SDL_Color corEntrada = {255, 0, 0, 255};
        SDL_Color corOculta = {0, 255, 0, 255};
        SDL_Color corSaida = {0, 0, 255, 255};
    };

private:
    SDL_Renderer* renderer;
    SDL_Rect area;
    Configuracao config;

public:
    Visualizador(SDL_Renderer* renderer, const SDL_Rect& area, 
                 const Configuracao& config = Configuracao());
    
    void renderizar(const Rede& rede);
    void definirArea(const SDL_Rect& novaArea) { area = novaArea; }
    void definirConfiguracao(const Configuracao& novaConfig) { config = novaConfig; }
};

} // namespace NEAT 