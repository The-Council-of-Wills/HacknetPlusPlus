#pragma once
#include "Executable.hpp"

class PortCracker : public Executable{
    private:
        int target;
    public:
        PortCracker(int target, std::string name) : target{target}, Executable(name) {

        }

        void run(std::vector<std::string> args) {
            std::cout << "test123" << target << name << '\n';
        }
};