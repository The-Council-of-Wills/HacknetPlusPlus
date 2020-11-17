#pragma once
#include <map>
#include <string>
#include "Computer.hpp"

class GameManager {
    private:
        std::map<std::string, Computer*> computerNetwork;
    public:
        void addComputer(std::string name, std::string ip) {
            Computer* newComp = new Computer(name, ip);
            computerNetwork[ip] = newComp;
        }

        void addComputer(Computer* comp) {
            std::string ip = comp->getIP();
            computerNetwork[ip] = comp;
        }

        Computer* connect(std::string ip) {
            return computerNetwork[ip];
        }
};
