#pragma once
#include "Command.hpp"

class RemoveDirCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            FileSystemElement* elem = game->getDirectory()->getElement(args[1]);
            if (elem != nullptr && elem->isFolder()) {
                Folder* folder = (Folder*) elem;
                if (folder->listChildren().empty()) {
                    game->getDirectory()->deleteElement(args[1]);
                }
                else {
                    std::cout << "Directory is not empty.\n";
                }
            }
            else {
                std::cout << "Directory does not exist.\n";
            }
        }
};
