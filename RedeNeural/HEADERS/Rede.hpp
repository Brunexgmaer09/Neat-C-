#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Configuracao.hpp"

namespace NEAT {

struct Conexao {
    int deNo;
    int paraNo;
    float peso;
    bool ativo;
    int inovacao;
};

struct No {
    int id;
    int camada;  // 0=entrada, 1=oculta, 2=saida
    float valor;
};

class Rede {
private:
    static int proximaInovacao;
    float aptidao;
    int proximoIdNo;
    std::vector<No> nos;
    std::vector<Conexao> conexoes;
    std::vector<float> entradas;
    std::vector<float> saidas;
    mutable bool cacheValido;
    mutable std::vector<float> cacheSaidas;

public:
    static float sigmoid(float x);

    Rede(int numEntradas = 5, int numSaidas = 1);
    
    // Métodos principais
    void definirEntradas(const std::vector<float>& novasEntradas);
    void avaliar() const;
    void mutar();
    void limpar();
    
    // Métodos de modificação da rede
    void adicionarNo(int camada);
    void adicionarConexao(int deNo, int paraNo, float peso);
    void mutarPesos();
    void adicionarNoAleatorio();
    void adicionarConexaoAleatoria();
    void removerNoAleatorio();
    void removerConexaoAleatoria();
    void reativarConexaoAleatoria();
    
    // Getters e Setters
    const std::vector<No>& obterNos() const { return nos; }
    void definirNos(const std::vector<No>& novosNos) { nos = novosNos; }
    const std::vector<Conexao>& obterConexoes() const { return conexoes; }
    void definirConexoes(const std::vector<Conexao>& novasConexoes) { conexoes = novasConexoes; }
    const std::vector<float>& obterSaidas() const { return saidas; }
    float obterAptidao() const { return aptidao; }
    void definirAptidao(float f) { aptidao = f; }
    static int obterProximaInovacao() { return proximaInovacao; }
    int obterProximoIdNo() const { return proximoIdNo; }
    
    void verificarLimitesRede() {
        if (nos.size() > ConfiguracaoNEAT::MAX_NOS) {
            throw std::runtime_error("Limite máximo de nós excedido");
        }
        if (conexoes.size() > ConfiguracaoNEAT::MAX_CONEXOES) {
            throw std::runtime_error("Limite máximo de conexões excedido");
        }
    }
    
    // Serialização
    void salvar(const std::string& arquivo);
    void carregar(const std::string& arquivo);
    void invalidarCache() { cacheValido = false; }
};

} // namespace NEAT 
