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
        CommandManager(GameManager *g);

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
                commands[args[0]]->run(game, args);
            }
            else {
                std::cout << "Unknown command." << '\n';
            }
        }
};

CommandManager::CommandManager(GameManager *g) {
    game = g;

    commands["scan"] = new ScanCommand;

    SelfCommand *self = new SelfCommand;
    commands["self"] = self;
    commands["whoami"] = self;

    commands["connect"] = new ConnectCommand;

    commands["whereami"] = new WhereCommand;

    commands["addComputer"] = new AddComputerCommand;
}
