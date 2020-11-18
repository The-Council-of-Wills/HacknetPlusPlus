#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Computer.hpp"

class GameManager {
    private:
        Computer* playerComp;
        Computer* currentComp;

        std::map<std::string, Computer*> computerNetwork;

        void showConnected() {
            std::cout << "Connected to " << currentComp->toString() << '\n';
        }

    public:
        GameManager(Computer* player) {
            playerComp = player;
            currentComp = player;
            std::string ip = player->getIP();
            computerNetwork[ip] = player;
            showConnected();
        }

        ~GameManager() {
            for (auto c : computerNetwork) {
                delete c.second;
            }
        }

        void addComputer(std::string name, std::string ip) {
            Computer* newComp = new Computer(name, ip);
            computerNetwork[ip] = newComp;
            currentComp->addLink(newComp);
        }

        void addComputer(Computer* comp) {
            std::string ip = comp->getIP();
            computerNetwork[ip] = comp;
            currentComp->addLink(comp);
        }

        void connect(std::string ip) {
            if (computerNetwork[ip] == nullptr) {
                std::cout << "Connection refused." << '\n';
            }
            else {
                currentComp = computerNetwork[ip];
                showConnected();
            }
        }

        Computer* getCurrent() {
            return currentComp;
        }

        Computer* getPlayer() {
            return playerComp;
        }
};
