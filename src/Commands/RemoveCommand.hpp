#pragma once
#include "Command.hpp"

class RemoveCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            Folder* directory = game->getDirectory();
            FileSystemElement* elem = evaluatePath(directory, args[1]);
            if (elem != nullptr && !elem->isFolder()) {
                Folder* folder = (Folder *)elem->getParent();
                folder->deleteElement(elem->getName());
            }
            else {
                std::cout << "Failed to delete file.\n";
            }
        }
};