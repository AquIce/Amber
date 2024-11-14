#include <ARE/ARE.hpp>

NODISCARD ARE::ExitCode ARE::Init(
    struct ARE::Config* config
) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return ARE::ExitCode::ADL_FATAL_ERR;
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
        return ARE::ExitCode::ADL_FATAL_ERR;
    }

    config->sdl.renderer = SDL_CreateRenderer(config->sdl.window, 0, 0);

    if(!config->sdl.renderer) {
        std::cerr << "Error trying to create renderer: " << SDL_GetError() << std::endl;
        return ARE::ExitCode::ADL_FATAL_ERR;
    }

    return ARE::ExitCode::ADL_SUCCESS;
}

NODISCARD ARE::ExitCode ARE::AddEventHandler(
    struct ARE::Config* config,
    ARE::EventHandler handler
) {
    config->eventHandlers.push_back(handler);
    return ARE::ExitCode::ADL_SUCCESS;
}

NODISCARD ARE::ExitCode ARE::Run(
    struct ARE::Config* config
) {
    bool running = true;
    float angle = 0;
    int size = 1;
    bool up = true;

    while(running) {

        // Rendering

        ARE::ClearScreen(config);

        struct ARE::PixelLine line = ARE::newPixelLine(
            ARE::newLine2(
                ARE::newVec2(0, 2 * size),
                ARE::newVec2(config->size.x, config->size.x - 2 * size)
            ),
            ARE::newRGBA(255, 255, 255, 255)
        );
        ARE::RenderPixelLine(config, &line);

        struct ARE::PixelRect rect = ARE::newPixelRect(
            ARE::newRect2(
                ARE::newVec2(240, 240),
                ARE::newVec2(50, 100),
                angle
            ),
            ARE::newRGBA(255, 0, 0, 255)
        );
        angle += M_PI / 1000;

        ARE::RenderPixelRect(config, &rect);

        struct ARE::PixelCurve curve = ARE::newPixelCurve(
            ARE::newCurve2(
                ARE::newVec2(240, 240),
                size,
                2 * M_PI / 3, - M_PI / 5
            ),
            ARE::newRGBA(0, 255, 0, 255)
        );

        ARE::RenderPixelCurve(config, &curve);
        size += up ? 1 : -1;
        if(size == 250) {
            up = false;
        } else if(size == 1) {
            up = true;
        }

        ARE::PushRender(config);

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

    return ARE::ExitCode::ADL_SUCCESS;
}
