//
// Created by dmitry on 3/29/20.
//

#include "Button.h"

Button::Button(ButtonParams params) {
    shape_.setPosition(params.x, params.y);
    shape_.setSize(sf::Vector2f(params.width, params.height));

    button_font_ = std::move(params.font);
    text_.setString(params.button_text);
    text_.setFont(*button_font_);
    text_.setFillColor(sf::Color::White);
    text_.setCharacterSize(params.character_size);
    text_.setPosition(shape_.getPosition().x + shape_.getGlobalBounds().width / 2 - text_.getGlobalBounds().width / 2,
                      shape_.getPosition().y + shape_.getGlobalBounds().height / 2 - text_.getGlobalBounds().height / 2);

    btn_colors_.active = params.btn_colors.active;
    btn_colors_.idle = params.btn_colors.idle;
    btn_colors_.hover = params.btn_colors.hover;
    txt_colors_.active = params.txt_colors.active;
    txt_colors_.idle = params.txt_colors.idle;
    txt_colors_.hover = params.txt_colors.hover;

}

Button::~Button() {

}

void Button::Update(const sf::Vector2f &mouse_pos) {
    button_state_ = ButtonState::IDLE;

    if (shape_.getGlobalBounds().contains(mouse_pos)) {
        button_state_ = ButtonState::HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            button_state_ = ButtonState::ACTIVE;
        }
    }

    switch (button_state_) {
        case ButtonState::IDLE:
            shape_.setFillColor(btn_colors_.idle);
            text_.setFillColor(txt_colors_.idle);
            break;
        case ButtonState::HOVER:
            shape_.setFillColor(btn_colors_.hover);
            text_.setFillColor(txt_colors_.hover);
            break;
        case ButtonState::ACTIVE:
            shape_.setFillColor(btn_colors_.active);
            text_.setFillColor(btn_colors_.active);
            break;
        default:
            throw (std::runtime_error("No state for button"));
    }
}

void Button::Render(sf::RenderTarget& target) const {
    target.draw(shape_);
    target.draw(text_);
}

bool Button::IsActive() const {
    return button_state_ == ButtonState::ACTIVE;
}


