#pragma once
#include <sstream>
#include "Folder.hpp"
#include "File.hpp"
#include "Executable.hpp"

FileSystemElement* evaluatePath(FileSystemElement* curr, std::string path) {
    if (path[0] == '/') {
        while (curr->getParent() != nullptr)
            curr = curr->getParent();
    }

    std::stringstream pathStream(path);
    std::string buffer;
    bool foundFile = false;
    while (getline(pathStream, buffer, '/')) {
        if (buffer.empty() || buffer == ".") continue;
        if (curr == nullptr) return nullptr;
        if (curr->getType() == FileSystemType::Folder) {
            if (buffer == "..") {
                curr = curr->getParent();
            }
            else {
                Folder* currFolder = (Folder *)curr;
                curr = currFolder->getElement(buffer);
            }
        }
        else if (foundFile) {
            return nullptr;
        }
        else {
            foundFile = true;
        }
    }

    return curr;
}
