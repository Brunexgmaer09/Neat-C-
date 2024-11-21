#include "../include/Populacao.h"
#include <algorithm>
#include <iostream>
#include <random>

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

Rede* Populacao::selecaoTorneio(int tamanhoTorneio) {
    float melhorAptidao = -1.0f;
    Rede* melhorRede = nullptr;
    
    for (int i = 0; i < tamanhoTorneio; i++) {
        int idx = rand() % individuos.size();
        float aptidao = individuos[idx].obterAptidao();
        if (aptidao > melhorAptidao) {
            melhorAptidao = aptidao;
            melhorRede = &individuos[idx];
        }
    }
    
    return melhorRede;
}

Rede Populacao::cruzarRedes(const Rede& rede1, const Rede& rede2) {
    // Criar uma nova rede com a mesma estrutura básica
    Rede filho(0, 0); // Os números serão ignorados pois vamos copiar a estrutura
    
    // Copiar nós usando os novos métodos
    filho.definirNos(rede1.obterNos());
    
    // Cruzar conexões
    const auto& conexoes1 = rede1.obterConexoes();
    const auto& conexoes2 = rede2.obterConexoes();
    
    std::vector<Conexao> novasConexoes;
    for (size_t i = 0; i < conexoes1.size(); i++) {
        if (rand() % 2 == 0) {
            novasConexoes.push_back(conexoes1[i]);
        } else {
            novasConexoes.push_back(conexoes2[i]);
        }
    }
    
    filho.definirConexoes(novasConexoes);
    return filho;
}

void Populacao::selecao() {
    // Ordenar indivíduos por aptidão
    std::sort(individuos.begin(), individuos.end(),
        [](const Rede& a, const Rede& b) {
            return a.obterAptidao() > b.obterAptidao();
        });
}

void Populacao::cruzamento() {
    std::vector<Rede> novaGeracao;
    
    // Preservar os melhores (elitismo)
    int numElite = static_cast<int>(config.tamanhoPopulacao * config.taxaElitismo);
    for (int i = 0; i < numElite; i++) {
        novaGeracao.push_back(individuos[i]);
    }
    
    // Preencher o resto com cruzamentos
    while (novaGeracao.size() < config.tamanhoPopulacao) {
        Rede* pai1 = selecaoTorneio(config.tamanhoTorneio);
        Rede* pai2 = selecaoTorneio(config.tamanhoTorneio);
        if (pai1 && pai2) {
            Rede filho = cruzarRedes(*pai1, *pai2);
            if ((float)rand() / RAND_MAX < config.taxaMutacao) {
                filho.mutar();
            }
            novaGeracao.push_back(filho);
        }
    }
    
    individuos = std::move(novaGeracao);
}

void Populacao::mutacao() {
    for (auto& individuo : individuos) {
        if ((float)rand() / RAND_MAX < config.taxaMutacao) {
            individuo.mutar();
        }
    }
}

void Populacao::especiar() {
    especies.clear();
    
    for (auto& individuo : individuos) {
        bool encontrouEspecie = false;
        
        for (auto& especie : especies) {
            if (especie.verificarCompatibilidade(individuo)) {
                especie.adicionarMembro(&individuo);
                encontrouEspecie = true;
                break;
            }
        }
        
        if (!encontrouEspecie && especies.size() < config.maxEspecies) {
            especies.emplace_back(individuo);
        }
    }
}

void Populacao::ajustarAptidoes() {
    for (auto& especie : especies) {
        especie.calcularAptidaoAjustada();
    }
}

void Populacao::eliminarEspeciesFracas() {
    especies.erase(
        std::remove_if(especies.begin(), especies.end(),
            [this](const Especie& especie) {
                return especie.obterAptidaoAjustada() < melhorAptidao * 0.2f;
            }),
        especies.end()
    );
}

void Populacao::salvarMelhorRede(const std::string& arquivo) {
    if (individuos.empty()) return;
    
    // Encontrar a melhor rede
    auto melhor = std::max_element(individuos.begin(), individuos.end(),
        [](const Rede& a, const Rede& b) {
            return a.obterAptidao() < b.obterAptidao();
        });
        
    melhor->salvar(arquivo);
}

void Populacao::carregarMelhorRede(const std::string& arquivo) {
    if (individuos.empty()) {
        individuos.emplace_back(0, 0);
    }
    individuos[0].carregar(arquivo);
}

} // namespace NEAT 