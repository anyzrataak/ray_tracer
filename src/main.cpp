/**
 * @mainpage Ray Tracer Project
 *
 * @section intro_sec Project Description
 * A C++ 3D scene renderer utilizing the Ray Tracing technique.
 * The application supports geometric primitives such as Axis-Aligned Bounding Boxes, along with various surface materials including Lambertian, Metal, and Dielectric.
 *
 * @section usage_sec Example Usage
 * The program initializes and manages the application loop through the Setup class.
 * It runs out of the box without requiring additional command-line arguments.
 *
 * @code
 * int main() {
 * Setup app;
 * app.run();
 * return 0;
 * }
 * @endcode
 *
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#include <exception>
#include "Setup.h"

int main() {
    std::cout << "\033]0;Ray Tracer\007";

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