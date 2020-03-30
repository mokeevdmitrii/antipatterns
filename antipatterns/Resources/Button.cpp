//
// Created by dmitry on 3/29/20.
//

#include "Button.h"

Button::Button(ButtonParams params) {
    _shape.setPosition(params._x, params._y);
    _shape.setSize(sf::Vector2f(params._width, params._height));

    _button_font = std::move(params._font);
    _text.setString(params._button_text);
    _text.setFont(*_button_font);
    _text.setFillColor(sf::Color::White);
    _text.setCharacterSize(20);
    _text.setPosition(_shape.getPosition().x + _shape.getGlobalBounds().width / 2 - _text.getGlobalBounds().width / 2,
                      _shape.getPosition().y + _shape.getGlobalBounds().height / 2 - _text.getGlobalBounds().height / 2);

    _colors._active = params._colors._active;
    _colors._idle = params._colors._idle;
    _colors._hover = params._colors._hover;
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

void Button::Render(const std::shared_ptr<sf::RenderTarget>& target) {
    target->draw(_shape);
    target->draw(_text);
}

bool Button::IsActive() const {
    return _button_state == ButtonState::ACTIVE;
}


