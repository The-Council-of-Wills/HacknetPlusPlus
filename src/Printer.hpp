#pragma once
#include <deque>
#include <string>
#include <sstream>
#include "lib/sol/sol.hpp"

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

        static void print(sol::variadic_args va) {
            std::string s;
            for (auto v : va) {
                s += v.as<std::string>() + ' ';
            }
            print(s);
        }

        static void clear() {
            printQueue.clear();
        }

        static void resize(int n) {
            while (printQueue.size() > n) printQueue.pop_front();
        }

        static std::deque<std::string> getDeque() {
            return printQueue;
        }
};

std::deque<std::string> Printer::printQueue = {};