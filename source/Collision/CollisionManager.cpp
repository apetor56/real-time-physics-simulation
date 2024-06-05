#include "CollisionManager.hpp"

namespace RTPS {

void CollisionManager::update( float deltaTime ) {
    handleCollision();
}

void CollisionManager::addCollidable( Shape& shape ) {
    m_collidable.push_back( &shape );
}

void CollisionManager::handleCollision() {
    const size_t collidableCount{ std::size( m_collidable ) };
    for ( size_t firstIndex{}; firstIndex < collidableCount; firstIndex++ ) {
        for ( size_t secondIndex{}; secondIndex < collidableCount; secondIndex++ ) {
            if ( firstIndex == secondIndex )
                continue;

            if ( m_collisionDetector.isColliding( *m_collidable.at( firstIndex ), *m_collidable.at( secondIndex ) ) )
                m_collidable.at( firstIndex )->onCollision();
        }
    }
}

} // namespace RTPS
