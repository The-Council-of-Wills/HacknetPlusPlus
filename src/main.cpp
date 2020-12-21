#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "FileSystem/FileSystemImport.hpp"
#include "Computer.hpp"
#include "Game.hpp"

void startupText();

int main(int argc, char *argv[]) {
    GameManager::setAppDirFromExe(argv[0]);
    if (argc == 1) {
        std::cerr << "Debug mode enabled" << '\n';
        std::cerr << "Loading sample extension." << '\n';

        GameManager::loadExtension("./extensions/sample");
    }
    else if (argc == 2) {
        std::string extensionFolder(argv[1]);
        GameManager::loadExtension(extensionFolder);
    }
    else {
        std::cerr << "Error: unexpected arguments found. Please try again." << '\n';
        return 1;
    }    
    
    GameManager* gameManager = GameManager::getInstance();
    CommandManager* commands = new CommandManager();

    Game game;
    game.run();
}

void startupText() {
    std::string buffer;
    std::ifstream bannerStream(GameManager::getResource("assets/banner"));

    if (bannerStream.is_open()) {
        while (getline(bannerStream, buffer)) {
            std::cout << buffer << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        bannerStream.close();
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Enter 'help' for a list of commands" << '\n';
}

