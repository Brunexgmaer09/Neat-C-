#pragma once
#include <stdexcept>
#include <string>

namespace NEAT {

class ErroNEAT : public std::runtime_error {
public:
    explicit ErroNEAT(const std::string& msg) : std::runtime_error(msg) {}
};

class ErroRedeInvalida : public ErroNEAT {
public:
    explicit ErroRedeInvalida(const std::string& msg) 
        : ErroNEAT("Rede inválida: " + msg) {}
};

class ErroCruzamento : public ErroNEAT {
public:
    explicit ErroCruzamento(const std::string& msg) 
        : ErroNEAT("Erro no cruzamento: " + msg) {}
};

} // namespace NEAT 