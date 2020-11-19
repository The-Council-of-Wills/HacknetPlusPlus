#pragma once
#include "FileSystemElement.hpp"

class File : public FileSystemElement {
    private:
        std::string contents;
    public:
        File(std::string filename, std::string fileContents) : FileSystemElement(filename) {
            contents = fileContents;
        }

        std::string showTree(std::string prefix, bool last) {
            std::string ans = prefix;
            if (last) {
                ans += u8"└── ";
            }
            else {
                ans += u8"├── ";
            }
            return ans + toString();
        }

        bool isFolder() {
            return false;
        }
};
