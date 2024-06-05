#pragma once

#include "CollisionDetector.hpp"
#include "Shape.hpp"

namespace RTPS {

class CollisionManager {
public:
    void update( float deltaTime );

    void addCollidable( Shape& shape );

private:
    CollisionDetector m_collisionDetector;
    std::vector< Shape * > m_collidable;

    void handleCollision();
};

} // namespace RTPS
