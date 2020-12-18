#pragma once
#include "Command.hpp"

class CatCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;

            std::string filename = args[1];
            Folder* dir = GameManager::getInstance()->getDirectory();
            FileSystemElement* elem = Folder::evaluatePath(dir, filename);

            if (elem == nullptr) {
                std::cout << "File not found. Please try again.\n";
            }
            else if (elem->getType() == FileSystemType::File) {
                File* file = (File *)elem;
                std::cout << file->getContents() << '\n';
            }
            else if (elem->getType() == FileSystemType::Executable) {
                std::cout << "Can't open binary file.\n";
            }
            else {
                std::cout << "Can't open a folder.\n";
            }
        }
};
