#include "Application.hpp"
#include "Config.hpp"

#include <iostream>

using namespace RTPS;

int main() {
    RTPS::Application application{
        RTPS::WindowConfig{ config::window::width, config::window::height, config::window::name } };

    application.init();

    try {
        application.run();
    }
    catch ( std::exception& e ) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
