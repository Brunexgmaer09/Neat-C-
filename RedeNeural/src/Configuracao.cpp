#include "../Headers/Configuracao.h"

namespace NEAT {

float ConfiguracaoNEAT::COEF_EXCESSO = 1.0f;
float ConfiguracaoNEAT::COEF_DISJUNTO = 1.0f;
float ConfiguracaoNEAT::COEF_PESO = 0.4f;

float ConfiguracaoNEAT::CHANCE_PESO_PERTURBADO = 0.8f;
float ConfiguracaoNEAT::CHANCE_CONEXAO_TOGGLE = 0.15f;
float ConfiguracaoNEAT::CHANCE_NOVO_NO = 0.9f;
float ConfiguracaoNEAT::CHANCE_NOVA_CONEXAO = 0.9f;

int ConfiguracaoNEAT::MAX_NOS = 10;
int ConfiguracaoNEAT::MAX_CONEXOES = 20;

void ConfiguracaoNEAT::inicializarPadrao() {
    COEF_EXCESSO = 1.0f;
    COEF_DISJUNTO = 1.0f;
    COEF_PESO = 0.4f;
    
    CHANCE_PESO_PERTURBADO = 0.8f;
    CHANCE_CONEXAO_TOGGLE = 0.15f;
    CHANCE_NOVO_NO = 0.9f;
    CHANCE_NOVA_CONEXAO = 0.9f;
    
    MAX_NOS = 10;
    MAX_CONEXOES = 20;
}

} // namespace NEAT 
