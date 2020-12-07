#pragma once
#include "Command.hpp"

class NotesCommand : public Command {
    public:
        void run(std::vector<std::string> args) {
            if (!hasExactArguments(1, args)) return;
            GameManager *game = GameManager::getInstance();
            Folder* playerDir = game->getPlayer()->getFileSystem();
            playerDir = playerDir->getOrCreateFolder("home");
            playerDir = playerDir->getOrCreateFolder("notes");
            File* notes = playerDir->getOrCreateFile("notes.txt");
            std::cout << notes->getContents() << '\n';
       }
};
