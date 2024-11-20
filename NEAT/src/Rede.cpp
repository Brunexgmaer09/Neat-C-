#include "../include/Rede.h"
#include <cmath>
#include <fstream>
#include <iostream>

namespace NEAT {

int Rede::proximaInovacao = 0;

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

void Rede::avaliar() {
    limpar();
    
    // Definir valores dos nós de entrada
    for (size_t i = 0; i < entradas.size(); i++) {
        nos[i].valor = entradas[i];
    }
    
    // Propagar valores pela rede
    for (const auto& conexao : conexoes) {
        if (conexao.ativo) {
            nos[conexao.paraNo].valor += nos[conexao.deNo].valor * conexao.peso;
        }
    }
    
    // Coletar saídas e aplicar função de ativação
    saidas.clear();
    for (const auto& no : nos) {
        if (no.camada == 2) {
            saidas.push_back(sigmoid(no.valor));
        }
    }
}

// ... resto da implementação igual ao arquivo original Rede.cpp ...

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

} // namespace NEAT 