//
// Created by dmitry on 3/29/20.
//

#ifndef ANTIPATTERNS_BUTTONMANAGER_H
#define ANTIPATTERNS_BUTTONMANAGER_H

#include "Button.h"
#include <unordered_map>
#include <utility>

class ButtonManager {
public:
    ButtonManager(const std::string &params_file, const std::string &font_file);

    void LoadFont(const std::string &file_name);

    void InitButtons(const std::string &file_name);

    bool IsActive(const std::string &button_name) const;

    void Update(const sf::Vector2f &mouse_pos);

    void Render(const std::shared_ptr<sf::RenderTarget> &target);

    std::shared_ptr<Button> operator[](const std::string &btn_name) const;

    std::unordered_map<std::string, std::shared_ptr<Button>>::iterator begin();

    std::unordered_map<std::string, std::shared_ptr<Button>>::iterator end();

private:
    std::unordered_map<std::string, std::shared_ptr<Button>> _buttons;
    sf::Font _button_font;
};


#endif //ANTIPATTERNS_BUTTONMANAGER_H
