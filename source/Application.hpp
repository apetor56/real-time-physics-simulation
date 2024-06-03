#pragma once

#include "Shape.hpp"
#include "InputHandler.hpp"

#include "SFML/Graphics.hpp"

namespace RTPS {

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
    RTPS::InputHandler m_inputHandler{};
    size_t m_currentShapeIndex{};

    void loadObjects();

    void processInput();
    void update( float deltaTime );
    void render();

    void processWindowEvents();
    void processShapeSwitch();
};

} // namespace RTPS
