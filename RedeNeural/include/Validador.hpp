
#pragma once
#include "Rede.hpp"
#include "Logger.hpp"
#include <stdexcept>
#include <algorithm>
#include <functional>

namespace NEAT {

class Validador {
public:
    // Validação de Rede
    static bool validarRede(const Rede& rede) {
        try {
            // Verifica estrutura básica
            if (rede.obterNos().empty()) {
                Logger::log(Logger::Nivel::ERROR, "Rede inválida: sem nós");
                return false;
            }

            // Verifica conexões
            for (const auto& conexao : rede.obterConexoes()) {
                if (!validarConexao(conexao, rede)) {
                    return false;
                }
            }

            // Verifica camadas
            if (!validarCamadas(rede)) {
                return false;
            }

            return true;
        }
        catch (const std::exception& e) {
            Logger::log(Logger::Nivel::ERROR, "Erro ao validar rede: " + std::string(e.what()));
            return false;
        }
    }

private:
    static bool validarConexao(const Conexao& conexao, const Rede& rede) {
        const auto& nos = rede.obterNos();
        
        // Verifica se os nós da conexão existem
        auto noInicio = std::find_if(nos.begin(), nos.end(),
            [&](const No& no) { return no.id == conexao.deNo; });
            
        auto noFim = std::find_if(nos.begin(), nos.end(),
            [&](const No& no) { return no.id == conexao.paraNo; });

        if (noInicio == nos.end() || noFim == nos.end()) {
            Logger::log(Logger::Nivel::ERROR, 
                "Conexão inválida: nós não encontrados");
            return false;
        }

        // Verifica direção da conexão (não pode haver ciclos)
        if (noInicio->camada >= noFim->camada) {
            Logger::log(Logger::Nivel::ERROR, 
                "Conexão inválida: direção incorreta entre camadas");
            return false;
        }

        return true;
    }

    static bool validarCamadas(const Rede& rede) {
        const auto& nos = rede.obterNos();
        
        // Verifica se existem nós de entrada e saída
        bool temEntrada = false;
        bool temSaida = false;

        for (const auto& no : nos) {
            if (no.camada == 0) temEntrada = true;
            if (no.camada == 2) temSaida = true;
        }

        if (!temEntrada || !temSaida) {
            Logger::log(Logger::Nivel::ERROR, 
                "Rede inválida: faltam nós de entrada ou saída");
            return false;
        }

        return true;
    }
};

} // namespace NEAT 