#include <iostream>
#include <vector>
#include <string>
#include "Game.hpp"
#include "FileSystem/FileSystemImport.hpp"
#include "Computer.hpp"

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