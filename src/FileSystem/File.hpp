#pragma once
#include "FileSystemElement.hpp"

class File : public FileSystemElement {
    private:
        std::string contents;
    public:
        File(std::string filename, std::string fileContents) : FileSystemElement(filename) {
            contents = fileContents;
        }

        std::string showTree(const std::string &prefix) {
            return prefix + toString();
        }

        bool isFolder() {
            return false;
        }
};
