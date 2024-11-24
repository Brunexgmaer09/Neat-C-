#pragma once
#include "Rede.hpp"
#include <SDL2/SDL.h>

namespace NEAT {

class Visualizador {
public:
    // Estrutura de configuração para personalizar a visualização
    struct Configuracao {
        int largura;         // Largura da área de visualização
        int altura;          // Altura da área de visualização
        int raioNo;         // Tamanho dos nós
        bool mostrarPesos;  // Mostrar valores dos pesos nas conexões
        bool mostrarBordas; // Mostrar bordas nos nós
        SDL_Color corFundo; // Cor do fundo da visualização
        SDL_Color corEntrada; // Cor dos nós de entrada (verde)
        SDL_Color corOculta;  // Cor dos nós ocultos (amarelo)
        SDL_Color corSaida;   // Cor dos nós de saída (vermelho)

        // Construtor com valores padrão
        Configuracao() {
            largura = 200;
            altura = 300;
            raioNo = 5;
            mostrarPesos = true;
            mostrarBordas = true;
            // Cores padrão
            corFundo = {30, 30, 30, 200};     // Cinza semi-transparente
            corEntrada = {0, 255, 0, 255};    // Verde
            corOculta = {255, 255, 0, 255};   // Amarelo
            corSaida = {255, 0, 0, 255};      // Vermelho
        }
    };

private:
    SDL_Renderer* renderer;  // Renderizador SDL
    SDL_Rect area;          // Área onde a rede será renderizada
    Configuracao config;    // Configurações de visualização

public:
    // Construtor
    Visualizador(SDL_Renderer* renderer, const SDL_Rect& area, 
                 const Configuracao& config = Configuracao());
    
    // Método principal de renderização
    void renderizar(const Rede& rede);

    // Métodos para ajustar a visualização em tempo real
    void definirArea(const SDL_Rect& novaArea) { area = novaArea; }
    void definirConfiguracao(const Configuracao& novaConfig) { config = novaConfig; }
    
    // Getters para configuração atual
    const Configuracao& obterConfiguracao() const { return config; }
    const SDL_Rect& obterArea() const { return area; }
};

} // namespace NEAT 
