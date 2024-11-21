#include "../include/Especie.h"
#include <cmath>

namespace NEAT {

Especie::Especie(const Rede& primeiro) 
    : representante(primeiro), 
      aptidaoAjustada(0), 
      geracoesSemMelhoria(0), 
      melhorAptidao(0) {
}

void Especie::adicionarMembro(Rede* rede) {
    membros.push_back(rede);
}

void Especie::calcularAptidaoAjustada() {
    if (membros.empty()) return;
    
    aptidaoAjustada = 0;
    for (auto membro : membros) {
        aptidaoAjustada += membro->obterAptidao();
    }
    aptidaoAjustada /= membros.size();
    
    // Atualizar melhor aptidão
    float melhorAtual = membros[0]->obterAptidao();
    for (size_t i = 1; i < membros.size(); i++) {
        melhorAtual = std::max(melhorAtual, membros[i]->obterAptidao());
    }
    
    if (melhorAtual > melhorAptidao) {
        melhorAptidao = melhorAtual;
        geracoesSemMelhoria = 0;
    } else {
        geracoesSemMelhoria++;
    }
}

bool Especie::verificarCompatibilidade(const Rede& rede) const {
    // Implementação simplificada - pode ser melhorada
    const auto& conexoesA = representante.obterConexoes();
    const auto& conexoesB = rede.obterConexoes();
    
    // Calcular diferença média dos pesos
    float somaDiferencas = 0;
    int conexoesComuns = 0;
    
    for (size_t i = 0; i < std::min(conexoesA.size(), conexoesB.size()); i++) {
        somaDiferencas += std::abs(conexoesA[i].peso - conexoesB[i].peso);
        conexoesComuns++;
    }
    
    if (conexoesComuns == 0) return false;
    
    float diferencaMedia = somaDiferencas / conexoesComuns;
    return diferencaMedia < 3.0f; // Limiar de compatibilidade
}

} // namespace NEAT 