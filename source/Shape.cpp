#include "Shape.hpp"
#include "InputHandler.hpp"
#include "Config.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <ranges>
#include <algorithm>
#include <iostream>
#include <format>

using namespace std::chrono;

namespace RTPS {

static constexpr float s_speed{ 300.0f };
static constexpr sf::Vector2f s_zeroVelocity{};

Shape::Shape( const std::vector< sf::Vector2f >& vertices, const sf::Color& color ) : m_color{ color } {
    setFillColor( m_color );
    m_vertices.resize( std::size( vertices ) );
    for ( size_t vertexIndex{}; vertexIndex < std::size( vertices ); vertexIndex++ ) {
        m_vertices.at( vertexIndex ).x = vertices.at( vertexIndex ).x;
        m_vertices.at( vertexIndex ).x = vertices.at( vertexIndex ).x;
        m_vertices.at( vertexIndex ).y = vertices.at( vertexIndex ).y;
        m_vertices.at( vertexIndex ).y = vertices.at( vertexIndex ).y;
    }
    const size_t pointsCount{ std::size( vertices ) };

    setPointCount( pointsCount );
    sf::Vector2f correntedPosition{};
    for ( size_t vertexIndex{ 0ull }; vertexIndex < pointsCount; vertexIndex++ ) {
        correntedPosition = vertices.at( vertexIndex );
        correntedPosition.y =
            config::window::height - correntedPosition.y; // y axis in SFML is an opposite to cartesian y axis

        setPoint( vertexIndex, correntedPosition );
    }
}

void Shape::processInput( const InputHandler& inputHandler ) {
    if ( !m_isControlled )
        return;

    const auto& inputs{ inputHandler.getInputTypes() };
    for ( const auto& inputType : inputs ) {
        switch ( inputType ) {
        case RTPS::InputType::MoveUp:
            m_velocity.y = s_speed;
            break;
        case RTPS::InputType::MoveDown:
            m_velocity.y = -s_speed;
            break;
        case RTPS::InputType::MoveLeft:
            m_velocity.x = -s_speed;
            break;
        case RTPS::InputType::MoveRight:
            m_velocity.x = s_speed;
            break;
        default:
            break;
        }
    }
}

void Shape::update( float deltaTime ) {
    setFillColor( m_color );

    if ( m_velocity != s_zeroVelocity ) {
        move( deltaTime * m_velocity );
        m_velocity = s_zeroVelocity;
    }
}

void Shape::render( sf::RenderWindow& window ) const {
    window.draw( *this );
}

void Shape::move( const sf::Vector2f& offset ) {
    sf::Transformable::move( { offset.x, -offset.y } ); // y axis in SFML is an opposite to y cartesian axis
    std::ranges::for_each( m_vertices, [ &offset ]( auto& vertex ) { vertex += offset; } );
}

void Shape::onCollision() {
    setFillColor( sf::Color::Red );
}

void Shape::setControlled( bool controllFlag ) {
    m_isControlled = controllFlag;
}

bool Shape::isControlled() const {
    return m_isControlled;
}

void Shape::printPositions() {
    std::ranges::for_each( m_vertices,
                           []( const auto vertex ) { std::cout << std::format( "({},{}) ", vertex.x, vertex.y ); } );
    std::cout << '\n';
}

std::vector< sf::Vector2f > Shape::getVertices() const {
    return m_vertices;
}

} // namespace RTPS
