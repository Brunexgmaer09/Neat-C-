#pragma once
#include <string>
#include "Rede.hpp"
#include "Populacao.hpp"

namespace NEAT {

class Persistencia {
public:
    static void salvarPopulacao(const Populacao& pop, const std::string& arquivo);
    static Populacao carregarPopulacao(const std::string& arquivo);
    
    static void exportarRede(const Rede& rede, const std::string& arquivo);
    static void importarRede(Rede& rede, const std::string& arquivo);
    
    // Formato JSON para melhor interoperabilidade
    static std::string redeParaJSON(const Rede& rede);
    static Rede redeDeJSON(const std::string& json);
};

} // namespace NEAT 