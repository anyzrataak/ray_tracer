/**
 * @file    main.cpp
 * @brief   File with executable function main.
 * @author  Katarzyna Pi¹tek
 * @date    2026-05-31
 */

#include <exception>
#include "Setup.h"

int main() {
    try {
        // Initializes and runs the application.
        Setup app;
        app.run();
    }
    catch (const std::exception& e) {
        // Catching exception from all over the project.
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}