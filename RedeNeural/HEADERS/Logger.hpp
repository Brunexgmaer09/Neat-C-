#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

namespace NEAT {

class Logger {
private:
    static std::ofstream logFile;
    static bool habilitado;
    
public:
    enum class Nivel {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };
    
    static void inicializar(const std::string& arquivo) {
        logFile.open(arquivo, std::ios::app);
        habilitado = true;
    }
    
    static void log(Nivel nivel, const std::string& mensagem) {
        if (!habilitado) return;
        
        auto agora = std::chrono::system_clock::now();
        auto tempo = std::chrono::system_clock::to_time_t(agora);
        
        std::string nivelStr;
        switch (nivel) {
            case Nivel::DEBUG: nivelStr = "DEBUG"; break;
            case Nivel::INFO:  nivelStr = "INFO"; break;
            case Nivel::WARN:  nivelStr = "WARN"; break;
            case Nivel::ERROR: nivelStr = "ERROR"; break;
        }
        
        logFile << std::ctime(&tempo) << " [" << nivelStr << "] " << mensagem << std::endl;
    }
    
    static void finalizar() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

} // namespace NEAT 