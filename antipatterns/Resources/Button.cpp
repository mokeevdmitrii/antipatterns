//
// Created by dmitry on 3/29/20.
//

#include "Button.h"

Button::Button(ButtonParams params) {
    _shape.setPosition(params.x, params.y);
    _shape.setSize(sf::Vector2f(params.width, params.height));

    _button_font = std::move(params.font);
    _text.setString(params.button_text);
    _text.setFont(*_button_font);
    _text.setFillColor(sf::Color::White);
    _text.setCharacterSize(params.character_size);
    _text.setPosition(_shape.getPosition().x + _shape.getGlobalBounds().width / 2 - _text.getGlobalBounds().width / 2,
                      _shape.getPosition().y + _shape.getGlobalBounds().height / 2 - _text.getGlobalBounds().height / 2);

    btn_colors.active = params.btn_colors.active;
    btn_colors.idle = params.btn_colors.idle;
    btn_colors.hover = params.btn_colors.hover;
    _txt_colors.active = params.txt_colors.active;
    _txt_colors.idle = params.txt_colors.idle;
    _txt_colors.hover = params.txt_colors.hover;

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
            _shape.setFillColor(btn_colors.idle);
            _text.setFillColor(_txt_colors.idle);
            break;
        case ButtonState::HOVER:
            _shape.setFillColor(btn_colors.hover);
            _text.setFillColor(_txt_colors.hover);
            break;
        case ButtonState::ACTIVE:
            _shape.setFillColor(btn_colors.active);
            _text.setFillColor(btn_colors.active);
            break;
        default:
            throw (std::runtime_error("No state for button"));
    }
}

void Button::Render(sf::RenderTarget& target) {
    target.draw(_shape);
    target.draw(_text);
}

bool Button::IsActive() const {
    return _button_state == ButtonState::ACTIVE;
}


