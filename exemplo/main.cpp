#include "RedeNeural/include/Populacao.h"
#include "RedeNeural/include/Visualizador.h"

int main() {
    // Configuração básica
    NEAT::Populacao::Configuracao config;
    config.tamanhoPopulacao = 150;
    config.taxaMutacao = 0.3f;
    
    // Criar população (2 entradas, 1 saída)
    NEAT::Populacao populacao(2, 1, config);
    
    // Função de avaliação
    auto avaliarRede = [](NEAT::Rede& rede) {
        // Sua lógica de avaliação aqui
        return 0.0f;
    };
    
    // Loop principal de evolução
    for (int geracao = 0; geracao < 100; geracao++) {
        populacao.avaliarPopulacao(avaliarRede);
        populacao.evoluir();
    }
    
    return 0;
} 