#include "../include/Configuracao.h"

namespace NEAT {

float ConfiguracaoNEAT::COEF_EXCESSO = 1.0f;
float ConfiguracaoNEAT::COEF_DISJUNTO = 1.0f;
float ConfiguracaoNEAT::COEF_PESO = 0.4f;

float ConfiguracaoNEAT::CHANCE_PESO_PERTURBADO = 0.9f;
float ConfiguracaoNEAT::CHANCE_CONEXAO_TOGGLE = 0.1f;
float ConfiguracaoNEAT::CHANCE_NOVO_NO = 0.03f;
float ConfiguracaoNEAT::CHANCE_NOVA_CONEXAO = 0.05f;

int ConfiguracaoNEAT::MAX_NOS = 1000;
int ConfiguracaoNEAT::MAX_CONEXOES = 2000;

void ConfiguracaoNEAT::inicializarPadrao() {
    COEF_EXCESSO = 1.0f;
    COEF_DISJUNTO = 1.0f;
    COEF_PESO = 0.4f;
    
    CHANCE_PESO_PERTURBADO = 0.9f;
    CHANCE_CONEXAO_TOGGLE = 0.1f;
    CHANCE_NOVO_NO = 0.03f;
    CHANCE_NOVA_CONEXAO = 0.05f;
    
    MAX_NOS = 1000;
    MAX_CONEXOES = 2000;
}

} // namespace NEAT 