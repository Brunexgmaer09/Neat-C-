#include "../include/Populacao.h"
#include <algorithm>
#include <iostream>

namespace NEAT {

Populacao::Populacao(int numEntradas, int numSaidas, const Configuracao& config)
    : config(config), geracao(0), melhorAptidao(0) {
    
    // Criar população inicial
    for (int i = 0; i < config.tamanhoPopulacao; i++) {
        individuos.emplace_back(numEntradas, numSaidas);
    }
}

void Populacao::evoluir() {
    // Ordenar por aptidão
    std::sort(individuos.begin(), individuos.end(),
        [](const Rede& a, const Rede& b) {
            return a.obterAptidao() > b.obterAptidao();
        });
    
    // Calcular estatísticas
    float aptidaoTotal = 0;
    float aptidaoMinima = individuos[0].obterAptidao();
    float aptidaoMaxima = individuos[0].obterAptidao();
    
    for (const auto& individuo : individuos) {
        float aptidao = individuo.obterAptidao();
        aptidaoTotal += aptidao;
        aptidaoMinima = std::min(aptidaoMinima, aptidao);
        aptidaoMaxima = std::max(aptidaoMaxima, aptidao);
    }
    
    float aptidaoMedia = aptidaoTotal / individuos.size();
    melhorAptidao = aptidaoMaxima;
    
    // Notificar callback se existir
    if (onGeracaoCallback) {
        onGeracaoCallback(geracao, aptidaoMaxima, aptidaoMedia, aptidaoMinima);
    }
    
    // Nova geração
    std::vector<Rede> novaGeracao;
    
    // Elitismo
    int numElite = static_cast<int>(config.tamanhoPopulacao * config.taxaElitismo);
    for (int i = 0; i < numElite; i++) {
        novaGeracao.push_back(individuos[i]);
    }
    
    // Criar resto da população
    while (novaGeracao.size() < config.tamanhoPopulacao) {
        if ((float)rand() / RAND_MAX < config.taxaCruzamento) {
            Rede* pai1 = selecaoTorneio(config.tamanhoTorneio);
            Rede* pai2 = selecaoTorneio(config.tamanhoTorneio);
            Rede filho = cruzarRedes(*pai1, *pai2);
            if ((float)rand() / RAND_MAX < config.taxaMutacao) {
                filho.mutar();
            }
            novaGeracao.push_back(filho);
        } else {
            int idx = rand() % individuos.size();
            novaGeracao.push_back(individuos[idx]);
        }
    }
    
    individuos = std::move(novaGeracao);
    geracao++;
}

void Populacao::avaliarPopulacao(std::function<float(Rede&)> funcaoAvaliacao) {
    for (auto& individuo : individuos) {
        float aptidao = funcaoAvaliacao(individuo);
        individuo.definirAptidao(aptidao);
    }
}

// ... resto da implementação igual ao arquivo original Populacao.cpp ...

} // namespace NEAT 