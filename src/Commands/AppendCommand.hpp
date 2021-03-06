#pragma once
#include "Command.hpp"

class AppendCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(3, args)) return;

            std::string filename = args[1], contents = args[2];
            Folder* dir = GameManager::getInstance()->getDirectory();
            FileSystemElement* elem = evaluatePath(dir, filename);
            
            if (elem == nullptr) {
                std::cout << "File not found. Please try again.\n";
            }
            else if (elem->getType() == FileSystemType::File) {
                File* file = (File *)elem;
                file->append(contents);
            }
            else if (elem->getType() == FileSystemType::Executable) {
                std::cout << "Error: can't append to a binary file.\n";
            }
            else {
                std::cout << "Error: can't append to a folder.\n";
            }
        }
};
