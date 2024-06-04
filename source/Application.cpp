#include "Application.hpp"

#include <ranges>
#include <algorithm>

namespace RTPS {

Application::Application( const WindowConfig& windowConfig )
    : m_window{ sf::VideoMode{ sf::Vector2u{ windowConfig.width, windowConfig.height } }, windowConfig.name } {}

void Application::init() {
    m_window.setFramerateLimit( 60u );
}

void Application::run() {
    using namespace std::chrono;
    auto lastTime{ high_resolution_clock::now() };
    decltype( lastTime ) currentTime;
    float delta;

    while ( m_window.isOpen() ) {
        currentTime = high_resolution_clock::now();
        delta       = duration< float >( currentTime - lastTime ).count();

        processInput();
        update( delta );
        render();

        lastTime = currentTime;
    }
}

void Application::processInput() {
    processWindowEvents();
    m_scene.processInput( m_inputHandler );
}

void Application::update( float deltaTime ) {
    m_inputHandler.update( deltaTime );
    m_scene.update( deltaTime );
}

void Application::render() {
    m_window.clear( sf::Color::Black );
    m_scene.render( m_window );
    m_window.display();
}

void Application::processWindowEvents() {
    static sf::Event event;
    while ( event = m_window.pollEvent() ) {
        if ( event.is< sf::Event::Closed >() )
            m_window.close();
    }
}

} // namespace RTPS
