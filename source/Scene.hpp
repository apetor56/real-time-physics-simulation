#pragma once

#include "Shape.hpp"
#include "Collision/CollisionManager.hpp"

namespace sf {
class RenderWindow;
}

namespace RTPS {

class InputHandler;

class Scene {
public:
    Scene();
    void processInput( const InputHandler& inputHandler );
    void update( float deltaTime );
    void render( sf::RenderWindow& window ) const;

private:
    RTPS::Shapes m_shapes;
    RTPS::CollisionManager m_collisionManager{};

    void loadShapes();
    void processShapeSwitch( const InputHandler& inputHandler );
};

} // namespace RTPS
