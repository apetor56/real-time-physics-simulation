#include "Application.hpp"

#include <ranges>
#include <algorithm>

namespace RTPS {

Application::Application( const WindowConfig& windowConfig )
    : m_window{ sf::VideoMode{ sf::Vector2u{ windowConfig.width, windowConfig.height } }, windowConfig.name } {}

void Application::init() {
    m_window.setFramerateLimit( 60u );
    loadObjects();
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

void Application::loadObjects() {
    const std::vector< sf::Vector2f > firstTriangleVertices{ sf::Vector2f{ 100, 300 }, { 400, 150 }, { 200, 140 } };
    const std::vector< sf::Vector2f > secondTriangleVertices{ sf::Vector2f{ 300, 400 }, { 600, 500 }, { 300, 300 } };

    m_shapes.emplace_back( Shape( firstTriangleVertices ) );
    m_shapes.emplace_back( Shape( secondTriangleVertices ) );

    m_shapes.at( 0 )->setControlled( true );
    m_shapes.at( 0 )->setFillColor( sf::Color{ 0, 255, 0 } );
    m_shapes.at( 1 )->setFillColor( sf::Color{ 0, 0, 255 } );
}

void Application::processInput() {
    processWindowEvents();
    processShapeSwitch();
    std::ranges::for_each( m_shapes, [ this ]( auto& shape ) { shape.value().processInput( m_inputHandler ); } );
}

void Application::update( float deltaTime ) {
    std::ranges::for_each( m_shapes, [ deltaTime ]( auto& shape ) { shape.value().update( deltaTime ); } );
}

void Application::render() {
    m_window.clear( sf::Color::Black );
    std::ranges::for_each( m_shapes, [ this ]( const auto& shape ) { shape.value().render( m_window ); } );
    m_window.display();
}

void Application::processShapeSwitch() {
    if ( !m_inputHandler.isPressed( sf::Keyboard::Key::Tab ) )
        return;

    auto controlledShape{
        std::ranges::find_if( m_shapes, []( const auto& shape ) { return shape.value().isControlled(); } ) };

    std::ranges::for_each( m_shapes, []( auto& shape ) { shape.value().setControlled( false ); } );

    if ( controlledShape != std::end( m_shapes ) ) {
        auto nextShape{ std::next( controlledShape ) };
        if ( nextShape == std::end( m_shapes ) ) {
            nextShape = std::begin( m_shapes );
        }
        nextShape->value().setControlled( true );
    }
}

void Application::processWindowEvents() {
    static sf::Event event;
    while ( event = m_window.pollEvent() ) {
        if ( event.is< sf::Event::Closed >() )
            m_window.close();
    }
}

} // namespace RTPS
