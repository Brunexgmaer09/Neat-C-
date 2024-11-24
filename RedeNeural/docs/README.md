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
- [Estrutura](#-estrutura)
- [Contribuindo](#-contribuindo)
- [Licença](#-licença)

## 🎯 Sobre

O NEAT é um algoritmo genético que cria e evolui redes neurais artificiais. Esta implementação oferece:

### Principais Diferenciais:
- **Sistema de Cache**: Otimização de performance com cache de avaliações
- **Validação Robusta**: Sistema completo de validação de redes e conexões
- **Tratamento de Erros**: Sistema especializado de exceções para NEAT
- **Logging Detalhado**: Sistema de logs para debug e monitoramento
- **Métricas e Análises**: Coleta e análise de dados de evolução
- **Visualização em Tempo Real**: Interface gráfica com SDL2
- **Persistência Flexível**: Salvamento/carregamento em múltiplos formatos

## 🔧 Instalação

### Pré-requisitos
- C++17 ou superior
- SDL2 (para visualização)
- CMake 3.10 ou superior

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

```cpp
#include "HEADERS/Rede.hpp"
#include "HEADERS/Populacao.hpp"
#include "HEADERS/Logger.hpp"

int main() {
    try {
        // Inicializar logger
        NEAT::Logger::inicializar("neat.log");
        
        // Configurar população
        NEAT::Populacao::Configuracao config;
        config.tamanhoPopulacao = 150;
        config.taxaMutacao = 0.3f;
        
        // Criar e evoluir população
        NEAT::Populacao populacao(2, 1, config);
        
        for (int geracao = 0; geracao < 100; geracao++) {
            populacao.avaliarPopulacao([](NEAT::Rede& rede) {
                // Sua função de avaliação aqui
                return 0.0f;
            });
            populacao.evoluir();
        }
        
        populacao.salvarMelhorRede("melhor_rede.neat");
        NEAT::Logger::finalizar();
    }
    catch (const NEAT::ErroNEAT& e) {
        std::cerr << "Erro NEAT: " << e.what() << std::endl;
    }
    return 0;
}
```

## 📁 Estrutura

```
RedeNeural/
├── HEADERS/                # Headers (.hpp)
│   ├── Configuracao.hpp   # Configurações globais
│   ├── ErrosNEAT.hpp      # Sistema de exceções
│   ├── Especie.hpp        # Gerenciamento de espécies
│   ├── GerenciadorInovacao.hpp
│   ├── Logger.hpp         # Sistema de logging
│   ├── Metricas.hpp       # Coleta de métricas
│   ├── Persistencia.hpp   # Salvamento/carregamento
│   ├── Populacao.hpp      # Gerenciamento populacional
│   ├── Rede.hpp          # Classe principal da rede
│   ├── Validador.hpp     # Sistema de validação
│   └── Visualizador.hpp  # Visualização SDL2
│
├── HPP/                   # Implementações (.cpp)
│   ├── Configuracao.cpp
│   ├── Especie.cpp
│   ├── Populacao.cpp
│   ├── Rede.cpp
│   └── Visualizador.cpp
│
├── docs/                  # Documentação
│   └── README.md
│
└── CMakeLists.txt        # Configuração do CMake
```

## ⚙️ Configurações

### Parâmetros da Rede
```cpp
struct ConfiguracaoNEAT {
    // Parâmetros de compatibilidade
    static float COEF_EXCESSO;      // Genes em excesso
    static float COEF_DISJUNTO;     // Genes disjuntos
    static float COEF_PESO;         // Diferença de pesos
    
    // Parâmetros de mutação
    static float CHANCE_PESO_PERTURBADO;
    static float CHANCE_CONEXAO_TOGGLE;
    static float CHANCE_NOVO_NO;
    static float CHANCE_NOVA_CONEXAO;
    
    // Limites de segurança
    struct Limites {
        static constexpr float MIN_PESO = -4.0f;
        static constexpr float MAX_PESO = 4.0f;
        static constexpr int MAX_CAMADAS = 10;
        static constexpr int MAX_NOS_POR_CAMADA = 50;
    };
};
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
