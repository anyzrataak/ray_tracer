#include <SDL3/SDL.h>
#include <exception>
#include "Setup.h"

int main() {
    try {
        Setup app;
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}