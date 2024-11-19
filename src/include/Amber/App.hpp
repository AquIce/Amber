#pragma once

namespace Amber {

    class App {
    public:
        App();
        virtual ~App();

        void Run();
    };

    App* CreateApp();
}
