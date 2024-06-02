#include "Application.hpp"
#include <iostream>

int main() {
    RTPS::Application application{ RTPS::WindowConfig{ 800, 600, "Collision Detection" } };
    application.init();

    try {
        application.run();
    }
    catch ( std::exception& e ) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}