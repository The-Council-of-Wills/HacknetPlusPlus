#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../GameManager.hpp"
#include "CommandInclude.hpp"

class CommandManager {
    private:
        GameManager* game;
        std::map<std::string, Command*> commands;
    public:
        CommandManager();

        ~CommandManager() {
            for (auto c : commands) {
                delete c.second;
            }
        }

        void addCommand(std::string name, Command *c) {
            commands[name] = c;
        }

        void processCommand(std::vector<std::string> args) {
            if (commands.count(args[0])) {
                commands[args[0]]->run(args);
            }
            else {
                std::cout << "Unknown command." << '\n';
            }
        }
};

CommandManager::CommandManager() {
    commands["scan"]        = new ScanCommand;
    commands["self"]        = new SelfCommand;
    commands["whoami"]      = new SelfCommand;
    commands["connect"]     = new ConnectCommand;
    commands["whereami"]    = new WhereCommand;
    commands["cd"]          = new ChangeDirectoryCommand;
    commands["tree"]        = new TreeCommand;
    commands["ls"]          = new ListDirectoryCommand;
    commands["cat"]         = new CatCommand;
    commands["mkdir"]       = new MakeDirCommand;
    commands["rmdir"]       = new RemoveDirCommand;
    commands["touch"]       = new TouchCommand;
    commands["append"]      = new AppendCommand;
    commands["probe"]       = new ProbeCommand;
    commands["help"]        = new HelpCommand;
    commands["notes"]       = new NotesCommand;
    commands["addNote"]     = new AddNoteCommand;
    commands["rm"]          = new RemoveCommand;
}
