#pragma once
#include <vector>
#include "../GameManager.hpp"

class Command {
    protected:
        static bool hasExactArguments(int amount, const std::vector<std::string> &args) {
            if ((int)args.size() < amount) {
                Printer::print("Missing arguments.");
                return false;
            }
            else if ((int)args.size() > amount) {
                Printer::print("Unexpected arguments.");
                return false;
            }
            return true;
        }
    public:
        virtual ~Command() {  };

        virtual void run(const std::vector<std::string> &args) = 0;
};
