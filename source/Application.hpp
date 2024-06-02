#pragma once

#include "Shape.hpp"

#include "SFML/Graphics.hpp"

#include <chrono>
#include <vector>
#include <memory>

namespace RTPS {

using Shapes = std::vector< std::optional< RTPS::Shape > >;

struct WindowConfig {
    const uint32_t width;
    const uint32_t height;
    const std::string name;
};

class Application final {
public:
    Application( const WindowConfig& windowConfig );

    Application( const Application& other ) = delete;
    Application( Application&& other )      = delete;

    Application& operator=( const Application& other ) = delete;
    Application& operator=( Application&& other )      = delete;

    void init();
    void run();

private:
    sf::RenderWindow m_window;
    RTPS::Shapes m_shapes;
    size_t m_currentShapeIndex{};

    void update( double deltaTime );
    void render();
};

} // namespace RTPS