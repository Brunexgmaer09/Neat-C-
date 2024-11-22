#include "../include/VisualizadorRedeNeural.h"
#include <map>
#include <sstream>
#include <iomanip>

VisualizadorRedeNeural::VisualizadorRedeNeural(SDL_Renderer* renderer, const SDL_Rect& area)
    : renderer(renderer), areaVisualizacao(area) {
}

void VisualizadorRedeNeural::desenharNo(int x, int y, const SDL_Color& cor, float valor) {
    // Desenhar círculo preenchido
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
    
    for (int w = 0; w < config.raioNo * 2; w++) {
        for (int h = 0; h < config.raioNo * 2; h++) {
            int dx = config.raioNo - w;
            int dy = config.raioNo - h;
            if ((dx*dx + dy*dy) <= (config.raioNo * config.raioNo)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
    
    // Desenhar valor do nó se necessário
    if (config.mostrarPesos) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << valor;
        desenharTexto(ss.str().c_str(), x - config.raioNo, y - config.raioNo - 15);
    }
}

void VisualizadorRedeNeural::desenharConexao(int x1, int y1, int x2, int y2, float peso) {
    // Escolher cor baseada no peso
    SDL_Color cor = (peso >= 0) ? config.corConexaoPositiva : config.corConexaoNegativa;
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
    
    // Desenhar linha
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    
    // Desenhar peso se necessário
    if (config.mostrarPesos) {
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << peso;
        desenharTexto(ss.str().c_str(), midX, midY);
    }
}

void VisualizadorRedeNeural::desenharTexto(const char* texto, int x, int y) {
    // Aqui você pode implementar a renderização de texto usando SDL_TTF
    // ou sua biblioteca preferida de renderização de texto
}

void VisualizadorRedeNeural::renderizar(const NEAT::Rede& rede) {
    // Limpar área de visualização
    SDL_SetRenderDrawColor(renderer, 
        config.corFundo.r, config.corFundo.g, 
        config.corFundo.b, config.corFundo.a);
    SDL_RenderFillRect(renderer, &areaVisualizacao);
    
    const auto& nos = rede.obterNos();
    const auto& conexoes = rede.obterConexoes();
    
    // Mapear posições dos nós
    std::map<int, SDL_Point> posicoes;
    std::vector<std::vector<const NEAT::No*>> camadasNos(3); // entrada, oculta, saída
    
    // Organizar nós por camada
    for (const auto& no : nos) {
        camadasNos[no.camada].push_back(&no);
    }
    
    // Calcular posições dos nós
    for (int camada = 0; camada < 3; camada++) {
        int x = areaVisualizacao.x + (camada * config.espacamentoHorizontal) + 50;
        float espacoY = (float)areaVisualizacao.h / (camadasNos[camada].size() + 1);
        
        for (size_t i = 0; i < camadasNos[camada].size(); i++) {
            int y = areaVisualizacao.y + ((i + 1) * espacoY);
            posicoes[camadasNos[camada][i]->id] = {x, y};
        }
    }
    
    // Desenhar conexões
    for (const auto& conexao : conexoes) {
        if (!conexao.ativo) continue;
        
        auto itInicio = posicoes.find(conexao.deNo);
        auto itFim = posicoes.find(conexao.paraNo);
        
        if (itInicio != posicoes.end() && itFim != posicoes.end()) {
            desenharConexao(
                itInicio->second.x, itInicio->second.y,
                itFim->second.x, itFim->second.y,
                conexao.peso
            );
        }
    }
    
    // Desenhar nós
    for (const auto& [id, pos] : posicoes) {
        auto it = std::find_if(nos.begin(), nos.end(),
            [id](const NEAT::No& n) { return n.id == id; });
            
        if (it != nos.end()) {
            SDL_Color cor;
            switch (it->camada) {
                case 0: cor = config.corNoEntrada; break;
                case 1: cor = config.corNoOculto; break;
                case 2: cor = config.corNoSaida; break;
            }
            desenharNo(pos.x, pos.y, cor, it->valor);
        }
    }
} 