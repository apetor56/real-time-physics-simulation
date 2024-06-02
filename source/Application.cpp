#include "Application.hpp"
#include <iostream>

#include <ranges>

using namespace std::chrono;

inline sf::Vector2f velocity{};
inline constexpr float velocityBase{ 0.5f };

namespace RTPS {

Application::Application( const WindowConfig& windowConfig )
    : m_window{ sf::VideoMode{ sf::Vector2u{ windowConfig.width, windowConfig.height } }, windowConfig.name } {}

void Application::init() {
    m_window.setFramerateLimit( 60u );
    const std::vector< sf::Vector2f > firstTriangleVertices{ sf::Vector2f{ 100, 300 }, { 400, 150 }, { 200, 140 } };
    const std::vector< sf::Vector2f > secondTriangleVertices{ sf::Vector2f{ 300, 400 }, { 600, 500 }, { 300, 300 } };

    m_shapes.emplace_back( Shape( firstTriangleVertices ) );
    m_shapes.emplace_back( Shape( secondTriangleVertices ) );

    m_shapes.at( 0 )->setFillColor( sf::Color{ 0, 255, 0 } );
    m_shapes.at( 1 )->setFillColor( sf::Color{ 0, 0, 255 } );
}

void Application::run() {
    auto lastTime{ high_resolution_clock::now() };
    decltype( lastTime ) currentTime;
    milliseconds delta;

    while ( m_window.isOpen() ) {
        currentTime = high_resolution_clock::now();
        delta       = duration_cast< milliseconds >( currentTime - lastTime );

        update( delta.count() );
        render();

        lastTime = currentTime;
    }
}

void Application::update( double deltaTime ) {
    sf::Event event;
    while ( event = m_window.pollEvent() ) {
        if ( event.is< sf::Event::Closed >() )
            m_window.close();
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::W ) ) {
        velocity = static_cast< float >( deltaTime ) * sf::Vector2f{ 0, -velocityBase };
        m_shapes.at( m_currentShapeIndex )->move( velocity );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::S ) ) {
        velocity = static_cast< float >( deltaTime ) * sf::Vector2f{ 0, velocityBase };
        m_shapes.at( m_currentShapeIndex )->move( velocity );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::A ) ) {
        velocity = static_cast< float >( deltaTime ) * sf::Vector2f{ -velocityBase, 0 };
        m_shapes.at( m_currentShapeIndex )->move( velocity );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::D ) ) {
        velocity = static_cast< float >( deltaTime ) * sf::Vector2f{ velocityBase, 0 };
        m_shapes.at( m_currentShapeIndex )->move( velocity );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Tab ) ) {
        m_currentShapeIndex = ( m_currentShapeIndex + 1 ) % std::size( m_shapes );
    }
}

void Application::render() {
    m_window.clear( sf::Color::Black );
    std::ranges::for_each( m_shapes, [ this ]( const auto& shape ) { m_window.draw( *shape ); } );
    m_window.display();
}

} // namespace RTPS