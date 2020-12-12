#pragma once
#include "FileSystemElement.hpp"
#include "../lib/lua.hpp"

class Executable : public FileSystemElement {
    private:
        lua_State* state;

        static void print_error(lua_State* state) {
            const char* message = lua_tostring(state, -1);
            std::cerr << message << '\n';
            lua_pop(state, 1);
        }
    public: 
        Executable(std::string name, std::string scriptName) : FileSystemElement(name) {
            state = luaL_newstate();
            luaL_openlibs(state);

            int result = luaL_loadfile(state, scriptName.c_str());

            if (result != LUA_OK) {
                print_error(state);
            }
        }

        ~Executable() {
            lua_close(state);
        }

        FileSystemType getType() {
            return FileSystemType::Executable;
        }

        void run(std::vector<std::string> args) {
            int result = lua_pcall(state, 0, LUA_MULTRET, 0);
            
            if (result != LUA_OK) {
                print_error(state);
            }
        }
};