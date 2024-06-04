#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

namespace RTPS {

class Shape;

class CollisionDetector {
public:
    bool checkCollision( const Shape& first, const Shape& second ) const;

private:
    bool sat( const Shape& first, const Shape& second ) const;

    inline sf::Vector2f getNormalVector( sf::Vector2f vector ) const;
    std::vector< sf::Vector2f > getShapeSidesAsVectors( const Shape& shape ) const;
    std::vector< sf::Vector2f > getAllShapeSides( const Shape& first, const Shape& second ) const;
    std::vector< sf::Vector2f > getAxes( const std::vector< sf::Vector2f >& shapeVectors ) const;
    std::vector< float > getPointsProjection( const Shape& shape, sf::Vector2f axe ) const;
    bool isOverllaping( float minA, float minB, float maxA, float maxB ) const;
};

} // namespace RTPS