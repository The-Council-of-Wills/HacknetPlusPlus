#include <iostream>
#include <string>
#include "GameManager.hpp"
#include "Computer.hpp"

int main() {
    std::cout << "Hacknet++ baybeee" << '\n';

    Computer* playerComp = new Computer("Tarche's battlestation", "123.123.123.123");
    Computer* currentComp = playerComp;

    GameManager game;
    game.addComputer(playerComp);

    std::cout << "Connected to " << playerComp->toString() << '\n';

    while (true) {
        std::cout << '>';
        std::string userInput;
        getline(std::cin, userInput);

        //TODO: make this huge elif block into something readable
        //TODO: parse commands as it would in a normal shell, instead of asking for the parameters one by one.
        if (userInput == "exit") {
            return 0;
        }
        else if (userInput == "self" || userInput == "whoami") {
            std::cout << playerComp->toString() << '\n';
        }
        else if (userInput == "whereami") {
            std::cout << currentComp->toString() << '\n';
        }
        else if (userInput == "scan") {
            std::cout << currentComp->scan();
        }
        else if (userInput == "connect") {
            std::string computerIP;
            std::cout << "Enter computer IP: ";
            getline(std::cin, computerIP);

            Computer *ans = game.connect(computerIP);
            if (ans == nullptr) {
                std::cout << "Connection refused." << '\n';
            }
            else {
                currentComp = ans;
                std::cout << "Connected to " << currentComp->toString() << '\n';
            }
        }
        //NOTE: this is meant to be used to debug, will be removed later.
        else if (userInput == "addComputer") {
            std::string computerName, computerIP;

            std::cout << "Enter computer name: ";
            getline(std::cin, computerName);

            std::cout << "Enter computer IP: ";
            getline(std::cin, computerIP);

            Computer* newComp = new Computer(computerName, computerIP);
            game.addComputer(newComp);
            currentComp->addLink(newComp);
        }
        else {
            std::cout << "Unknown command." << '\n';
        }
    }
}
