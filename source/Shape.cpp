#include "Shape.hpp"

using namespace std::chrono;

namespace RTPS {

Shape::Shape( const std::vector< sf::Vector2f >& vertices ) {
    const size_t pointsCount{ std::size( vertices ) };

    setPointCount( pointsCount );
    for ( size_t vertexIndex{ 0ull }; vertexIndex < pointsCount; vertexIndex++ ) {
        setPoint( vertexIndex, vertices.at( vertexIndex ) );
    }
}

} // namespace RTPS