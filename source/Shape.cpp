#include "Shape.hpp"
#include "InputHandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

using namespace std::chrono;

namespace RTPS {

static constexpr float s_speed{ 300.0f };
static constexpr sf::Vector2f s_zeroVelocity{};

Shape::Shape( const std::vector< sf::Vector2f >& vertices ) {
    const size_t pointsCount{ std::size( vertices ) };

    setPointCount( pointsCount );
    for ( size_t vertexIndex{ 0ull }; vertexIndex < pointsCount; vertexIndex++ ) {
        setPoint( vertexIndex, vertices.at( vertexIndex ) );
    }
}

void Shape::processInput( const InputHandler& inputHandler ) {
    if ( !m_isControlled )
        return;

    if ( inputHandler.isPressed( sf::Keyboard::Key::W ) )
        m_velocity.y = -s_speed;
    if ( inputHandler.isPressed( sf::Keyboard::Key::S ) )
        m_velocity.y = s_speed;
    if ( inputHandler.isPressed( sf::Keyboard::Key::A ) )
        m_velocity.x = -s_speed;
    if ( inputHandler.isPressed( sf::Keyboard::Key::D ) )
        m_velocity.x = s_speed;
}

void Shape::update( float deltaTime ) {
    if ( m_velocity != s_zeroVelocity ) {
        move( deltaTime * m_velocity );
        m_velocity = s_zeroVelocity;
    }
}

void Shape::render( sf::RenderWindow& window ) const {
    window.draw( *this );
}

void Shape::setControlled( bool controllFlag ) {
    m_isControlled = controllFlag;
}

bool Shape::isControlled() const {
    return m_isControlled;
}

} // namespace RTPS
