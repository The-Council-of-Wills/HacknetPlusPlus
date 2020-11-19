#pragma once
#include "Command.hpp"
#include "../FileSystem/FileSystemImport.hpp"

class ChangeDirectoryCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (args.size() < 2) {
                std::cout << "Missing arguments\n";
            }
            else if (args.size() > 2) {
                std::cout << "Unexpected argument: " << args[2] << '\n';
            }
            else {
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
                for (auto element : game->getDirectory()->getChildren()) {
                    if (element->toString() == newDirectory && element->isFolder()) {
                        game->setDirectory(element);
                        return;
                    }
                }

                std::cout << newDirectory << " is not a folder\n";
            }
        }
};