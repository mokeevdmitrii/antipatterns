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
#include <fstream>
#include <unordered_map>

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
    sf::Color idle;
    sf::Color hover;
    sf::Color active;
};

struct TextColors {
    sf::Color idle;
    sf::Color hover;
    sf::Color active;
};

struct ButtonParams {
    float x;
    float y;
    float width;
    float height;
    std::shared_ptr<sf::Font> font;
    std::string button_text;
    unsigned int character_size;
    ButtonColors btn_colors;
    TextColors txt_colors;
};

class Button {
public:
    Button(ButtonParams params);

    virtual ~Button();

    /* accessing */
    bool IsActive() const;

    /* functions */
    void Update(const sf::Vector2f &mouse_pos);

    void Render(sf::RenderTarget& target) const;

private:
    sf::RectangleShape _shape;
    std::shared_ptr<sf::Font> _button_font;
    sf::Text _text;
    ButtonColors btn_colors;
    TextColors _txt_colors;
    ButtonState _button_state;
};


#endif //ANTIPATTERNS_BUTTON_H
