#pragma once

#include <SFML/Graphics/ConvexShape.hpp>

#include <vector>

namespace sf {
class RenderWindow;
}

namespace RTPS {

class InputHandler;

struct Shape : public sf::ConvexShape {
public:
    Shape( const std::vector< sf::Vector2f >& vertices );

    void processInput( const InputHandler& inputHandler );
    void update( float deltaTime );
    void render( sf::RenderWindow& window ) const;

    sf::Vector2f getPoint( size_t index ) const;
    void move( const sf::Vector2f& offset );

    void setControlled( bool controllFlag );
    bool isControlled() const;
    void printPositions();

private:
    std::vector< sf::Vector2f > m_vertices{};
    sf::Vector2f m_velocity{};
    bool m_isControlled{ false };
};

using Shapes = std::vector< std::optional< RTPS::Shape > >;

} // namespace RTPS
