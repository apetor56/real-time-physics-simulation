#include "CollisionDetector.hpp"
#include "Shape.hpp"

#include <ranges>
#include <algorithm>
#include <limits>
#include "Math.hpp"

namespace RTPS {

bool CollisionDetector::isColliding( const Shape& first, const Shape& second ) const {
    return sat( first, second );
}

bool CollisionDetector::sat( const Shape& first, const Shape& second ) const {
    const auto firstVertices{ first.getVertices() };
    const auto secondVertices{ second.getVertices() };
    const auto& firstSideVectors{ Math::getSideVectors( firstVertices ) };
    const auto& secondSideVectors{ Math::getSideVectors( secondVertices ) };

    auto axes{ Math::getShapeNormals( firstSideVectors ) };
    const auto secondNormals{ Math::getShapeNormals( secondSideVectors ) };
    axes.insert( std::end( axes ), std::begin( secondNormals ), std::end( secondNormals ) );

    for ( const auto& axis : axes ) {
        std::vector< float > firstProjections{};
        std::vector< float > secondProjections{};

        std::ranges::for_each( firstVertices, [ &axis, &firstProjections ]( const auto& vertex ) {
            firstProjections.push_back( Math::projection( vertex, axis ) );
        } );

        std::ranges::for_each( secondVertices, [ &axis, &secondProjections ]( const auto& vertex ) {
            secondProjections.push_back( Math::projection( vertex, axis ) );
        } );

        auto [ firstMin,
               firstMax ]{ std::minmax_element( std::begin( firstProjections ), std::end( firstProjections ) ) };
        auto [ secondMin,
               secondMax ]{ std::minmax_element( std::begin( secondProjections ), std::end( secondProjections ) ) };

        if ( !Math::isOverllaping( *firstMin, *firstMax, *secondMin, *secondMax ) )
            return false;
    }

    return true;
}

} // namespace RTPS
