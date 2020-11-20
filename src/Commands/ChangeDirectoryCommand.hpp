#pragma once
#include "Command.hpp"
#include "../FileSystem/FileSystemImport.hpp"

class ChangeDirectoryCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            std::string newDirectory = args[1];
            if (newDirectory == ".") {
                return;
            }
            else if (newDirectory == "..") {
                FileSystemElement* parent = game->getDirectory()->getParent();
                if (parent != nullptr && parent->isFolder()) {
                    game->setDirectory(parent);
                }
                return;
            }

            FileSystemElement *elem = game->getDirectory()->getElement(newDirectory);
            if (elem != nullptr && elem->isFolder()) {
                game->setDirectory(elem);
            }
            else {
                std::cout << newDirectory << " is not a folder\n";
            }

        }
};
