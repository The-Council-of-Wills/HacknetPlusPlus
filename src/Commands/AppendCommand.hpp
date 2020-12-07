#pragma once
#include "Command.hpp"

class AppendCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(3, args)) return;

            std::string filename = args[1], contents = args[2];
            Folder* dir = GameManager::getInstance()->getDirectory();
            FileSystemElement* elem = evaluatePath(dir, filename);
            
            if (elem != nullptr && !elem->isFolder()) {
                File* file = (File *)elem;
                file->append(contents);
                return;
            }

            std::cout << "File not found. Please try again.\n";
        }
};
