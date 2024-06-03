#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>
#include <optional>

namespace RTPS {

enum class InputType : int { MoveUp, MoveDown, MoveLeft, MoveRight, ChangeObject };

class InputHandler {
public:
    bool isPressed( sf::Keyboard::Key key ) const noexcept;

private:
    const std::unordered_multimap< sf::Keyboard::Key, InputType > m_inputMap{
        { sf::Keyboard::Key::W, InputType::MoveUp },
        { sf::Keyboard::Key::S, InputType::MoveDown },
        { sf::Keyboard::Key::A, InputType::MoveLeft },
        { sf::Keyboard::Key::D, InputType::MoveRight },
        { sf::Keyboard::Key::Tab, InputType::ChangeObject } };
};

} // namespace RTPS
