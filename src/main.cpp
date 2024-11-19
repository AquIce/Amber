#include <Amber/Amber.hpp>

#include <iostream>

class SandboxApp : public Amber::App {
public:
    SandboxApp() {}
    ~SandboxApp() {}
};

Amber::App* Amber::CreateApp() {
    return new SandboxApp();
}
