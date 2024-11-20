# NEAT (NeuroEvolution of Augmenting Topologies)

Uma implementação em C++ do algoritmo **NEAT** para evolução de redes neurais. Esta biblioteca permite que redes neurais evoluam tanto sua **topologia** quanto seus **pesos**, começando com estruturas simples e tornando-se progressivamente mais complexas.

## 🚀 Características

- **Implementação NEAT completa e modular**
- **Evolução automática da topologia da rede**
- **Visualização em tempo real** usando **SDL2** (opcional)
- **Sistema de espécies e elitismo**
- **Suporte a salvamento/carregamento de redes**
- **Namespace próprio** para evitar conflitos
- **Callbacks** para monitoramento da evolução

---

## 🛠️ Como Usar

### Requisitos

- **C++11** ou superior
- **SDL2** (opcional, apenas para visualização)
- Compilador com suporte a **C++11** (g++, clang++, MSVC)

### Instalação

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/neat-implementation.git
   ```

2. Inclua os arquivos no seu projeto:
   ```cpp
   #include "NEAT/include/Rede.h"
   #include "NEAT/include/Populacao.h"
   #include "NEAT/include/Visualizador.h"
   ```

---

## 📄 Exemplo Básico de Uso

```cpp
#include "NEAT/include/Populacao.h"
using namespace NEAT;

int main() {
    // Configurar a população
    Populacao::Configuracao config;
    config.tamanhoPopulacao = 50;
    config.taxaMutacao = 0.3f;
    config.taxaCruzamento = 0.8f;
    config.taxaElitismo = 0.1f;

    // Criar população (5 entradas, 1 saída)
    Populacao populacao(5, 1, config);

    // Definir callback para acompanhar evolução
    populacao.definirCallbackGeracao([](int geracao, float melhor, float media, float pior) {
        std::cout << "Geracao " << geracao << ": " << melhor << std::endl;
    });

    // Loop principal de evolução
    for (int geracao = 0; geracao < 100; geracao++) {
        // Avaliar cada rede na população
        populacao.avaliarPopulacao([](Rede& rede) {
            // Seu código de avaliação aqui
            return pontuacao; // Defina a pontuação da rede aqui
        });

        // Evoluir para próxima geração
        populacao.evoluir();
    }
}
```

---

## 📚 Guia Detalhado

### Configuração da População

```cpp
Populacao::Configuracao config;
config.tamanhoPopulacao = 50;     // Número de indivíduos
config.taxaMutacao = 0.3f;        // Chance de mutação (0-1)
config.taxaCruzamento = 0.8f;     // Chance de cruzamento (0-1)
config.taxaElitismo = 0.1f;       // Percentual de elite preservada
config.tamanhoTorneio = 3;        // Tamanho do torneio na seleção
```

### Avaliação de Redes

```cpp
float avaliarRede(Rede& rede) {
    // Definir entradas
    std::vector<float> entradas = {0.5f, 0.3f, 0.8f, 0.2f, 0.1f};
    rede.definirEntradas(entradas);

    // Processar rede
    rede.avaliar();

    // Obter saídas
    const auto& saidas = rede.obterSaidas();

    // Calcular pontuação baseada no desempenho
    float pontuacao = /* seu cálculo aqui */;
    return pontuacao;
}
```

### Visualização (com SDL2)

```cpp
Visualizador::Configuracao visConfig;
visConfig.largura = 200;
visConfig.altura = 300;
visConfig.raioNo = 5;
visConfig.mostrarPesos = true;
visConfig.corFundo = {0, 0, 0, 128};
visConfig.corEntrada = {255, 0, 0, 255};
visConfig.corOculta = {0, 255, 0, 255};
visConfig.corSaida = {0, 0, 255, 255};

Visualizador visualizador(renderer, {600, 10, 180, 200}, visConfig);
visualizador.renderizar(rede);
```

### Salvamento/Carregamento

Salvar a melhor rede:
```cpp
populacao.salvarMelhorRede("melhor_rede.bin");
```

Carregar uma rede:
```cpp
Rede rede(5, 1);
rede.carregar("melhor_rede.bin");
```

---

## 💡 Dicas de Uso

### Ajuste de Parâmetros

- Comece com populações pequenas (`50-100`)
- Use taxas de mutação moderadas (`0.2-0.4`)
- Ajuste o elitismo baseado no problema

### Função de Avaliação

- Deve refletir claramente o objetivo
- Considere múltiplos aspectos do desempenho
- Evite platôs na função de fitness

### Otimização

- Use **threads** para avaliação paralela
- Implemente **cache de inovações**
- Monitore a **diversidade da população**

---

## 📜 Licença

Este projeto é licenciado sob a **MIT License**. Veja o arquivo [LICENSE.md](LICENSE.md) para mais detalhes.

---

## 🤝 Contribuindo

Contribuições são sempre bem-vindas! Siga os passos abaixo:

1. Faça um **fork** do projeto.
2. Crie uma branch para sua feature:
   ```bash
   git checkout -b feature/AmazingFeature
   ```
3. Commit suas mudanças:
   ```bash
   git commit -m 'Add some AmazingFeature'
   ```
4. Faça o push para a branch:
   ```bash
   git push origin feature/AmazingFeature
   ```
5. Abra um **Pull Request**.

---

### 📫 Contato

Se tiver dúvidas ou sugestões, entre em contato por meio de um **Pull Request** ou abra uma **Issue** no repositório.

---

**Happy Coding!** 🎉
