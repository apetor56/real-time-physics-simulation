#include "Scene.hpp"
#include "InputHandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <ranges>
#include <algorithm>
#include <iostream>

#include "Math.hpp"

namespace RTPS {

Scene::Scene() {
    loadShapes();

    std::ranges::for_each( m_shapes, [ this ]( auto& shape ) { m_collisionManager.addCollidable( shape.value() ); } );
}

void Scene::processInput( const InputHandler& inputHandler ) {
    std::ranges::for_each( m_shapes, [ &inputHandler ]( auto& shape ) { shape.value().processInput( inputHandler ); } );
    processShapeSwitch( inputHandler );
}

void Scene::update( float deltaTime ) {
    std::ranges::for_each( m_shapes, [ deltaTime ]( auto& shape ) {
        if ( shape.has_value() )
            shape.value().update( deltaTime );
    } );

    m_collisionManager.update( deltaTime );
}

void Scene::render( sf::RenderWindow& window ) const {
    std::ranges::for_each( m_shapes, [ &window ]( const auto& shape ) {
        if ( shape.has_value() )
            shape.value().render( window );
    } );
}

void Scene::loadShapes() {
    const std::vector< sf::Vector2f > triangle{ sf::Vector2f{ 550, 20 }, { 570, 200 }, { 900, 250 } };
    const std::vector< sf::Vector2f > rectangle{ sf::Vector2f{ 100, 200 }, { 300, 200 }, { 300, 500 }, { 100, 500 } };
    const std::vector< sf::Vector2f > concave{
        sf::Vector2f{ 500, 300 }, { 700, 330 }, { 800, 480 }, { 600, 370 }, { 520, 450 } };
    const std::vector< sf::Vector2f > custom{ sf::Vector2f{ 700, 550 }, { 900, 550 }, { 1000, 750 }, { 800, 750 } };

    m_shapes.emplace_back( Shape( triangle, sf::Color::Cyan ) );
    m_shapes.emplace_back( Shape( rectangle, sf::Color::Magenta ) );
    m_shapes.emplace_back( Shape( concave, sf::Color::Green ) );
    m_shapes.emplace_back( Shape( custom, sf::Color::Blue ) );

    m_shapes.at( 0 )->setControlled( true );
}

void Scene::processShapeSwitch( const InputHandler& inputHandler ) {
    const auto& inputs{ inputHandler.getInputTypes() };

    for ( const auto& inputType : inputs ) {
        switch ( inputType ) {
        case RTPS::InputType::ChangeObject: {
            auto controlledShape{
                std::ranges::find_if( m_shapes, []( const auto& shape ) { return shape.value().isControlled(); } ) };

            std::ranges::for_each( m_shapes, []( auto& shape ) { shape.value().setControlled( false ); } );

            if ( controlledShape != std::end( m_shapes ) ) {
                auto nextShape{ std::next( controlledShape ) };
                if ( nextShape == std::end( m_shapes ) ) {
                    nextShape = std::begin( m_shapes );
                }
                nextShape->value().setControlled( true );
            }
            break;
        }

        default:
            break;
        }
    }
}

} // namespace RTPS
