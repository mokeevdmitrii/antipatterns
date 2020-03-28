//
// Created by dmitry on 3/29/20.
//

#ifndef ANTIPATTERNS_BUTTON_H
#define ANTIPATTERNS_BUTTON_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum class ButtonState {
    IDLE,
    HOVER,
    ACTIVE
};

struct ButtonColors {
    sf::Color _active;
    sf::Color _idle;
    sf::Color _hover;
};

class Button {
public:
    /* heavy constructor but this class will be worked up */
    Button(float x, float y, float width, float height,
           std::shared_ptr<sf::Font> font, std::string button_text,
           sf::Color active_color, sf::Color idle_color, sf::Color hover_color);

    virtual ~Button();

    /* accessing */
    bool IsActive() const;

    /* functions */
    void Update(const sf::Vector2f& mouse_pos);
    void Render(std::shared_ptr<sf::RenderTarget> target);

private:
    sf::RectangleShape _shape;
    std::shared_ptr<sf::Font> _button_font;
    sf::Text _text;
    ButtonColors _colors;
    ButtonState _button_state;
};


#endif //ANTIPATTERNS_BUTTON_H
