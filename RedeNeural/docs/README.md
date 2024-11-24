# 🧠 NEAT (NeuroEvolution of Augmenting Topologies)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++: 17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/wiki/faq/cpp17)
[![SDL2](https://img.shields.io/badge/SDL-2.0-orange.svg)](https://www.libsdl.org/)

Uma implementação robusta e eficiente do algoritmo NEAT em C++, com foco em segurança, performance e facilidade de uso.

## 📋 Índice

- [Sobre](#-sobre)
- [Características](#-características)
- [Instalação](#-instalação)
- [Como Usar](#-como-usar)
- [Exemplos](#-exemplos)
- [Documentação](#-documentação)
- [Contribuindo](#-contribuindo)
- [Licença](#-licença)

## 🎯 Sobre

O NEAT é um algoritmo genético que cria e evolui redes neurais artificiais. Esta implementação oferece:

### Principais Diferenciais:
- **Sistema de Cache**: Otimização de performance com cache de avaliações
- **Validação Robusta**: Sistema completo de validação de redes e conexões
- **Logging Detalhado**: Sistema de logs para debug e monitoramento
- **Métricas e Análises**: Coleta e análise de dados de evolução
- **Visualização em Tempo Real**: Interface gráfica com SDL2
- **Persistência Flexível**: Salvamento/carregamento em múltiplos formatos

## ✨ Características

### Novas Funcionalidades:
- **Sistema de Cache**
  - Cache de avaliações para melhor performance
  - Invalidação automática quando necessário

- **Validação e Segurança**
  - Verificação de limites e restrições
  - Validação de estrutura da rede
  - Prevenção de ciclos e conexões inválidas

- **Sistema de Logging**
  - Múltiplos níveis de log (DEBUG, INFO, WARN, ERROR)
  - Registro de timestamp e contexto
  - Rotação automática de logs

- **Métricas e Análises**
  - Coleta de dados por geração
  - Análise de diversidade
  - Exportação para CSV
  - Geração de gráficos

### Configurações Avançadas:
```cpp
struct ConfiguracaoNEAT {
    // Parâmetros de compatibilidade
    static float COEF_EXCESSO;      // Coeficiente para genes em excesso
    static float COEF_DISJUNTO;     // Coeficiente para genes disjuntos
    static float COEF_PESO;         // Coeficiente para diferença de pesos
    
    // Parâmetros de mutação
    static float CHANCE_PESO_PERTURBADO;  // Chance de perturbar pesos
    static float CHANCE_CONEXAO_TOGGLE;   // Chance de alternar conexões
    static float CHANCE_NOVO_NO;          // Chance de adicionar nós
    static float CHANCE_NOVA_CONEXAO;     // Chance de novas conexões
    
    // Limites de segurança
    static int MAX_NOS;             // Máximo de nós permitidos
    static int MAX_CONEXOES;        // Máximo de conexões permitidas
};
```

## 💻 Como Usar

### Exemplo Básico:
```cpp
#include "RedeNeural/include/Rede.hpp"
#include "RedeNeural/include/Populacao.hpp"
#include "RedeNeural/include/Logger.hpp"

int main() {
    // Inicializar logger
    NEAT::Logger::inicializar("neat.log");
    
    // Configurar população
    NEAT::Populacao::Configuracao config;
    config.tamanhoPopulacao = 150;
    config.taxaMutacao = 0.3f;
    
    // Criar e evoluir população
    NEAT::Populacao populacao(2, 1, config);  // 2 entradas, 1 saída
    
    for (int geracao = 0; geracao < 100; geracao++) {
        populacao.avaliarPopulacao([](NEAT::Rede& rede) {
            // Sua função de avaliação aqui
            return 0.0f;
        });
        populacao.evoluir();
    }
    
    // Salvar melhor rede
    populacao.salvarMelhorRede("melhor_rede.neat");
    
    NEAT::Logger::finalizar();
    return 0;
}
```

## 📚 Documentação

### Estrutura do Projeto
```
RedeNeural/
├── include/
│   ├── Rede.hpp           # Classe principal da rede neural
│   ├── Populacao.hpp      # Gerenciamento da população
│   ├── Validador.hpp      # Sistema de validação
│   ├── Logger.hpp         # Sistema de logging
│   ├── Metricas.hpp       # Coleta de métricas
│   └── Configuracao.hpp   # Configurações globais
├── src/
│   └── ...               # Implementações
└── docs/
    └── README.md         # Esta documentação
```

## 🤝 Contribuindo

1. Faça um Fork do projeto
2. Crie sua Feature Branch (`git checkout -b feature/MinhaFeature`)
3. Commit suas mudanças (`git commit -m 'Adiciona MinhaFeature'`)
4. Push para a Branch (`git push origin feature/MinhaFeature`)
5. Abra um Pull Request

## 📝 Licença

Este projeto está sob a licença MIT - veja o arquivo [LICENSE.md](LICENSE.md) para detalhes

---
⭐️ **From [BrunexCoder](https://github.com/seu-usuario)**
