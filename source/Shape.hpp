#pragma once

#include <SFML/Graphics/ConvexShape.hpp>

#include <vector>
#include <chrono>

namespace RTPS {

struct Shape : public sf::ConvexShape {
public:
    Shape( const std::vector< sf::Vector2f >& vertices );

private:
    sf::Vector2f m_velocity{};
    inline static sf::Vector2f m_baseVelocity{ 10.0f, 10.0f };
};

} // namespace RTPS