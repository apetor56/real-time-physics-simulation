#include "Math.hpp"

#include <ranges>
#include <algorithm>
#include <cmath>

namespace RTPS {

namespace Math {

float dot( sf::Vector2f first, sf::Vector2f second ) {
    return first.x * second.x + first.y * second.y;
}

float length( sf::Vector2f vector ) {
    return static_cast< float >( sqrt( dot( vector, vector ) ) );
}

sf::Vector2f normalize( sf::Vector2f vector ) {
    return vector / length( vector );
}

sf::Vector2f getNormal( sf::Vector2f vector ) {
    return { vector.y, -vector.x };
}

float projection( sf::Vector2f point, sf::Vector2f axis ) {
    return dot( point, Math::normalize( axis ) );
}

sf::Vector2f getVectorFromPoints( sf::Vector2f firstPoint, sf::Vector2f secondPoint ) {
    return secondPoint - firstPoint;
}

std::vector< sf::Vector2f > getSideVectors( const std::vector< sf::Vector2f >& vertices ) {
    std::vector< sf::Vector2f > vectors{};
    for ( auto pointIt{ std::begin( vertices ) }; pointIt != std::end( vertices ); pointIt++ ) {
        auto nextPointIt{ std::next( pointIt ) };
        if ( nextPointIt == std::end( vertices ) )
            nextPointIt = std::begin( vertices );

        vectors.emplace_back( *nextPointIt - *pointIt );
    }

    return vectors;
}

std::vector< sf::Vector2f > getShapeNormals( const std::vector< sf::Vector2f >& shapeVectors ) {
    std::vector< sf::Vector2f > normals{};
    std::ranges::for_each( shapeVectors,
                           [ &normals ]( const auto vector ) { normals.emplace_back( Math::getNormal( vector ) ); } );

    return normals;
}

bool isOverllaping( float firstMin, float firstMax, float secondMin, float secondMax ) {
    float globalMax{ std::max( firstMax, secondMax ) };
    float globalMin( std::min( firstMin, secondMin ) );
    return ( firstMax - firstMin ) + ( secondMax - secondMin ) > ( globalMax - globalMin );
}

} // namespace Math

} // namespace RTPS
