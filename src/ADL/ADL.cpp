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
    float angle = 0;
    int size = 1;
    bool up = true;
    while(running) {

        // Rendering

        ADL::ClearScreen(config);

        struct ADL::PixelLine line = ADL::newPixelLine(
            ADL::newLine2(
                ADL::newVec2(0, 2 * size - radius),
                ADL::newVec2(config->size.x - 1, config->size.x - 2 * size)
            ),
            ADL::newRGBA(255, 255, 255, 255)
        );
        ADL::RenderPixelLine(config, &line);

        struct ADL::PixelRect rect = ADL::newPixelRect(
            ADL::newRect2(
                ADL::newVec2(240, 240),
                ADL::newVec2(50, 100),
                angle
            ),
            ADL::newRGBA(255, 0, 0, 255)
        );
        angle += M_PI / 1000;

        ADL::RenderPixelRect(config, &rect);

        struct ADL::PixelCurve curve = ADL::newPixelCurve(
            ADL::newCurve2(
                ADL::newVec2(240, 240),
                size,
                0, 0
            ),
            ADL::newRGBA(0, 255, 0, 255)
        );

        ADL::RenderPixelCurve(config, &curve);
        size += up ? 1 : -1;
        if(size == 250) {
            up = false;
        } else if(size == 1) {
            up = true;
        }

        ADL::PushRender(config);

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
