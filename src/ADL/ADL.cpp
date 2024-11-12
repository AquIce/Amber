#include <ADL/ADL.hpp>

NODISCARD ADL::ExitCode ADL::Init(
    struct ADL::Config* config
) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return ADL::ExitCode::ADL_FATAL_ERR;
    }

    config->sdl.window = SDL_CreateWindow(
        config->name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config->size.x, config->size.y,
        0
    );

    if(!config->sdl.window) {
        std::cerr << "Error trying to create window: " << SDL_GetError() << std::endl;
        return ADL::ExitCode::ADL_FATAL_ERR;
    }

    config->sdl.renderer = SDL_CreateRenderer(config->sdl.window, 0, 0);

    if(!config->sdl.renderer) {
        std::cerr << "Error trying to create renderer: " << SDL_GetError() << std::endl;
        return ADL::ExitCode::ADL_FATAL_ERR;
    }

    return ADL::ExitCode::ADL_SUCCESS;
}

NODISCARD ADL::ExitCode ADL::AddEventHandler(
    struct ADL::Config* config,
    ADL::EventHandler handler
) {
    config->eventHandlers.push_back(handler);
    return ADL::ExitCode::ADL_SUCCESS;
}

NODISCARD ADL::ExitCode ADL::Run(
    struct ADL::Config* config
) {
    bool running = true;
    while(running) {

        // Rendering

        ADL::ClearScreen(config);

        struct ADL::PixelLine line = {
            ADL::newLine2(
                ADL::newVec2(0, 0),
                ADL::newVec2(config->size.x - 1, config->size.x / 3)
            ),
            ADL::newRGBA(255, 255, 255, 255)
        };

        ADL::RenderLine(config, &line);

        ADL::Flush(config);

        // Events Handling

        SDL_Event e;
        while(SDL_PollEvent(&e) > 0) {
            for(const EventHandler& handler : config->eventHandlers) {
                if(e.type == handler.eventType) {
                    handler.handler(&running);
                }
            }
        }
    }

    SDL_DestroyRenderer(config->sdl.renderer);
    SDL_DestroyWindow(config->sdl.window);

    return ADL::ExitCode::ADL_SUCCESS;
}
