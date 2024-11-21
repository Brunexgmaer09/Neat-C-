# 🧠 NEAT (NeuroEvolution of Augmenting Topologies)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++: 11](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/wiki/faq/cpp11)
[![SDL2](https://img.shields.io/badge/SDL-2.0-orange.svg)](https://www.libsdl.org/)

Uma implementação robusta e eficiente do algoritmo NEAT em C++, permitindo a evolução automática de redes neurais através de neuroevolução.

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

O NEAT (NeuroEvolution of Augmenting Topologies) é um algoritmo genético que cria e evolui redes neurais artificiais. Esta implementação oferece uma solução completa e modular para problemas de aprendizado por reforço e otimização.

### Principais Diferenciais:
- **Evolução Incremental**: Começa com redes simples e aumenta a complexidade gradualmente
- **Especiação**: Protege inovações através de nichos evolutivos
- **Visualização em Tempo Real**: Acompanhe a evolução da rede visualmente

## ✨ Características

- **Evolução Automática** da topologia da rede
- **Sistema de Espécies** para preservar inovações
- **Crescimento Gradual** da complexidade
- **Visualização em Tempo Real** (usando SDL2)
- **Salvamento/Carregamento** de redes
- **Interface Intuitiva**
- **Alta Configurabilidade**

## 📥 Instalação

1. **Clone o repositório:**
```bash
git clone https://github.com/seu-usuario/rede-neural-neat.git
cd rede-neural-neat
```

2. **Dependências:**
- C++11 ou superior
- SDL2 (opcional, para visualização)
- Compilador compatível (g++, clang++, MSVC)

3. **Compilação:**
```bash
make
```

## 💻 Como Usar

1. **Inclua os headers necessários:**
```cpp
#include "RedeNeural/include/Rede.h"
#include "RedeNeural/include/Populacao.h"
#include "RedeNeural/include/Visualizador.h"
```

2. **Configure sua população:**
```cpp
NEAT::Populacao::Configuracao config;
config.tamanhoPopulacao = 150;
config.taxaMutacao = 0.3f;
config.taxaCruzamento = 0.75f;
config.taxaElitismo = 0.1f;
```

3. **Crie e evolua a população:**
```cpp
NEAT::Populacao populacao(numEntradas, numSaidas, config);

// Loop de evolução
for (int geracao = 0; geracao < numGeracoes; geracao++) {
    populacao.avaliarPopulacao(avaliarRede);
    populacao.evoluir();
}
```

## 📚 Exemplos

### Problema XOR
```cpp
#include "RedeNeural/include/Populacao.h"
#include <iostream>

// Dados de treinamento XOR
const std::vector<std::vector<float>> ENTRADAS = {
    {0, 0}, {0, 1}, {1, 0}, {1, 1}
};
const std::vector<float> SAIDAS_ESPERADAS = {0, 1, 1, 0};

// Função de avaliação
float avaliarRede(NEAT::Rede& rede) {
    float pontuacao = 0;
    
    for (size_t i = 0; i < ENTRADAS.size(); i++) {
        rede.definirEntradas(ENTRADAS[i]);
        rede.avaliar();
        float saida = rede.obterSaidas()[0];
        pontuacao += 1 - std::abs(saida - SAIDAS_ESPERADAS[i]);
    }
    
    return pontuacao;
}

int main() {
    NEAT::Populacao populacao(2, 1);  // 2 entradas, 1 saída
    
    // Evoluir por 100 gerações
    for (int i = 0; i < 100; i++) {
        populacao.avaliarPopulacao(avaliarRede);
        populacao.evoluir();
    }
    
    return 0;
}
```

## 📖 Documentação

### Estrutura do Projeto
```
RedeNeural/
├── include/          # Headers
│   ├── Rede.h       # Classe principal da rede neural
│   ├── Populacao.h  # Gerenciamento da população
│   ├── Especie.h    # Sistema de espécies
│   └── ...
├── src/             # Implementações
├── docs/            # Documentação
└── examples/        # Exemplos de uso
```

### Classes Principais

- **Rede**: Implementa a rede neural
- **Populacao**: Gerencia a evolução
- **Especie**: Implementa o sistema de espécies
- **Visualizador**: Renderiza a rede graficamente

## 🤝 Contribuindo

1. Faça um Fork do projeto
2. Crie sua Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. Push para a Branch (`git push origin feature/AmazingFeature`)
5. Abra um Pull Request

## 📝 Licença

Este projeto está sob a licença MIT - veja o arquivo [LICENSE.md](LICENSE.md) para detalhes

## ✨ Agradecimentos

- Kenneth O. Stanley - Criador do algoritmo NEAT
- Contribuidores do projeto
- Comunidade Open Source

---
⭐️ **From [BrunexCoder](https://github.com/seu-usuario)**
