#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Computer.hpp"
#include "FileSystem/FileSystemImport.hpp"

class GameManager {
    private:
        static GameManager* instance;

        GameManager(Computer* player) {
            playerComp = player;
            currentComp = player;
            currentFolder = player->getFileSystem();

            std::string ip = player->getIP();
            computerNetwork[ip] = player;
            showConnected();

            instance = this;
        }

        Computer* playerComp;
        Computer* currentComp;

        Folder* currentFolder;

        std::map<std::string, Computer*> computerNetwork;

        void showConnected() {
            std::cout << "Connected to " << currentComp->toString() << '\n';
        }

    public:
        static GameManager* getInstance() {
            if (instance == nullptr) {
                GameManager(new Computer("Tarche's battlestation", "123.123.123.123", 4));
            }
            return instance;
        }

        ~GameManager() {
            for (auto c : computerNetwork) {
                delete c.second;
            }
        }

        void addComputer(std::string name, std::string ip, int securityLevel) {
            Computer* newComp = new Computer(name, ip, securityLevel);
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
                currentFolder = currentComp->getFileSystem();
                showConnected();
            }
        }

        void setDirectory(FileSystemElement* dir) {
            currentFolder = (Folder*)dir;
        }

        Computer* getCurrent() {
            return currentComp;
        }

        Computer* getPlayer() {
            return playerComp;
        }

        Folder* getDirectory() {
            return currentFolder;
        }
};
