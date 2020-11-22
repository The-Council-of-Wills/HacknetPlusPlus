#pragma once
#include <string>
#include <map>

typedef struct {
    int number;
    bool isOpen;
    std::string name;
} Port;

class SecuritySuite {
    private:
        const std::string separator = "----------------";
        int required;
        std::map<int, Port> ports;
    public:
        SecuritySuite(int requiredAmount) {
            required = requiredAmount;
        }

        void addPort(int number, std::string name) {
            if (!ports.count(number)) {
                ports[number] = {
                    number,
                    false,
                    name
                };
            }
        }

        bool isOpen(int number) {
            if (!ports.count(number)) return false;
            return ports[number].isOpen;
        }

        void openPort(int number) {
            if (!ports.count(number)) return;
            ports[number].isOpen = true;
        }

        std::string probe() {
            std::string ans = "Open ports:\n" + separator + '\n';
            for (auto p : ports) {
                Port curr = p.second;
                ans += "Port " + std::to_string(curr.number) + " - ";
                ans += curr.name + " :";
                if (curr.isOpen) {
                    ans += "Opened";
                }
                else {
                    ans += "Closed";
                }
                ans += '\n';
            }
            ans += separator + '\n';
            ans += "Required ports: " + std::to_string(required) + '\n';
            return ans;
        }
};
