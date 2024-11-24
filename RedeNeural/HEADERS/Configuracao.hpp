#pragma once

namespace NEAT {

struct ConfiguracaoNEAT {
    // Parâmetros de compatibilidade
    static float COEF_EXCESSO;
    static float COEF_DISJUNTO;
    static float COEF_PESO;
    
    // Parâmetros de mutação
    static float CHANCE_PESO_PERTURBADO;
    static float CHANCE_CONEXAO_TOGGLE;
    static float CHANCE_NOVO_NO;
    static float CHANCE_NOVA_CONEXAO;
    
    // Limites
    static int MAX_NOS;
    static int MAX_CONEXOES;
    
    // Adicionar validações e limites
    struct Limites {
        static constexpr float MIN_PESO = -4.0f;
        static constexpr float MAX_PESO = 4.0f;
        static constexpr int MAX_CAMADAS = 10;
        static constexpr int MAX_NOS_POR_CAMADA = 50;
        static constexpr float MAX_TAXA_MUTACAO = 1.0f;
    };

    // Adicionar validação de configuração
    static bool validarConfiguracao() {
        if (COEF_EXCESSO < 0 || COEF_DISJUNTO < 0 || COEF_PESO < 0) return false;
        if (CHANCE_PESO_PERTURBADO < 0 || CHANCE_PESO_PERTURBADO > 1) return false;
        if (MAX_NOS <= 0 || MAX_CONEXOES <= 0) return false;
        return true;
    }

    // Inicialização padrão
    static void inicializarPadrao();
};

} // namespace NEAT 
