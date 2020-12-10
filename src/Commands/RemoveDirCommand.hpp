#pragma once
#include "Command.hpp"

class RemoveDirCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;

            GameManager *game = GameManager::getInstance();
            FileSystemElement* elem = game->getDirectory()->getElement(args[1]);
            
            if (elem == nullptr) {
                std::cout << "Error: directory does not exist.\n";
            }
            else if (elem->getType() == FileSystemType::Folder) {
                Folder* folder = (Folder*) elem;
                if (folder->listChildren().empty()) {
                    game->getDirectory()->deleteElement(args[1]);
                }
                else {
                    std::cout << "Error: directory is not empty.\n";
                }
            }
            else {
                std::cout << "Error: is not a directory.\n";
            }
        }
};
