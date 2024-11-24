#pragma once
#include <vector>
#include <string>

namespace NEAT {

class Metricas {
private:
    struct DadosGeracao {
        float melhorAptidao;
        float aptidaoMedia;
        int numEspecies;
        int numConexoes;
        float taxaMutacao;
    };
    
    std::vector<DadosGeracao> historico;
    
public:
    void registrarGeracao(float melhorAptidao, float aptidaoMedia, 
                         int numEspecies, int numConexoes, float taxaMutacao) {
        historico.push_back({melhorAptidao, aptidaoMedia, 
                           numEspecies, numConexoes, taxaMutacao});
    }
    
    void exportarCSV(const std::string& arquivo) const;
    void gerarGraficos() const;  // Requer biblioteca de plotagem
    void analisarTendencias() const;
};

} // namespace NEAT 