# Biblioteca NEAT (NeuroEvolution of Augmenting Topologies)

**NEAT** é uma implementação robusta e eficiente do algoritmo NEAT em C++, permitindo a evolução de redes neurais através de neuroevolução.

## 🧠 Sobre o Projeto

Esta biblioteca implementa o **algoritmo NEAT**, que permite a evolução automática de redes neurais. O sistema começa com redes simples e aumenta gradualmente sua complexidade através de mutações e evolução natural.

## ✨ Características Principais

- **Evolução automática da topologia da rede**
- **Sistema de espécies para preservar inovações**
- **Crescimento gradual da complexidade**
- **Visualização em tempo real** (usando SDL2)
- **Salvamento e carregamento de redes**
- **Interface simples e intuitiva**
- **Totalmente configurável**

## 🚀 Começando

### Pré-requisitos

- **C++11** ou superior
- **SDL2** (opcional, para visualização)
- **Compilador compatível**: g++, clang++, MSVC

### 📥 Instalação

1. **Clone o repositório:**

    ```bash
    git clone https://github.com/seu-usuario/rede-neural-neat.git
    ```

2. **Inclua os arquivos em seu projeto:**

    ```cpp
    #include "RedeNeural/include/Rede.h"
    #include "RedeNeural/include/Populacao.h"
    #include "RedeNeural/include/Visualizador.h"
    ```

## 💻 Exemplo de Uso

```cpp
#include "RedeNeural/include/Populacao.h"

// Configurar população
Populacao::Configuracao config;
config.tamanhoPopulacao = 150;
config.taxaMutacao = 0.3f;

// Criar população
Populacao populacao(2, 1, config);

// Evoluir
populacao.avaliarPopulacao(avaliarRede);
populacao.evoluir();
```

## ⚙️ Configuração

### Parâmetros Principais

```cpp
Populacao::Configuracao config;
config.tamanhoPopulacao = 150; // Tamanho da população
config.taxaMutacao = 0.3f; // Chance de mutação
config.taxaCruzamento = 0.75f; // Chance de cruzamento
config.taxaElitismo = 0.1f; // Percentual de elite
```

## 📁 Estrutura do Projeto

```
RedeNeural/
├── include/
│   ├── Rede.h
│   ├── Populacao.h
│   ├── Especie.h
│   ├── Configuracao.h
│   └── Visualizador.h
├── src/
└── docs/
```

## 🤝 Contribuindo

1. **Faça um Fork do projeto**
2. **Crie sua Feature Branch:**

    ```bash
    git checkout -b feature/NovaFeature
    ```

3. **Commit suas mudanças:**

    ```bash
    git commit -m 'Adiciona nova feature'
    ```

4. **Push para a Branch:**

    ```bash
    git push origin feature/NovaFeature
    ```

5. **Abra um Pull Request**

## 📝 Licença

Este projeto está sob a licença **MIT**. Veja o arquivo LICENSE para mais detalhes.

**Link do Projeto:** [https://github.com/seu-usuario/rede-neural-neat](https://github.com/seu-usuario/rede-neural-neat)

⭐️ **From BrunexCoder**
