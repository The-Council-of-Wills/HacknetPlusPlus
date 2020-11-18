#pragma once
#include <vector>
#include "../GameManager.hpp"

class Command {
    public:
        virtual ~Command() {  };

        virtual void run(GameManager* game, std::vector<std::string> args) = 0;
};
