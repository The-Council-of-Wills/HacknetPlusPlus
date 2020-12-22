#pragma once
#include <deque>
#include <string>
#include <sstream>

class Printer {
    private:
        Printer() { }
        static std::deque<std::string> printQueue;
    public:
        static void print(std::string s) {
            std::stringstream str(s);
            for (std::string buf; getline(str, buf);) {
                printQueue.push_back(buf);
            }
        }

        static void resize(int n) {
            while (printQueue.size() > n) printQueue.pop_front();
        }

        static std::deque<std::string> getDeque() {
            return printQueue;
        }
};

std::deque<std::string> Printer::printQueue = {};