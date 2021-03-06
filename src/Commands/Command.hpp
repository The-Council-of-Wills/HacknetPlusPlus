#pragma once
#include <vector>
#include "../GameManager.hpp"

class Command {
    protected:
        static bool hasExactArguments(int amount, const std::vector<std::string> &args) {
            if ((int)args.size() < amount) {
                std::cout << "Missing arguments.\n";
                return false;
            }
            else if ((int) args.size() > amount) {
                std::cout << "Unexpected arguments.\n";
                return false;
            }
            return true;
        }
    public:
        virtual ~Command() {  };

        virtual void run(const std::vector<std::string> &args) = 0;
};
