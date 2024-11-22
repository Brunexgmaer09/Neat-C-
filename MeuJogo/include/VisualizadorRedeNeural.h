#pragma once
#include "RedeNeural/include/Rede.h"
#include <SDL2/SDL.h>

class VisualizadorRedeNeural {
private:
    SDL_Renderer* renderer;
    SDL_Rect areaVisualizacao;
    
    struct ConfiguracaoVisual {
        int raioNo = 10;
        int espacamentoHorizontal = 150;
        int espacamentoVertical = 50;
        SDL_Color corFundo = {40, 44, 52, 255};      // Fundo escuro
        SDL_Color corNoEntrada = {52, 152, 219, 255}; // Azul
        SDL_Color corNoOculto = {46, 204, 113, 255};  // Verde
        SDL_Color corNoSaida = {231, 76, 60, 255};    // Vermelho
        SDL_Color corConexaoPositiva = {255, 255, 255, 180}; // Branco transparente
        SDL_Color corConexaoNegativa = {231, 76, 60, 180};   // Vermelho transparente
        bool mostrarPesos = true;
        int tamanhoFonte = 12;
    };
    
    ConfiguracaoVisual config;
    
    void desenharNo(int x, int y, const SDL_Color& cor, float valor = 0.0f);
    void desenharConexao(int x1, int y1, int x2, int y2, float peso);
    void desenharTexto(const char* texto, int x, int y);

public:
    VisualizadorRedeNeural(SDL_Renderer* renderer, const SDL_Rect& area);
    void renderizar(const NEAT::Rede& rede);
    void definirArea(const SDL_Rect& area) { areaVisualizacao = area; }
}; 