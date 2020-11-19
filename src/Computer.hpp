#pragma once
#include <string>
#include <set>
#include "FileSystem/FileSystemImport.hpp"

class Computer {
    private:
        const std::string separator = "\n-----------------\n";

        std::string name;
        std::string ip;
        std::set<Computer*> links;

        Folder* root = regularFileSystem();
    public:
        Computer(std::string compName, std::string compIp) {
            name = compName;
            ip = compIp;
        }

        Folder* getFileSystem() {
            return root;
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
            std::string computerAmount = std::to_string(links.size());
            std::string res = "Scanning ended. Found " + computerAmount + " computers.";

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
