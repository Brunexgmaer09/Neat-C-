#pragma once
#include "Rede.h"
#include <vector>
#include <functional>

namespace NEAT {

class Populacao {
public:
    struct Configuracao {
        int tamanhoPopulacao = 50;
        float taxaElitismo = 0.1f;
        float taxaMutacao = 0.3f;
        float taxaCruzamento = 0.8f;
        int tamanhoTorneio = 3;
    };

private:
    Configuracao config;
    int geracao;
    float melhorAptidao;
    std::vector<Rede> individuos;
    
    // Função de callback para notificar eventos
    std::function<void(int, float, float, float)> onGeracaoCallback;

public:
    Populacao(int numEntradas, int numSaidas, const Configuracao& config = Configuracao());
    
    // Métodos principais
    void evoluir();
    void avaliarPopulacao(std::function<float(Rede&)> funcaoAvaliacao);
    
    // Getters
    int obterGeracao() const { return geracao; }
    float obterMelhorAptidao() const { return melhorAptidao; }
    const std::vector<Rede>& obterIndividuos() const { return individuos; }
    std::vector<Rede>& obterIndividuos() { return individuos; }
    
    // Callback para eventos
    void definirCallbackGeracao(std::function<void(int, float, float, float)> callback) {
        onGeracaoCallback = callback;
    }
    
    // Serialização
    void salvarMelhorRede(const std::string& arquivo);
    void carregarMelhorRede(const std::string& arquivo);

protected:
    Rede* selecaoTorneio(int tamanhoTorneio);
    Rede cruzarRedes(const Rede& rede1, const Rede& rede2);
};

} // namespace NEAT 