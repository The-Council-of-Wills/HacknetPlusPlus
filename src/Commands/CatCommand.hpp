#pragma once
#include "Command.hpp"

class CatCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            std::string filename = args[1];
            FileSystemElement* elem = evaluatePath(game->getDirectory(), filename);

            if (elem != nullptr && !elem->isFolder()) {
                File* file = (File *)elem;
                std::cout << file->getContents() << '\n';
                return;
            }

            std::cout << "File not found. Please try again.\n";
        }
};
