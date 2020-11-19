#pragma once
#include "Folder.hpp"
#include "File.hpp"

Folder regularFileSystem() {
    Folder root("/");
    Folder* home = new Folder("home");
    Folder* log = new Folder("log");
    Folder* bin = new Folder("bin");
    Folder* sys = new Folder("sys");
    root.insertElement(home);
    root.insertElement(log);
    root.insertElement(bin);
    root.insertElement(sys);
    return root;
}
