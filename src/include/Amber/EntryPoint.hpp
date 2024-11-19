#pragma once

extern Amber::App* Amber::CreateApp();

int WinMain(int argc, char** argv) {
    Amber::App* app = Amber::CreateApp();
    if(app == nullptr) {
        return -1;
    }

    app->Run();
    delete app;

    return 0;
}
