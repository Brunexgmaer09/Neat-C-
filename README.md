Biblioteca NEAT (NeuroEvolution of Augmenting Topologies)
Uma implementação robusta e eficiente do algoritmo NEAT em C++, permitindo a evolução de redes neurais através de neuroevolução.

🧠 Sobre o Projeto
Esta biblioteca implementa o algoritmo NEAT, que permite a evolução automática de redes neurais. O sistema começa com redes simples e aumenta gradualmente sua complexidade através de mutações e evolução natural.

✨ Características Principais
Evolução automática da topologia da rede
Sistema de espécies para preservar inovações
Crescimento gradual da complexidade
Visualização em tempo real (usando SDL2)
Salvamento e carregamento de redes
Interface simples e intuitiva
Totalmente configurável
🚀 Começando
Pré-requisitos
C++11 ou superior
SDL2 (opcional, para visualização)
Compilador compatível (g++, clang++, MSVC)
📥 Instalação
Clone o repositório:

git clone https://github.com/seu-usuario/rede-neural-neat.git
Inclua os arquivos em seu projeto:

#include "RedeNeural/include/Rede.h"
#include "RedeNeural/include/Populacao.h"
#include "RedeNeural/include/Visualizador.h"
💻 Exemplo de Uso

#include "RedeNeural/include/Populacao.h"
#include <iostream>

// Configurar população
Populacao::Configuracao config;
config.tamanhoPopulacao = 150;
config.taxaMutacao = 0.3f;

// Criar população
Populacao populacao(2, 1, config);

// Evoluir
populacao.avaliarPopulacao(avaliarRede);
populacao.evoluir();
⚙️ Configuração
Parâmetros Principais

Populacao::Configuracao config;
config.tamanhoPopulacao = 150;    // Tamanho da população
config.taxaMutacao = 0.3f;        // Chance de mutação
config.taxaCruzamento = 0.75f;    // Chance de cruzamento
config.taxaElitismo = 0.1f;       // Percentual de elite
📁 Estrutura do Projeto

RedeNeural/
├── include/
│   ├── Rede.h
│   ├── Populacao.h
│   ├── Especie.h
│   ├── Configuracao.h
│   └── Visualizador.h
├── src/
└── docs/
🤝 Contribuindo
Faça um Fork do projeto
Crie sua Feature Branch (git checkout -b feature/NovaFeature)
Commit suas mudanças (git commit -m 'Adiciona nova feature')
Push para a Branch (git push origin feature/NovaFeature)
Abra um Pull Request
📝 Licença
Este projeto está sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.

Link do Projeto: [https://github.com/seu-usuario/rede-neural-neat](https://github.com/Brunexgmaer09/Neat-C-/edit/main/README.md)

⭐️ From BrunexCoder
