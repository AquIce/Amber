#include <ADL/ADL.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <iostream>

int WinMain(int argc, char** argv) {

    struct ADL::ADLConfig config = {
        "ADL",
        { 680, 480 }
    };

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        config.name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config.size.x, config.size.y,
        0
    );

    if(!window) {
        std::cerr << "Error trying to create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    bool running = true;
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
    }

    return 0;
}
