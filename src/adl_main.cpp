#include <ARE/ARE.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <iostream>

int WinMain(int argc, char** argv) {

    struct ARE::Config config = ARE::newConfig(
        "ARE",
        ARE::newVec2(480, 480)
    );

    ARE::ExitCode status = ARE::Init(&config);
    if(status != ARE::ExitCode::ADL_SUCCESS) {
        return static_cast<int>(status);
    }

    FORCE_DISCARD ARE::AddEventHandler(&config, {
        SDL_QUIT,
        [] (bool* running) -> void {
            *running = false;
        }
    });

    (void)ARE::Run(&config);

    return 0;
}
