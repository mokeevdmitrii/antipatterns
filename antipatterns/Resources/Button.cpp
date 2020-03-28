//
// Created by dmitry on 3/29/20.
//

#include "Button.h"

Button::Button(float x, float y, float width, float height, std::shared_ptr<sf::Font> font, std::string button_text,
               sf::Color active_color, sf::Color idle_color, sf::Color hover_color) {
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));

    _button_font = std::move(font);
    _text.setString(button_text);
    _text.setFont(*_button_font);
    _text.setFillColor(sf::Color::White);
    _text.setCharacterSize(20);
    _text.setPosition(_shape.getPosition().x + _shape.getGlobalBounds().width / 2 - _text.getGlobalBounds().width / 2,
                      _shape.getPosition().y + _shape.getGlobalBounds().height / 2 - _text.getGlobalBounds().height / 2);

    _colors._active = active_color;
    _colors._idle = idle_color;
    _colors._hover = hover_color;
}

Button::~Button() {

}

void Button::Update(const sf::Vector2f &mouse_pos) {
    _button_state = ButtonState::IDLE;

    if (_shape.getGlobalBounds().contains(mouse_pos)) {
        _button_state = ButtonState::HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _button_state = ButtonState::ACTIVE;
        }
    }

    switch (_button_state) {
        case ButtonState::IDLE:
            _shape.setFillColor(_colors._idle);
            break;
        case ButtonState::HOVER:
            _shape.setFillColor(_colors._hover);
            break;
        case ButtonState::ACTIVE:
            _shape.setFillColor(_colors._active);
            break;
        default:
            throw (std::runtime_error("No state for button"));
    }
}

void Button::Render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(_shape);
    target->draw(_text);
}

bool Button::IsActive() const {
    return _button_state == ButtonState::ACTIVE;
}


