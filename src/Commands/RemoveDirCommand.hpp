#pragma once
#include "Command.hpp"

class RemoveDirCommand : public Command {
    public:
        void run(const std::vector<std::string> &args) override {
            if (!hasExactArguments(2, args)) return;

            GameManager *game = GameManager::getInstance();
            FileSystemElement* elem = game->getDirectory()->evaluatePath(args[1]);
            
            if (elem == nullptr) {
                Printer::print("Error: directory does not exist.");
            }
            else if (elem->getType() == FileSystemType::Folder) {
                Folder* folder = (Folder*) elem;
                if (folder->listChildren().empty()) {
                    game->getDirectory()->deleteElement(args[1]);
                }
                else {
                    Printer::print("Error: directory is not empty.");
                }
            }
            else {
                Printer::print("Error: is not a directory.");
            }
        }
};
