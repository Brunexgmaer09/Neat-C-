#include "../include/Populacao.hpp"
#include "../include/Validador.hpp"
#include "../include/Logger.hpp"
#include "../include/Especie.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <iomanip>
#include <map>
#include <set>

namespace NEAT {

Populacao::Populacao(int numEntradas, int numSaidas, const Configuracao& config)
    : config(config), geracao(0), melhorAptidao(0) {
    
    std::cout << "\n[NEAT] Inicializando população com:" 
              << "\n - Tamanho: " << config.tamanhoPopulacao
              << "\n - Entradas: " << numEntradas
              << "\n - Saídas: " << numSaidas << std::endl;
    
    // Criar população inicial
    for (int i = 0; i < config.tamanhoPopulacao; i++) {
        individuos.emplace_back(numEntradas, numSaidas);
    }
}

void Populacao::evoluir() {
    std::cout << "\n[NEAT] Iniciando evolução da geração " << geracao << std::endl;
    
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
    
    // Log das estatísticas
    std::cout << std::fixed << std::setprecision(2)
              << "\n[NEAT] Estatísticas da geração " << geracao
              << "\n - Melhor Fitness: " << aptidaoMaxima
              << "\n - Fitness Médio: " << aptidaoMedia
              << "\n - Pior Fitness: " << aptidaoMinima << std::endl;
    
    // Nova geração
    std::vector<Rede> novaGeracao;
    
    // Elitismo
    int numElite = static_cast<int>(config.tamanhoPopulacao * config.taxaElitismo);
    std::cout << "\n[NEAT] Aplicando elitismo - Preservando " << numElite << " indivíduos" << std::endl;
    
    for (int i = 0; i < numElite; i++) {
        novaGeracao.push_back(individuos[i]);
        std::cout << " - Elite #" << i + 1 << " Fitness: " << individuos[i].obterAptidao() << std::endl;
    }
    
    // Contadores para logs
    int numCruzamentos = 0;
    int numMutacoes = 0;
    int numCopias = 0;
    
    // Criar resto da população
    while (novaGeracao.size() < config.tamanhoPopulacao) {
        if ((float)rand() / RAND_MAX < config.taxaCruzamento) {
            Rede* pai1 = selecaoTorneio(config.tamanhoTorneio);
            Rede* pai2 = selecaoTorneio(config.tamanhoTorneio);
            
            // Realizar cruzamento
            cruzamento();
            
            // Realizar mutação
            mutacao();
            
            // Validar nova população
            for (const auto& individuo : individuos) {
                if (!Validador::validarRede(individuo)) {
                    throw std::runtime_error("Nova população inválida");
                }
            }
            
            // Atualizar geração
            geracao++;
            
            Logger::log(Logger::Nivel::INFO, 
                "Evolução concluída com sucesso - Geração " + std::to_string(geracao));
        }
        catch (const std::exception& e) {
            // Restaurar backup em caso de erro
            Logger::log(Logger::Nivel::ERROR, 
                "Erro durante evolução: " + std::string(e.what()));
            individuos = backupPopulacao;
            throw;
        }
    }
    catch (const std::exception& e) {
        Logger::log(Logger::Nivel::ERROR, 
            "Erro fatal durante evolução: " + std::string(e.what()));
        throw;
    }
}

void Populacao::analisarDiversidade(const std::vector<Rede>& populacao) {
    // Contagem de estruturas únicas
    std::map<size_t, int> estruturas;
    
    for (const auto& individuo : populacao) {
        size_t numConexoes = individuo.obterConexoes().size();
        size_t numNos = individuo.obterNos().size();
        size_t hash = numConexoes * 1000 + numNos; // Hash simples da estrutura
        estruturas[hash]++;
    }
    
    std::cout << "\n[NEAT] Análise de diversidade:"
              << "\n - Estruturas únicas: " << estruturas.size()
              << "\n - Distribuição:";
              
    for (const auto& [estrutura, quantidade] : estruturas) {
        size_t numNos = estrutura % 1000;
        size_t numConexoes = estrutura / 1000;
        std::cout << "\n   * " << quantidade << " indivíduos com "
                  << numNos << " nós e " << numConexoes << " conexões";
    }
    std::cout << std::endl;
}

void Populacao::especiar() {
    std::cout << "\n[NEAT] Iniciando especiação" << std::endl;
    
    especies.clear();
    int individuosSemEspecie = 0;
    
    for (auto& individuo : individuos) {
        bool encontrouEspecie = false;
        
        for (auto& especie : especies) {
            if (especie.verificarCompatibilidade(individuo)) {
                especie.adicionarMembro(&individuo);
                encontrouEspecie = true;
                break;
            }
        }
        
        if (!encontrouEspecie) {
            if (especies.size() < config.maxEspecies) {
                especies.emplace_back(individuo);
                std::cout << "[NEAT] Nova espécie criada - Total: " << especies.size() << std::endl;
            } else {
                individuosSemEspecie++;
            }
        }
    }
    
    std::cout << "[NEAT] Especiação concluída:"
              << "\n - Total de espécies: " << especies.size()
              << "\n - Indivíduos sem espécie: " << individuosSemEspecie << std::endl;
}

void Populacao::avaliarPopulacao(std::function<float(Rede&)> funcaoAvaliacao) {
    for (auto& individuo : individuos) {
        float aptidao = funcaoAvaliacao(individuo);
        individuo.definirAptidao(aptidao);
    }
}

Rede* Populacao::selecaoTorneio(int tamanhoTorneio) {
    std::vector<Rede*> candidatos;
    
    // Aumentar viés para melhores indivíduos
    for (int i = 0; i < tamanhoTorneio; i++) {
        if ((float)rand() / RAND_MAX < 0.8f) {  // Aumentado de 0.7f para 0.8f
            // Selecionar do top 33% ao invés de 50%
            int idx = rand() % (individuos.size() / 3);
            candidatos.push_back(&individuos[idx]);
        } else {
            int idx = rand() % individuos.size();
            candidatos.push_back(&individuos[idx]);
        }
    }
    
    // Encontrar o melhor candidato
    Rede* melhor = candidatos[0];
    float melhorFitness = melhor->obterAptidao();
    
    for (size_t i = 1; i < candidatos.size(); i++) {
        float fitness = candidatos[i]->obterAptidao();
        if (fitness > melhorFitness) {
            melhorFitness = fitness;
            melhor = candidatos[i];
        }
    }
    
    // Se o melhor candidato tem fitness muito baixo, tentar novamente
    if (melhorFitness < melhorAptidao * 0.1f && tamanhoTorneio < 5) {
        return selecaoTorneio(tamanhoTorneio + 1);
    }
    
    return melhor;
}

Rede Populacao::cruzarRedes(const Rede& rede1, const Rede& rede2) {
    // Validar redes antes do cruzamento
    if (!Validador::validarRede(rede1) || !Validador::validarRede(rede2)) {
        Logger::log(Logger::Nivel::ERROR, "Tentativa de cruzar redes inválidas");
        throw std::runtime_error("Redes inválidas para cruzamento");
    }

    // Criar filho
    Rede filho(0, 0);
    
    try {
        // Copiar nós
        std::vector<No> nosFilho;
        auto nosRede1 = rede1.obterNos();
        auto nosRede2 = rede2.obterNos();
        
        // Garantir que todos os nós necessários sejam copiados
        std::set<int> idsNos;
        for (const auto& no : nosRede1) idsNos.insert(no.id);
        for (const auto& no : nosRede2) idsNos.insert(no.id);
        
        for (int id : idsNos) {
            auto noRede1 = std::find_if(nosRede1.begin(), nosRede1.end(),
                [id](const No& no) { return no.id == id; });
                
            auto noRede2 = std::find_if(nosRede2.begin(), nosRede2.end(),
                [id](const No& no) { return no.id == id; });
                
            if (noRede1 != nosRede1.end()) {
                nosFilho.push_back(*noRede1);
            } else if (noRede2 != nosRede2.end()) {
                nosFilho.push_back(*noRede2);
            }
        }
        
        filho.definirNos(nosFilho);
        
        // Cruzar conexões com verificação de compatibilidade
        std::vector<Conexao> conexoesFilho;
        auto conexoesRede1 = rede1.obterConexoes();
        auto conexoesRede2 = rede2.obterConexoes();
        
        for (const auto& conexao : conexoesRede1) {
            if (conexao.ativo && rand() % 2 == 0) {
                // Verificar se os nós existem no filho
                if (std::find_if(nosFilho.begin(), nosFilho.end(),
                    [&](const No& no) { return no.id == conexao.deNo; }) != nosFilho.end() &&
                    std::find_if(nosFilho.begin(), nosFilho.end(),
                    [&](const No& no) { return no.id == conexao.paraNo; }) != nosFilho.end()) {
                    conexoesFilho.push_back(conexao);
                }
            }
        }
        
        for (const auto& conexao : conexoesRede2) {
            if (conexao.ativo && rand() % 2 == 0) {
                // Verificar se os nós existem no filho
                if (std::find_if(nosFilho.begin(), nosFilho.end(),
                    [&](const No& no) { return no.id == conexao.deNo; }) != nosFilho.end() &&
                    std::find_if(nosFilho.begin(), nosFilho.end(),
                    [&](const No& no) { return no.id == conexao.paraNo; }) != nosFilho.end()) {
                    conexoesFilho.push_back(conexao);
                }
            }
        }
        
        filho.definirConexoes(conexoesFilho);
        
        // Validar filho antes de retornar
        if (!Validador::validarRede(filho)) {
            throw std::runtime_error("Filho gerado é inválido");
        }
        
        return filho;
    }
    catch (const std::exception& e) {
        Logger::log(Logger::Nivel::ERROR, 
            "Erro durante cruzamento: " + std::string(e.what()));
        throw;
    }
}

void Populacao::selecao() {
    // Ordenar por fitness
    std::sort(individuos.begin(), individuos.end(),
        [](const Rede& a, const Rede& b) {
            return a.obterAptidao() > b.obterAptidao();
        });

    // Calcular soma total de fitness
    float somaFitness = 0.0f;
    for (const auto& individuo : individuos) {
        somaFitness += std::max(0.1f, individuo.obterAptidao()); // Evita fitness 0
    }

    // Calcular probabilidades de seleção
    std::vector<float> probabilidades;
    for (const auto& individuo : individuos) {
        float prob = std::max(0.1f, individuo.obterAptidao()) / somaFitness;
        probabilidades.push_back(prob);
    }
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
        // Aumentar chance de mutação para indivíduos ruins
        float chanceMutacao = config.taxaMutacao;
        if (individuo.obterAptidao() < melhorAptidao * 0.5f) {
            chanceMutacao *= 2.0f;
        }
        
        if ((float)rand() / RAND_MAX < chanceMutacao) {
            // Adicionar diferentes tipos de mutação
            switch(rand() % 3) {
                case 0:
                    individuo.mutarPesos();
                    break;
                case 1:
                    individuo.adicionarNoAleatorio();
                    break;
                case 2:
                    individuo.adicionarConexaoAleatoria();
                    break;
            }
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