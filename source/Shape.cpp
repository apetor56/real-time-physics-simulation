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

    const auto& inputs{ inputHandler.getInputTypes() };
    for ( const auto& inputType : inputs ) {
        switch ( inputType ) {
        case RTPS::InputType::MoveUp:
            m_velocity.y = -s_speed;
            break;
        case RTPS::InputType::MoveDown:
            m_velocity.y = s_speed;
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
