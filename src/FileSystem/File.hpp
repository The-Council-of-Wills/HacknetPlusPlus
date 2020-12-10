#pragma once
#include "FileSystemElement.hpp"

class File : public FileSystemElement {
    private:
        std::string contents;
    public:
        File(std::string filename) : FileSystemElement(filename) {  }
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

        FileSystemType getType() {
            return FileSystemType::File;
        }

        std::string getContents() {
            return contents;
        }

        void append(std::string text) {
            if (!contents.empty()) contents += '\n';
            contents += text;
        }
};
