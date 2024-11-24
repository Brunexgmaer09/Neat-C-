#include "../HEADERS/Visualizador.hpp"
#include <map>
#include <algorithm>
#include <iostream>

namespace NEAT {

Visualizador::Visualizador(SDL_Renderer* renderer, const SDL_Rect& area, 
                         const Configuracao& config)
    : renderer(renderer), area(area), config(config) {
}

void Visualizador::renderizar(const Rede& rede) {
    // Desenhar fundo semi-transparente para melhor visualização
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 
        config.corFundo.r, config.corFundo.g, 
        config.corFundo.b, config.corFundo.a);
    SDL_RenderFillRect(renderer, &area);
    
    const auto& nos = rede.obterNos();
    const auto& conexoes = rede.obterConexoes();
    
    // Organizar nós por camada (entrada, oculta, saída)
    // Isso permite que a visualização se adapte quando novos nós são adicionados
    std::vector<std::vector<const No*>> camadasNos(3);  
    
    for (const auto& no : nos) {
        if (no.camada >= 0 && no.camada < 3) {
            camadasNos[no.camada].push_back(&no);
        }
    }

    // Log para debug da estrutura atual
    std::cout << "\n[Visualizador] Estrutura atual da rede:"
              << "\n - Nós de entrada: " << camadasNos[0].size()
              << "\n - Nós ocultos: " << camadasNos[1].size()
              << "\n - Nós de saída: " << camadasNos[2].size() << std::endl;
    
    // Calcular posições dos nós dinamicamente
    std::map<int, SDL_Point> posicoes;
    
    // Posicionar cada camada
    // A visualização se ajusta automaticamente ao número de nós em cada camada
    for (int camada = 0; camada < 3; camada++) {
        // Calcular posição X da camada
        float x = area.x + (camada * area.w / 2.0f);
        if (camada == 1) {  // Centralizar nós ocultos
            x = area.x + (area.w / 2.0f);
        }
        
        const auto& nosNaCamada = camadasNos[camada];
        // Distribuir nós verticalmente com espaçamento dinâmico
        float espacoY = area.h / (nosNaCamada.size() + 1);
        
        for (size_t i = 0; i < nosNaCamada.size(); i++) {
            float y = area.y + ((i + 1) * espacoY);
            posicoes[nosNaCamada[i]->id] = {
                static_cast<int>(x),
                static_cast<int>(y)
            };
        }
    }
    
    // Desenhar conexões
    // As conexões são coloridas com base no peso (vermelho = negativo, verde = positivo)
    for (const auto& conexao : conexoes) {
        if (!conexao.ativo) continue;  // Pular conexões desativadas
        
        auto itInicio = posicoes.find(conexao.deNo);
        auto itFim = posicoes.find(conexao.paraNo);
        
        if (itInicio != posicoes.end() && itFim != posicoes.end()) {
            // Cor baseada no peso da conexão
            int intensidade = std::min(255, static_cast<int>(std::abs(conexao.peso) * 255));
            Uint8 r = conexao.peso < 0 ? intensidade : 0;
            Uint8 g = conexao.peso > 0 ? intensidade : 0;
            SDL_SetRenderDrawColor(renderer, r, g, 0, 255);
            
            // Desenhar linha da conexão
            SDL_RenderDrawLine(renderer,
                itInicio->second.x, itInicio->second.y,
                itFim->second.x, itFim->second.y);
        }
    }
    
    // Desenhar nós
    // Cada tipo de nó tem uma cor diferente para fácil identificação
    for (const auto& [id, pos] : posicoes) {
        auto it = std::find_if(nos.begin(), nos.end(),
            [id](const No& n) { return n.id == id; });
            
        if (it != nos.end()) {
            SDL_Color cor;
            switch (it->camada) {
                case 0: cor = config.corEntrada; break;  // Verde para entrada
                case 1: cor = config.corOculta; break;   // Amarelo para ocultos
                case 2: cor = config.corSaida; break;    // Vermelho para saída
            }
            
            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
            
            // Desenhar nó como retângulo
            SDL_Rect noRect = {
                pos.x - config.raioNo,
                pos.y - config.raioNo,
                config.raioNo * 2,
                config.raioNo * 2
            };
            SDL_RenderFillRect(renderer, &noRect);
            
            // Desenhar borda do nó
            if (config.mostrarBordas) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &noRect);
            }
        }
    }

    // Log do número de conexões ativas
    std::cout << "[Visualizador] Conexões ativas: " 
              << std::count_if(conexoes.begin(), conexoes.end(), 
                             [](const Conexao& c) { return c.ativo; })
              << "/" << conexoes.size() << std::endl;
}

} // namespace NEAT 