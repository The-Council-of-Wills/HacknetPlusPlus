#pragma once
#include "Command.hpp"

class AppendCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(3, args)) return;
            std::string filename = args[1], contents = args[2];
            FileSystemElement* elem = game->getDirectory()->getElement(filename);
            if (elem != nullptr && !elem->isFolder()) {
                File* file = (File *)elem;
                file->append(contents);
                return;
            }

            std::cout << "File not found. Please try again.\n";
        }
};
