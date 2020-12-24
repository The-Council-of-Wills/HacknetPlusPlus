#pragma once
#include <string>
#include <any>
#include <set>
#include "Security/SecuritySuite.hpp"
#include "FileSystem/FileSystemImport.hpp"
#include "lib/sol/sol.hpp"
#include "Printer.hpp"

class Computer {
    private:
        const std::string separator = "\n-----------------\n";

        std::string name;
        std::string id;
        std::string ip;
        std::set<Computer*> links;

        Folder* root = new Folder("/");
        SecuritySuite security;

        Folder* currentDirectory = root;

        sol::state lua;

        std::map<std::string, sol::object> systemVars;
    public:
        Computer(std::string name, std::string id, std::string ip, int securityLevel) :
            name { name }, id{ id }, ip{ ip }, security(securityLevel)
        {
            lua.open_libraries(sol::lib::base);
            lua.open_libraries(sol::lib::string);
            lua.open_libraries(sol::lib::math);
            lua.open_libraries(sol::lib::table);

            lua.set_function("print", sol::resolve<sol::variadic_args>(&Printer::print));
            lua.set_function("clearScreen", &Printer::clear);

            //               |  function name   |      method definition      | instance
            lua.set_function("getSystemVariable", &Computer::getSystemVariable, this);
            lua.set_function("setSystemVariable", &Computer::setSystemVariable, this);
            lua.set_function("getFileSystem", &Computer::getFileSystem, this);
            lua.set_function("getcwd", &Computer::getDirectory, this);
            lua.set_function("setcwd", &Computer::setDirectory, this);

            /*
            Usertype registration
            Used for interacting with the API
            in an OOP manner.

            Example:
            root = getFileSystem()
            print(root:getTree())
            */ 

            sol::usertype<FileSystemElement> fsElementType = lua.new_usertype<FileSystemElement>("FileSystemElement");
            fsElementType.set_function("getParent", &FileSystemElement::getParent);
            fsElementType.set_function("getName", &FileSystemElement::getName);
            fsElementType.set_function("toString", &FileSystemElement::toString);


            File::registerUsertype(lua);
            Folder::registerUsertype(lua);
            Executable::registerUsertype(lua);
        }

        ~Computer() {
            delete root;
        }

        Folder* getFileSystem() {
            return root;
        }

        SecuritySuite getSecurity() {
            return security;
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

        void setDirectory(Folder* dir) {
            currentDirectory = dir;
        }

        Folder* getDirectory() {
            return currentDirectory;
        }

        void run(Executable* exe, std::vector<std::string> args) {
            sol::load_result load = lua.load_file(exe->getScript());

            if (!load.valid()) {
                sol::error err = load;
                std::cerr << "There was an error parsing file: " << exe->getName() << '\n';
                std::cerr << err.what() << '\n';
            }

            sol::function f = load;
            sol::environment execEnv(lua, sol::create, lua.globals());
            sol::set_environment(execEnv, f);

            f(sol::as_table(args));
        }


        // ============================== LUA API ============================== 

        sol::object getSystemVariable(std::string key) {
            return systemVars[key];
        }

        void setSystemVariable(std::string key, sol::object value) {
            systemVars[key] = value;
        }

        // =====================================================================
};
