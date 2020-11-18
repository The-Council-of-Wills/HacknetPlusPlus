#pragma once
#include <string>
#include <set>

class Computer {
    private:
        const std::string separator = "\n-----------------\n";

        std::string name;
        std::string ip;
        std::set<Computer*> links;
    public:
        Computer(std::string compName, std::string compIp) {
            name = compName;
            ip = compIp;
        }

        bool connected(Computer *computer) {
            return links.count(computer);
        }

        void addLink(Computer *computer) {
            links.insert(computer);
        }

        std::string getIP() {
            return ip;
        }

        std::string toString() {
            return name + "::" + ip;
        }

        std::string scan() {
            int computerAmount = (int)links.size();
            std::string res = "Scanning ended. Found " + std::to_string(computerAmount) + " computers.";

            if (links.empty()) {
                return "Scanning ended. No computers were found\n";
            }

            res += separator;
            for (auto comp : links) {
                res += comp->toString() + '\n';
            }

            return res;
        }
};
