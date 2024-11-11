#include <ADL/ADL.hpp>

struct ADL::Config ADL::newConfig(std::string name, Vec2 size) {
    return {
        name,
        size,
        nullptr,
        std::vector<struct ADL::EventHandler>()
    };
}

[[nodiscard]] ADL::ExitCode ADL::Init_Window(struct ADL::Config* config) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return ADL::ExitCode::ADL_FATAL_ERR;
    }

    config->window = SDL_CreateWindow(
        config->name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config->size.x, config->size.y,
        0
    );

    if(!config->window) {
        std::cerr << "Error trying to create window: " << SDL_GetError() << std::endl;
        return ADL::ExitCode::ADL_FATAL_ERR;
    }

    return ADL::ExitCode::ADL_SUCCESS;
}

[[nodiscard]] ADL::ExitCode ADL::AddEventHandler(struct ADL::Config* config, ADL::EventHandler handler) {
    config->eventHandlers.push_back(handler);
    return ADL::ExitCode::ADL_SUCCESS;
}

[[nodiscard]] ADL::ExitCode ADL::Run(const struct ADL::Config& config) {
    bool running = true;
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0) {
            for(const EventHandler& handler : config.eventHandlers) {
                if(e.type == handler.eventType) {
                    handler.handler(&running);
                }
            }
        }
    }

    return ADL::ExitCode::ADL_SUCCESS;
}
