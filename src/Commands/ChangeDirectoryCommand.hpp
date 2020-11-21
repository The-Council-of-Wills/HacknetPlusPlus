#pragma once
#include "Command.hpp"
#include "../FileSystem/FileSystemImport.hpp"

class ChangeDirectoryCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            std::string newDirectory = args[1];
            FileSystemElement *gameDir = game->getDirectory();
            FileSystemElement *elem = evaluatePath(gameDir, newDirectory);
            if (elem != nullptr && elem->isFolder()) {
                game->setDirectory(elem);
            }
            else {
                std::cout << newDirectory << " is not a folder\n";
            }

        }
};
