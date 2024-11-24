#pragma once
#include "Rede.hpp"
#include <vector>
#include <functional>

namespace NEAT {

class Populacao {
private:
    std::vector<Rede> individuos;
    int geracao;
    float melhorAptidao;
    
    struct Configuracao {
        int tamanhoPopulacao = 150;
        float taxaMutacao = 0.3f;
        float taxaCruzamento = 0.75f;
        float taxaElitismo = 0.1f;
        int tamanhoTorneio = 3;
        int maxEspecies = 10;
    } config;

public:
    Populacao(int numEntradas, int numSaidas, const Configuracao& config = Configuracao());
    
    void evoluir();
    void avaliarPopulacao(std::function<float(Rede&)> funcaoAvaliacao);
    void selecao();
    void cruzamento();
    void mutacao();
    void especiar();
    void ajustarAptidoes();
    void eliminarEspeciesFracas();
    
    // Métodos auxiliares
    Rede* selecaoTorneio(int tamanhoTorneio);
    Rede cruzarRedes(const Rede& rede1, const Rede& rede2);
    void analisarDiversidade(const std::vector<Rede>& populacao);
    
    // Persistência
    void salvarMelhorRede(const std::string& arquivo);
    void carregarMelhorRede(const std::string& arquivo);
    
    // Getters
    const std::vector<Rede>& obterIndividuos() const { return individuos; }
    int obterGeracao() const { return geracao; }
    float obterMelhorAptidao() const { return melhorAptidao; }
};

} // namespace NEAT 
