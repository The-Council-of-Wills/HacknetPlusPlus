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

        static void registerUsertype(sol::state& lua) {
            sol::usertype<File> fileType = lua.new_usertype<File>("File");

            fileType.set_function("getType", &File::getType);
            fileType.set_function("setParent", &File::setParent);
            fileType.set_function("getContents", &File::getContents);
            fileType.set_function("append", &File::append);
        }

        FileSystemType getType() {
            return FileSystemType::File;
        }

        std::string getContents() {
            return contents;
        }

        void append(std::string text) {
            contents += text;
        }
        
};
