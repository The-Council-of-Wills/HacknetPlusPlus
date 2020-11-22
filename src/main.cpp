#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GameManager.hpp"
#include "Commands/CommandManager.hpp"
#include "FileSystem/FileSystemImport.hpp"
#include "Computer.hpp"

int main() {
    std::cout << "Hacknet++ baybeee" << '\n';

    Computer* playerComp = new Computer("Tarche's battlestation", "123.123.123.123", 4);

    GameManager* game = new GameManager(playerComp);
    CommandManager* commands = new CommandManager(game);

    while (true) {
        std::cout << '>';
        std::string userInput;
        getline(std::cin, userInput);

        std::stringstream userInputStream(userInput);

        if (userInput == "exit") {
            return 0;
        }

        std::vector<std::string> args;
        std::string buffer;
        char current;
        bool quote = false;
        while(userInputStream.get(current)) {
            if (current == '"') {
                if (quote) {
                    args.push_back(buffer);
                    buffer = "";
                }
                quote = !quote;
            }
            else if (quote) {
                buffer += current;
            }
            else if (current == ' ') {
                if (buffer != "") {
                    args.push_back(buffer);
                    buffer = "";
                }
            }
            else {
                buffer += current;
            }
        }

        if (buffer != "") args.push_back(buffer);

        commands->processCommand(args);
    }
}
