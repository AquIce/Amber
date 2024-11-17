#include <ARE/ARE.hpp>

[[nodiscard]] struct ARE::ReturnCode ARE::Init(
    struct ARE::Config* config
) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return ARE::log(
            ARE::newLog(
                ARE::LogLevel::ERROR,
                ARE::newReturnCode(
                    true,
                    -1
                ),
                std::string("Error initializing SDL: ") + SDL_GetError()
            )
        );
    }

    config->sdl.window = SDL_CreateWindow(
        config->name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config->size.x, config->size.y,
        0
    );

    if(!config->sdl.window) {
        return ARE::log(
            ARE::newLog(
                ARE::LogLevel::ERROR,
                ARE::newReturnCode(
                    true,
                    -1
                ),
                std::string("Error trying to create window: ") + SDL_GetError()
            )
        );
    }

    config->sdl.renderer = SDL_CreateRenderer(config->sdl.window, 0, 0);

    if(!config->sdl.renderer) {
        return ARE::log(
            ARE::newLog(
                ARE::LogLevel::ERROR,
                ARE::newReturnCode(
                    true,
                    -1
                ),
                std::string("Error trying to create renderer: ") + SDL_GetError()
            )
        );
    }

    return ARE::newReturnCode();
}

[[nodiscard]] ARE::ReturnCode ARE::AddEventHandler(
    struct ARE::Config* config,
    ARE::EventHandler handler
) {
    config->eventHandlers.push_back(handler);
    return ARE::newReturnCode();
}

[[nodiscard]] ARE::ReturnCode ARE::Run(
    struct ARE::Config* config
) {
    bool running = true;
    float angle = 0;
    int size = 1;
    bool up = true;
    ARE::Benchmark benchmark = ARE::newBenchmark("FPS Counter");

    struct ARE::PixelLine line = ARE::newPixelLine(
        ARE::newLine2(
            ARE::newVec2(0, 2 * size),
            ARE::newVec2(config->size.x, config->size.x - 2 * size)
        ),
        ARE::newRGBA(255, 255, 255, 255),
        false
    );

    struct ARE::PixelRect rect = ARE::newPixelRect(
        ARE::newRect2(
            ARE::newVec2(config->size.x / 2, config->size.y / 2),
            ARE::newVec2(50, 100),
            angle
        ),
        ARE::newRGBA(255, 0, 0, 255),
        false
    );

    struct ARE::PixelCurve curve = ARE::newPixelCurve(
        ARE::newCurve2(
            ARE::newVec2(config->size.x / 2, config->size.y / 2),
            size,
            angle * 4, M_PI / 3
        ),
        ARE::newRGBA(0, 255, 0, 255),
        false
    );

    struct ARE::PixelParabola parabola = ARE::newPixelParabola(
        ARE::newParabola2(
            ARE::newVec2(config->size.x / 2, config->size.y / 2),
            std::vector<float>({0, 0, 0, static_cast<float>(
                0.1 / 7 / size
            )}),
            ARE::newVec2(config->size.x / 4, config->size.y),
            ARE::newVec2(-config->size.x / 4, 0)
        ),
        ARE::newRGBA(255, 255, 0, 255),
        false
    );

    struct ARE::PixelTrig trig = ARE::newPixelTrig(
        ARE::newTrig2(
            ARE::newVec2(config->size.x / 2, config->size.x / 4 * 3),
            ARE::TrigType::SIN,
            5,
            config->size.x / 2, -config->size.y / 2
        ),
        ARE::newRGBA(255, 255, 255, 255)
    );

    while(running) {
        (void)ARE::log(
            ARE::AddBenchmarkMilestone(&benchmark)
        );

        // Rendering

        ARE::ClearScreen(config);

        line.geometry = ARE::newLine2(
            ARE::newVec2(0, 2 * size),
            ARE::newVec2(config->size.x, config->size.x - 2 * size)
        );

        ARE::RenderPixelLine(config, &line);

        rect.geometry.angle = angle;

        ARE::RenderPixelRect(config, &rect);

        curve.geometry = ARE::newCurve2(
            ARE::newVec2(config->size.x / 2, config->size.y / 2),
            size,
            angle * 4, M_PI / 3
        );

        ARE::RenderPixelCurve(config, &curve);

        parabola.geometry.coefficients = std::vector<float>(
            { 0, 0, 0, static_cast<float>(
                0.1 / 7 / size
            )}
        );

        ARE::RenderPixelParabola(config, &parabola);

        ARE::RenderPixelTrig(config, &trig);

        size += up ? 1 : -1;
        if(size == config->size.x / 2) {
            up = false;
        } else if(size == 1) {
            up = true;
        }

        angle += M_PI / 1000;

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

    ARE::ShowBenchmarkStats(benchmark);

    SDL_DestroyRenderer(config->sdl.renderer);
    SDL_DestroyWindow(config->sdl.window);

    return ARE::newReturnCode();
}
