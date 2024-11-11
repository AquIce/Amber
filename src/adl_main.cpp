#include <ADL/ADL.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <iostream>

int WinMain(int argc, char** argv) {

    struct ADL::Config config = ADL::newConfig(
        "ADL",
        ADL::newVec2(480, 480)
    );

    ADL::ExitCode status = ADL::Init(&config);
    if(status != ADL::ExitCode::ADL_SUCCESS) {
        return static_cast<int>(status);
    }

    FORCE_DISCARD ADL::AddEventHandler(&config, {
        SDL_QUIT,
        [] (bool* running) -> void {
            *running = false;
        }
    });

    (void)ADL::Run(&config);

    return 0;
}
