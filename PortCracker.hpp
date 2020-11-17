#pragma once
#import "Port.hpp"

class PortCracker {
    private:
        Port *port;
    public:
        PortCracker(Port *port) {
            this->port = port;
        }

        ~PortCracker() {
            delete port;
        }
};
