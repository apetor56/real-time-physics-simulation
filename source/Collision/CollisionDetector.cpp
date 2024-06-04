#include "CollisionDetector.hpp"
#include "Shape.hpp"

#include <ranges>
#include <algorithm>

namespace RTPS {

bool CollisionDetector::checkCollision( const Shape& first, const Shape& second ) const {
    return sat( first, second );
}

bool CollisionDetector::sat( const Shape& first, const Shape& second ) const {
    const auto normalAxes{ getAxes( getAllShapeSides( first, second ) ) };

    float minA{}, minB{};
    float maxA{}, maxB{};

    for ( const auto& axe : normalAxes ) {
        const auto projectionsA{ getPointsProjection( first, axe ) };
        const auto projectionsB{ getPointsProjection( second, axe ) };

        minA = *std::min_element( std::begin( projectionsA ), std::end( projectionsA ) );
        minB = *std::min_element( std::begin( projectionsB ), std::end( projectionsB ) );
        maxA = *std::max_element( std::begin( projectionsA ), std::end( projectionsA ) );
        maxB = *std::max_element( std::begin( projectionsB ), std::end( projectionsB ) );

        if ( !isOverllaping( minA, minB, maxA, maxB ) )
            return false;
    }

    return true;
}

inline sf::Vector2f CollisionDetector::getNormalVector( sf::Vector2f vector ) const {
    return sf::Vector2f{ vector.y, -vector.x }.normalized();
}

std::vector< sf::Vector2f > CollisionDetector::getShapeSidesAsVectors( const Shape& shape ) const {
    std::vector< sf::Vector2f > vectors{};
    sf::Vector2f firstPoint{}, secondPoint{};

    for ( size_t pointIndex{ 1ull }; pointIndex <= shape.getPointCount(); pointIndex++ ) {
        firstPoint  = shape.getPoint( pointIndex - 1 );
        secondPoint = shape.getPoint( pointIndex % shape.getPointCount() );
        auto sideVector{ secondPoint - firstPoint };
        sideVector.y *= -1.0f; // due to sfml window coordinates
        vectors.emplace_back( sideVector );
    }

    return vectors;
}

std::vector< sf::Vector2f > CollisionDetector::getAllShapeSides( const Shape& first, const Shape& second ) const {
    const auto firstShapeVectors{ getShapeSidesAsVectors( first ) };
    const auto secondShapeVectors{ getShapeSidesAsVectors( second ) };

    std::vector< sf::Vector2f > allShapesVectors{ std::begin( firstShapeVectors ), std::end( firstShapeVectors ) };
    allShapesVectors.insert( std::end( allShapesVectors ), std::begin( secondShapeVectors ),
                             std::end( secondShapeVectors ) );

    return allShapesVectors;
}

std::vector< sf::Vector2f > CollisionDetector::getAxes( const std::vector< sf::Vector2f >& shapeVectors ) const {
    std::vector< sf::Vector2f > axes{};

    std::ranges::for_each( shapeVectors, [ this, &axes ]( const auto shapeVector ) {
        axes.emplace_back( getNormalVector( shapeVector ) );
    } );

    return axes;
}

std::vector< float > CollisionDetector::getPointsProjection( const Shape& shape, sf::Vector2f axe ) const {
    std::vector< float > projections{};
    for ( size_t pointIndex{}; pointIndex < shape.getPointCount(); pointIndex++ ) {
        projections.emplace_back( shape.getPoint( pointIndex ).dot( axe ) );
    }

    return projections;
}

bool CollisionDetector::isOverllaping( float minA, float minB, float maxA, float maxB ) const {
    float ultimateMax{ std::max( maxA, maxB ) };
    float ultimateMin( std::min( minA, minB ) );
    static constexpr float epsilon{ 0.0f };
    return ( maxA - minA ) + ( maxB - minB ) - epsilon > ( ultimateMax - ultimateMin );
}

} // namespace RTPS