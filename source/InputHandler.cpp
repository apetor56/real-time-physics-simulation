#include "InputHandler.hpp"

namespace RTPS {

bool InputHandler::isPressed( sf::Keyboard::Key key ) const noexcept {
    return sf::Keyboard::isKeyPressed( key );
}

} // namespace RTPS
