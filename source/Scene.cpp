#include "Scene.hpp"
#include "InputHandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <ranges>
#include <algorithm>

namespace RTPS {

Scene::Scene() {
    loadShapes();
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
}

void Scene::render( sf::RenderWindow& window ) const {
    std::ranges::for_each( m_shapes, [ &window ]( const auto& shape ) {
        if ( shape.has_value() )
            shape.value().render( window );
    } );
}

void Scene::loadShapes() {
    const std::vector< sf::Vector2f > firstTriangleVertices{ sf::Vector2f{ 100, 300 }, { 400, 150 }, { 200, 140 } };
    const std::vector< sf::Vector2f > secondTriangleVertices{ sf::Vector2f{ 300, 400 }, { 600, 500 }, { 300, 300 } };

    m_shapes.emplace_back( Shape( firstTriangleVertices ) );
    m_shapes.emplace_back( Shape( secondTriangleVertices ) );

    m_shapes.at( 0 )->setControlled( true );
    m_shapes.at( 0 )->setFillColor( sf::Color{ 0, 255, 0 } );
    m_shapes.at( 1 )->setFillColor( sf::Color{ 0, 0, 255 } );
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