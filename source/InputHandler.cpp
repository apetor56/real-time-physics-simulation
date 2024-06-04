#include "InputHandler.hpp"

#include <ranges>
#include <algorithm>

namespace RTPS {

void InputHandler::update( float deltaTime ) {
    clearPreviousInputs();
    addCurrentInputs();
}

void InputHandler::clearPreviousInputs() {
    m_inputTypes.clear();
}

const std::unordered_set< InputType >& InputHandler::getInputTypes() const noexcept {
    return m_inputTypes;
}

void InputHandler::addCurrentInputs() {
    std::ranges::for_each( m_inputMap, [ this ]( const auto& pair ) {
        auto& [ key, inputType ] = pair;
        if ( sf::Keyboard::isKeyPressed( key ) )
            m_inputTypes.insert( inputType );
    } );
}

} // namespace RTPS
