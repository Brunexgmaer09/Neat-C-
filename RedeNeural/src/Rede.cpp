#include "../Headers/Rede.h"
#include "../Headers/Configuracao.h"
#include <cmath>
#include <fstream>
#include <iostream>

namespace NEAT {

int Rede::proximaInovacao = 0;

float Rede::sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}

void Rede::limpar() {
    for (auto& no : nos) {
        no.valor = 0.0f;
    }
    saidas.clear();
}

void Rede::definirEntradas(const std::vector<float>& novasEntradas) {
    entradas = novasEntradas;
}

void Rede::adicionarNo(int camada) {
    No novoNo;
    novoNo.id = proximoIdNo++;
    novoNo.camada = camada;
    novoNo.valor = 0.0f;
    nos.push_back(novoNo);
}

void Rede::adicionarConexao(int deNo, int paraNo, float peso) {
    Conexao novaConexao;
    novaConexao.deNo = deNo;
    novaConexao.paraNo = paraNo;
    novaConexao.peso = peso;
    novaConexao.ativo = true;
    novaConexao.inovacao = proximaInovacao++;
    conexoes.push_back(novaConexao);
}

void Rede::mutar() {
    // Mutação de pesos
    if ((float)rand() / RAND_MAX < ConfiguracaoNEAT::CHANCE_PESO_PERTURBADO) {
        mutarPesos();
    }
    
    // Mutação estrutural - adicionar nó
    if ((float)rand() / RAND_MAX < ConfiguracaoNEAT::CHANCE_NOVO_NO && 
        nos.size() < ConfiguracaoNEAT::MAX_NOS) {
        adicionarNoAleatorio();
    }
    
    // Mutação estrutural - remover nó
    if ((float)rand() / RAND_MAX < 0.05f && nos.size() > 16) { // 16 é o mínimo (entrada + saída)
        removerNoAleatorio();
    }
    
    // Mutação estrutural - adicionar conexão
    if ((float)rand() / RAND_MAX < ConfiguracaoNEAT::CHANCE_NOVA_CONEXAO && 
        conexoes.size() < ConfiguracaoNEAT::MAX_CONEXOES) {
        adicionarConexaoAleatoria();
    }
    
    // Mutação estrutural - remover conexão
    if ((float)rand() / RAND_MAX < 0.1f && conexoes.size() > 30) { // 30 é o mínimo de conexões
        removerConexaoAleatoria();
    }
    
    // Mutação estrutural - reativar conexão
    if ((float)rand() / RAND_MAX < ConfiguracaoNEAT::CHANCE_CONEXAO_TOGGLE) {
        reativarConexaoAleatoria();
    }
    
    // Log das mutações
    int conexoesAtivas = std::count_if(conexoes.begin(), conexoes.end(), 
        [](const Conexao& c) { return c.ativo; });
    
    std::cout << "[NEAT] Mutações aplicadas na rede:"
              << "\n - Nós: " << nos.size()
              << "\n - Conexões ativas: " << conexoesAtivas
              << "\n - Conexões totais: " << conexoes.size() << std::endl;
}

void Rede::mutarPesos() {
    const float CHANCE_PERTURBAR = 0.9f;  // 90% chance de perturbar, 10% de substituir
    const float FORCA_PERTURBACAO = 0.5f;  // Força máxima da perturbação
    
    for (auto& conexao : conexoes) {
        if ((float)rand() / RAND_MAX < CHANCE_PERTURBAR) {
            // Perturbar peso existente
            float perturbacao = ((float)rand() / RAND_MAX * 2.0f - 1.0f) * FORCA_PERTURBACAO;
            conexao.peso += perturbacao;
            
            // Limitar peso entre -4 e 4
            conexao.peso = std::max(-4.0f, std::min(4.0f, conexao.peso));
        } else {
            // Substituir peso completamente
            conexao.peso = (float)rand() / RAND_MAX * 8.0f - 4.0f;
        }
    }
    
    std::cout << "[NEAT] Mutação de pesos aplicada em " << conexoes.size() << " conexões" << std::endl;
}

void Rede::adicionarNoAleatorio() {
    if (conexoes.empty() || nos.size() >= ConfiguracaoNEAT::MAX_NOS) return;
    
    // Escolher uma conexão aleatória para dividir
    int idxConexao = rand() % conexoes.size();
    auto& conexao = conexoes[idxConexao];
    
    // Desativar a conexão original
    conexao.ativo = false;
    
    // Criar novo nó na camada oculta (1)
    No novoNo;
    novoNo.id = proximoIdNo++;
    novoNo.camada = 1;
    novoNo.valor = 0.0f;
    nos.push_back(novoNo);
    
    // Criar duas novas conexões
    // 1. Do nó de entrada para o novo nó
    adicionarConexao(conexao.deNo, novoNo.id, 1.0f);
    
    // 2. Do novo nó para o nó de saída
    adicionarConexao(novoNo.id, conexao.paraNo, conexao.peso);
    
    std::cout << "[NEAT] Novo nó adicionado (ID: " << novoNo.id 
              << ") dividindo conexão " << conexao.deNo 
              << " -> " << conexao.paraNo << std::endl;
}

void Rede::adicionarConexaoAleatoria() {
    if (nos.size() < 2 || conexoes.size() >= ConfiguracaoNEAT::MAX_CONEXOES) return;
    
    // Tentar várias vezes encontrar uma conexão válida
    for (int tentativas = 0; tentativas < 20; tentativas++) {
        // Escolher dois nós aleatórios
        int idxNo1 = rand() % nos.size();
        int idxNo2 = rand() % nos.size();
        
        No& no1 = nos[idxNo1];
        No& no2 = nos[idxNo2];
        
        // Verificar se a conexão seria válida:
        // 1. Não conectar nó com ele mesmo
        // 2. Não conectar nós da mesma camada
        // 3. Respeitar a direção do fluxo (camada menor para maior)
        if (idxNo1 != idxNo2 && 
            no1.camada != no2.camada && 
            no1.camada < no2.camada) {
            
            // Verificar se a conexão já existe
            bool conexaoExiste = false;
            for (const auto& conexao : conexoes) {
                if (conexao.deNo == no1.id && conexao.paraNo == no2.id) {
                    conexaoExiste = true;
                    break;
                }
            }
            
            if (!conexaoExiste) {
                // Criar nova conexão com peso aleatório
                float peso = (float)rand() / RAND_MAX * 8.0f - 4.0f;
                adicionarConexao(no1.id, no2.id, peso);
                
                std::cout << "[NEAT] Nova conexão adicionada: " 
                          << no1.id << " -> " << no2.id 
                          << " (peso: " << peso << ")" << std::endl;
                return;
            }
        }
    }
    
    std::cout << "[NEAT] Não foi possível adicionar nova conexão após 20 tentativas" << std::endl;
}

Rede::Rede(int numEntradas, int numSaidas) : aptidao(0), proximoIdNo(0) {
    // Adicionar nós de entrada
    for (int i = 0; i < numEntradas; i++) {
        adicionarNo(0);  // camada de entrada
    }
    
    // Adicionar nós de saída
    for (int i = 0; i < numSaidas; i++) {
        adicionarNo(2);  // camada de saída
    }
    
    // Criar conexões iniciais entre todas as entradas e saídas
    for (int i = 0; i < numEntradas; i++) {
        for (int j = 0; j < numSaidas; j++) {
            float peso = (float)(rand() % 2000 - 1000) / 1000.0f;
            adicionarConexao(i, numEntradas + j, peso);
        }
    }
}

void Rede::avaliar() const {
    // Como o método é const, precisamos usar mutable nos membros que serão modificados
    // ou fazer um cast para remover o const
    auto& naoConstNos = const_cast<std::vector<No>&>(nos);
    auto& naoConstSaidas = const_cast<std::vector<float>&>(saidas);
    
    // Limpar valores
    for (auto& no : naoConstNos) {
        no.valor = 0.0f;
    }
    naoConstSaidas.clear();
    
    // Definir valores dos nós de entrada
    for (size_t i = 0; i < entradas.size(); i++) {
        naoConstNos[i].valor = entradas[i];
    }
    
    // Propagar valores pela rede
    for (const auto& conexao : conexoes) {
        if (conexao.ativo) {
            naoConstNos[conexao.paraNo].valor += nos[conexao.deNo].valor * conexao.peso;
        }
    }
    
    // Coletar saídas e aplicar função de ativação
    for (const auto& no : nos) {
        if (no.camada == 2) {
            naoConstSaidas.push_back(sigmoid(no.valor));
        }
    }
}

void Rede::salvar(const std::string& arquivo) {
    std::ofstream out(arquivo, std::ios::binary);
    
    // Salvar nós
    size_t numNos = nos.size();
    out.write(reinterpret_cast<char*>(&numNos), sizeof(numNos));
    out.write(reinterpret_cast<char*>(nos.data()), numNos * sizeof(No));
    
    // Salvar conexões
    size_t numConexoes = conexoes.size();
    out.write(reinterpret_cast<char*>(&numConexoes), sizeof(numConexoes));
    out.write(reinterpret_cast<char*>(conexoes.data()), numConexoes * sizeof(Conexao));
}

void Rede::carregar(const std::string& arquivo) {
    std::ifstream in(arquivo, std::ios::binary);
    
    // Carregar nós
    size_t numNos;
    in.read(reinterpret_cast<char*>(&numNos), sizeof(numNos));
    nos.resize(numNos);
    in.read(reinterpret_cast<char*>(nos.data()), numNos * sizeof(No));
    
    // Carregar conexões
    size_t numConexoes;
    in.read(reinterpret_cast<char*>(&numConexoes), sizeof(numConexoes));
    conexoes.resize(numConexoes);
    in.read(reinterpret_cast<char*>(conexoes.data()), numConexoes * sizeof(Conexao));
}

void Rede::removerNoAleatorio() {
    // Não remover nós de entrada ou saída
    std::vector<int> nosOcultos;
    for (size_t i = 0; i < nos.size(); i++) {
        if (nos[i].camada == 1) { // Camada oculta
            nosOcultos.push_back(i);
        }
    }
    
    if (nosOcultos.empty()) return;
    
    // Escolher um nó oculto aleatório para remover
    int idxRemover = nosOcultos[rand() % nosOcultos.size()];
    int idNo = nos[idxRemover].id;
    
    // Remover conexões associadas
    conexoes.erase(
        std::remove_if(conexoes.begin(), conexoes.end(),
            [idNo](const Conexao& c) {
                return c.deNo == idNo || c.paraNo == idNo;
            }),
        conexoes.end()
    );
    
    // Remover o nó
    nos.erase(nos.begin() + idxRemover);
    
    std::cout << "[NEAT] Nó removido (ID: " << idNo << ")" << std::endl;
}

void Rede::removerConexaoAleatoria() {
    if (conexoes.empty()) return;
    
    // Escolher uma conexão aleatória
    int idx = rand() % conexoes.size();
    conexoes.erase(conexoes.begin() + idx);
    
    std::cout << "[NEAT] Conexão removida" << std::endl;
}

void Rede::reativarConexaoAleatoria() {
    // Encontrar conexões inativas
    std::vector<int> conexoesInativas;
    for (size_t i = 0; i < conexoes.size(); i++) {
        if (!conexoes[i].ativo) {
            conexoesInativas.push_back(i);
        }
    }
    
    if (conexoesInativas.empty()) return;
    
    // Reativar uma conexão aleatória
    int idx = conexoesInativas[rand() % conexoesInativas.size()];
    conexoes[idx].ativo = true;
    
    std::cout << "[NEAT] Conexão reativada: "
              << conexoes[idx].deNo << " -> " << conexoes[idx].paraNo << std::endl;
}

} // namespace NEAT 