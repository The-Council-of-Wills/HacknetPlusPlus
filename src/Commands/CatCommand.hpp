#pragma once
#include "Command.hpp"

class CatCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;

            std::string filename = args[1];
            Folder* dir = GameManager::getInstance()->getDirectory();
            FileSystemElement* elem = evaluatePath(dir, filename);

            if (elem != nullptr && !elem->isFolder()) {
                File* file = (File *)elem;
                std::cout << file->getContents() << '\n';
                return;
            }

            std::cout << "File not found. Please try again.\n";
        }
};
