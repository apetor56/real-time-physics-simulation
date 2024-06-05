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
    Shape( const std::vector< sf::Vector2f >& vertices, const sf::Color& color );

    void processInput( const InputHandler& inputHandler );
    void update( float deltaTime );
    void render( sf::RenderWindow& window ) const;

    void move( const sf::Vector2f& offset );

    // only color changing, no need for collision info
    void onCollision();

    void setControlled( bool controllFlag );
    bool isControlled() const;
    void printPositions();
    std::vector< sf::Vector2f > getVertices() const;

private:
    std::vector< sf::Vector2f > m_vertices{};
    sf::Color m_color{};
    sf::Vector2f m_velocity{};
    bool m_isControlled{ false };
};

using Shapes = std::vector< std::optional< RTPS::Shape > >;

} // namespace RTPS
