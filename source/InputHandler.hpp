#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>
#include <optional>
#include <queue>
#include <unordered_set>

namespace RTPS {

enum class InputType : int { MoveUp, MoveDown, MoveLeft, MoveRight, ChangeObject };

class InputHandler {
public:
    void update( float deltaTime );
    const std::unordered_set< InputType >& getInputTypes() const noexcept;

private:
    inline static const std::unordered_multimap< sf::Keyboard::Key, InputType > m_inputMap{
        { sf::Keyboard::Key::W, InputType::MoveUp },
        { sf::Keyboard::Key::S, InputType::MoveDown },
        { sf::Keyboard::Key::A, InputType::MoveLeft },
        { sf::Keyboard::Key::D, InputType::MoveRight },
        { sf::Keyboard::Key::Tab, InputType::ChangeObject } };

    std::unordered_set< InputType > m_inputTypes{};

    void clearPreviousInputs();
    void addCurrentInputs();
};

} // namespace RTPS
