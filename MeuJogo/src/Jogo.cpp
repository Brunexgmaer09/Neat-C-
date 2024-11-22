#include "VisualizadorRedeNeural.h"

class Jogo {
private:
    NEAT::Populacao populacao;
    VisualizadorRedeNeural* visualizador;
    
public:
    void inicializar() {
        // ... outras inicializações ...
        
        // Criar área de visualização (ajuste conforme necessário)
        SDL_Rect areaVisual = {
            10,                     // x
            10,                     // y
            300,                    // largura
            200                     // altura
        };
        
        visualizador = new VisualizadorRedeNeural(renderer, areaVisual);
    }
    
    void renderizar() {
        // ... renderização do jogo ...
        
        // Renderizar a melhor rede
        const auto& individuos = populacao.obterIndividuos();
        auto melhorRede = std::max_element(individuos.begin(), individuos.end(),
            [](const NEAT::Rede& a, const NEAT::Rede& b) {
                return a.obterAptidao() < b.obterAptidao();
            });
            
        if (melhorRede != individuos.end()) {
            visualizador->renderizar(*melhorRede);
        }
    }
}; 