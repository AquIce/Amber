#include <ARE/ARE.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

int WinMain(int argc, char** argv) {

    struct ARE::Config config = ARE::newConfig(
        "ARE",
        ARE::newVec2(1200, 640)
    );

    ARE::ReturnCode status = ARE::Init(&config);
    if(status.isExitCode) {
        return static_cast<int>(status.exitCode);
    }

    (void)ARE::AddEventHandler(&config, {
        SDL_QUIT,
        [] (bool* running) -> void {
            *running = false;
        }
    });

    (void)ARE::Run(&config);

    return 0;
}
