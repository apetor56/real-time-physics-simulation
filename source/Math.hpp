#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace RTPS {

namespace Math {

float dot( sf::Vector2f first, sf::Vector2f second );

float length( sf::Vector2f vector );

sf::Vector2f normalize( sf::Vector2f vector );

sf::Vector2f getNormal( sf::Vector2f vector );

float projection( sf::Vector2f point, sf::Vector2f axis );

sf::Vector2f getVectorFromPoints( sf::Vector2f firstPoint, sf::Vector2f secondPoint );

std::vector< sf::Vector2f > getSideVectors( const std::vector< sf::Vector2f >& vertices );

std::vector< sf::Vector2f > getShapeNormals( const std::vector< sf::Vector2f >& shapeVectors );

bool isOverllaping( float firstMin, float firstMax, float secondMin, float secondMax );

} // namespace Math

} // namespace RTPS
