#include "../Headers/Configuracao.h"

namespace NEAT {

float ConfiguracaoNEAT::COEF_EXCESSO = 1.0f;
float ConfiguracaoNEAT::COEF_DISJUNTO = 1.0f;
float ConfiguracaoNEAT::COEF_PESO = 0.4f;

float ConfiguracaoNEAT::CHANCE_PESO_PERTURBADO = 0.8f;
float ConfiguracaoNEAT::CHANCE_CONEXAO_TOGGLE = 0.15f;
float ConfiguracaoNEAT::CHANCE_NOVO_NO = 0.2f;
float ConfiguracaoNEAT::CHANCE_NOVA_CONEXAO = 0.25f;

int ConfiguracaoNEAT::MAX_NOS = 1000;
int ConfiguracaoNEAT::MAX_CONEXOES = 2000;

void ConfiguracaoNEAT::inicializarPadrao() {
    COEF_EXCESSO = 1.0f;
    COEF_DISJUNTO = 1.0f;
    COEF_PESO = 0.4f;
    
    CHANCE_PESO_PERTURBADO = 0.8f;
    CHANCE_CONEXAO_TOGGLE = 0.15f;
    CHANCE_NOVO_NO = 0.2f;
    CHANCE_NOVA_CONEXAO = 0.25f;
    
    MAX_NOS = 1000;
    MAX_CONEXOES = 2000;
}

} // namespace NEAT 