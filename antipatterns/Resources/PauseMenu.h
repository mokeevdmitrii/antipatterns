//
// Created by dmitry on 4/1/20.
//

#ifndef ANTIPATTERNS_PAUSEMENU_H
#define ANTIPATTERNS_PAUSEMENU_H

#include "ButtonManager.h"

class PauseMenu {
public:
    PauseMenu(const std::shared_ptr<sf::RenderWindow>& window);
    ~PauseMenu();

    void Update(const sf::Vector2f& mouse_pos);
    void Render(sf::RenderTarget& target);

    bool IsButtonActive(const std::string& button_key);
private:
    sf::RectangleShape _background;
    sf::RectangleShape _inner;
    sf::Text _menu_text;
    ButtonManager _btn_manager;

    constexpr static const float _outer_ratio_x{1.0};
    constexpr static const float _outer_ratio_y{1.0};

    constexpr static const float _inner_ratio_x{0.4};
    constexpr static const float _inner_ratio_y{1.0};
};


#endif //ANTIPATTERNS_PAUSEMENU_H
