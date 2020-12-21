#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "GameManager.hpp"
#include "Commands/CommandManager.hpp"

class Game {
    private:
        static std::queue<std::string> printQueue;

        SDL_Window* window;
        SDL_Renderer* renderer;

        TTF_Font* font;

        bool isRunning;
        int bufIndex;
        std::string inputBuffer;
        std::string userInput;

        Uint32 tickCount;

        GameManager* gameManager;
        CommandManager commandManager;
    public:
        Game() : isRunning{true}, bufIndex{0}, inputBuffer{""}, userInput{""} {
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cerr << "Error initializing SDL: " << SDL_GetError() << '\n';
            }
            if (TTF_Init() != 0) {
                std::cerr << "Error initializing TTF: " << TTF_GetError() << '\n';
            }

            window = SDL_CreateWindow(
                "hacknet++",
                100,
                100,
                1024,
                768,
                0
            );

            renderer = SDL_CreateRenderer(
                window,
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );

            font = TTF_OpenFont(GameManager::getResource("assets/SourceCodePro-Regular.ttf").c_str(), 24);
            if (!font) {
                std::cerr << "Failed to load font: " << TTF_GetError() << '\n';
            }

            SDL_StartTextInput();
            tickCount = SDL_GetTicks();

            gameManager = GameManager::getInstance();
        }

        ~Game() {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_StopTextInput();
            SDL_Quit();

            delete gameManager;
        }

        void run() {
            while (isRunning) {
                processInput();
                updateGame();
                renderScreen();

                while(!SDL_TICKS_PASSED(SDL_GetTicks(), tickCount + 16));
                tickCount = SDL_GetTicks();
            }
        }

        static void print(std::string s) {
            printQueue.push(s);
        }
    
    private:
        void processInput() {
            for (SDL_Event event; SDL_PollEvent(&event);) {
                switch (event.type) {
                    case SDL_QUIT:
                        isRunning = false;
                        break;
                    case SDL_TEXTINPUT:
                        inputBuffer.insert(bufIndex, event.text.text);
                        bufIndex++;
                        break;
                    case SDL_KEYDOWN:
                        processKey(event.key.keysym.sym);
                        break;
                }
            }
        }

        void processKey(SDL_Keycode k) {
            switch (k) {
                case SDLK_RETURN:
                    userInput = inputBuffer;
                    inputBuffer = "";
                    bufIndex = 0;
                    break;
                case SDLK_BACKSPACE:
                    if (bufIndex == 0 || inputBuffer.size() == 0) break;
                    bufIndex--;
                    inputBuffer.erase(bufIndex, 1);
                    break;
                case SDLK_LEFT:
                    bufIndex = std::max(0, bufIndex - 1);
                    break;
                case SDLK_RIGHT:
                    bufIndex = std::min((int)inputBuffer.size(), bufIndex + 1);
                    break;
            }
        }

        void updateGame() {
            commandManager.updateExecutables();

            if (userInput == "exit") {
                isRunning = false;
            }
            else if (userInput != "") {
                std::vector<std::string> args;
                parseArgs(userInput, args);
                commandManager.processCommand(args);
                userInput = "";
            }
        }

        void renderScreen() {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            displayText((">" + inputBuffer), 100, 100);

            SDL_RenderPresent(renderer);
        }

        void displayText(std::string s, int x, int y) {
            SDL_Surface* text = TTF_RenderText_Solid(font, s.c_str(), {255, 255, 255});
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
            SDL_Rect destination = {
                x, y, text->w, text->h
            };
            SDL_RenderCopy(renderer, text_texture, NULL, &destination);
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);
        }

        static void parseArgs(std::string input, std::vector<std::string> &out) {
            std::stringstream userInputStream(input);
            char current;
            bool quote = false;
            std::string buffer;
            while(userInputStream.get(current)) {
                if (current == '"') {
                    if (quote) {
                        out.push_back(buffer);
                        buffer = "";
                    }
                    quote = !quote;
                }
                else if (quote) {
                    buffer += current;
                }
                else if (current == ' ') {
                    if (buffer != "") {
                        out.push_back(buffer);
                        buffer = "";
                    }
                }
                else {
                    buffer += current;
                }
            }

            if (buffer != "") out.push_back(buffer);
        }
};