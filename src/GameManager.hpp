#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "lib/json.hpp"
#include "Computer.hpp"
#include "FileSystem/FileSystemImport.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

class GameManager {
    private:
        static GameManager* instance;

        std::string extensionPath;

        Computer* playerComp;
        Computer* currentComp;

        //Folder* currentFolder;

        std::map<std::string, Computer*> computerIDs;
        std::map<std::string, Computer*> computerNetwork;

        GameManager(std::string extensionPath) : extensionPath{extensionPath} { }

        GameManager(Computer* player) {
            playerComp = player;
            currentComp = player;
            //currentFolder = player->getFileSystem();

            std::string ip = player->getIP();
            computerNetwork[ip] = player;
        }

        void setPlayer(Computer* player) {
            playerComp = player;
            currentComp = player;
            //currentFolder = player->getFileSystem();
        }
    protected:
        void buildNode(const json &data, const std::string &playerID);
        void buildFileSystem(const json &data, Folder *f);
    public:
        static GameManager* getInstance() {
            if (instance == nullptr) {
                instance = new GameManager(new Computer("Tarche's battlestation", "tarche", "123.123.123.123", 4));
            }
            return instance;
        }

        static void loadExtension(std::string extensionPath);

        ~GameManager() {
            for (auto c : computerNetwork) {
                delete c.second;
            }
        }

        void addComputer(Computer* comp) {
            std::string ip = comp->getIP();
            computerNetwork[ip] = comp;
            currentComp->addLink(comp);
        }

        void addLink(Computer* from, Computer* to) {
            from->addLink(to);
        }

        void connect(std::string ip) {
            if (computerNetwork[ip] == nullptr) {
                std::cout << "Connection refused." << '\n';
            }
            else {
                currentComp = computerNetwork[ip];
                //currentFolder = currentComp->getFileSystem();
                showConnected();
            }
        }

        void setDirectory(Folder* dir) {
            currentComp->setDirectory(dir);
            //currentFolder = (Folder*)dir;
        }

        Computer* getCurrentComputer() {
            return currentComp;
        }

        Computer* getPlayer() {
            return playerComp;
        }

        Folder* getDirectory() {
            return currentComp->getDirectory();
        }

        Folder* getPlayerDir() {
            return playerComp->getFileSystem();
        }

        void showConnected() {
            std::cout << "Connected to " << currentComp->toString() << '\n';
        }
};

GameManager* GameManager::instance = nullptr;

void GameManager::loadExtension(std::string extensionPath) {
    json extensionInfo;
    std::ifstream infoFile(extensionPath + "/extension_info.json");
    
    if (!infoFile.is_open()) {
        std::cerr << "Error opening extension_info.json" << '\n';
        return;
    }

    infoFile >> extensionInfo;

    if (extensionInfo["game"] != "hacknet++") {
        std::cerr << "This extension if not for Hacknet++" << '\n';
        return;
    }

    std::string playerID = extensionInfo["playerComp"];
    std::string nodeFolder = extensionPath + "/" + (std::string)extensionInfo["nodeFolder"];

    std::map<std::string, std::vector<std::string>> dlinks;

    GameManager *g = new GameManager(extensionPath);
    instance = g;

    for (const auto &nodeFile : fs::directory_iterator(nodeFolder)) {
        json curr;
        std::ifstream currFile(nodeFile.path());
        currFile >> curr;
        currFile.close();
        
        g->buildNode(curr, playerID);
        
        for (auto link : curr["dlinks"]) {
            dlinks[curr["id"]].push_back(link);
        }
    }

    for (auto i : dlinks) {
        for (auto j : i.second) {
            g->addLink(g->computerIDs[i.first], g->computerIDs[j]);
        }
    }
}

void GameManager::buildNode(const json &data, const std::string &playerID) {
    std::string id = data["id"];

    Computer* currComp = new Computer(
        data["name"],
        id,
        data["ip"],
        data["security"]["required"]
    );

    GameManager *g = GameManager::getInstance();
    g->computerIDs[id] = currComp;
    g->computerNetwork[data["ip"]] = currComp;

    if (id == playerID) {
        g->setPlayer(currComp);
    }

    buildFileSystem(data["filesystem"], currComp->getFileSystem());
}

void GameManager::buildFileSystem(const json &data, Folder *f) {
    for (auto &elem : data.items()) {
        std::string name = elem.key();
        json value = elem.value();

        if (name[0] == '/') {
            Folder* folder = new Folder(name.substr(1));
            GameManager::getInstance()->buildFileSystem(value, folder);
            f->insertElement(folder);
        }
        
        else {
            if (value.contains("script")) {
                std::string filename = value["script"];
                Executable *e = new Executable(name, extensionPath + '/' + filename);
                f->insertElement(e);
            }
            else {
                std::string content = value["content"];
                File* file = new File(name, content);
                f->insertElement(file);
            }
        }
    }
}