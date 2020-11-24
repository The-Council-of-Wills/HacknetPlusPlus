#pragma once
#include "Command.hpp"

class AddNoteCommand : public Command {
    public:
        void run(GameManager *game, std::vector<std::string> args) {
            if (!hasExactArguments(2, args)) return;
            Folder* playerDir = game->getPlayer()->getFileSystem();
            playerDir = playerDir->getOrCreateFolder("home");
            playerDir = playerDir->getOrCreateFolder("notes");
            File* notes = playerDir->getOrCreateFile("notes.txt");
            notes->append(args[1]);
        }
};
