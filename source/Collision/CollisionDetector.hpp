#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

namespace RTPS {

struct Shape;

class CollisionDetector {
public:
    bool isColliding( const Shape& first, const Shape& second ) const;

private:
    bool sat( const Shape& first, const Shape& second ) const;
};

} // namespace RTPS
