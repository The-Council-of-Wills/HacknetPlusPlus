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
