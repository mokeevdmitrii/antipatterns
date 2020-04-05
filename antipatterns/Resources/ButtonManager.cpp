//
// Created by dmitry on 3/29/20.
//

#include "ButtonManager.h"

ButtonManager::ButtonManager(const std::string &params_file, const std::string &font_file) {
    LoadFont(font_file);
    InitButtons(params_file);
}

void ButtonManager::LoadFont(const std::string &file_name) {
    if (!_button_font.loadFromFile(file_name)) {
        throw std::runtime_error("Cannot load font");
    }
}

void ButtonManager::InitButtons(const std::string &file_name) {
    std::fstream in(file_name);
    if (in.is_open()) {
        ButtonParams params{};
        std::string button_name{};
        int r, g, b, a;
        while (in >> button_name) {
            in >> params.x >> params.y >> params.width >> params.height;
            in.ignore();
            std::getline(in, params.button_text);
            params.font = std::make_shared<sf::Font>(_button_font);
            in >> params.character_size;
            in >> r >> g >> b >> a;
            params.btn_colors.idle = sf::Color(r, g, b, a);
            in >> r >> g >> b >> a;
            params.btn_colors.hover = sf::Color(r, g, b, a);
            in >> r >> g >> b >> a;
            params.btn_colors.active = sf::Color(r, g, b, a);
            in >> r >> g >> b >> a;
            params.txt_colors.idle = sf::Color(r, g, b, a);
            in >> r >> g >> b >> a;
            params.txt_colors.hover = sf::Color(r, g, b, a);
            in >> r >> g >> b >> a;
            params.txt_colors.active = sf::Color(r, g, b, a);
            _buttons[button_name] = std::make_shared<Button>(params);
        }
    }
    in.close();
}

bool ButtonManager::IsActive(const std::string &button_name) const {
    return _buttons.at(button_name)->IsActive();
}

void ButtonManager::Update(const sf::Vector2f& mouse_pos) {
    for (const auto&[str, btn_ptr] : _buttons) {
        btn_ptr->Update(mouse_pos);
    }
}

void ButtonManager::Render(sf::RenderTarget &target) const {
    for (auto&[str, btn_ptr] : _buttons) {
        btn_ptr->Render(target);
    }
}

const sf::Font& ButtonManager::GetFont() {
    return _button_font;
}

std::shared_ptr<Button> ButtonManager::operator[](const std::string &btn_name) const {
    return _buttons.at(btn_name);
}

std::unordered_map<std::string, std::shared_ptr<Button>>::iterator ButtonManager::begin() {
    return _buttons.begin();
}

std::unordered_map<std::string, std::shared_ptr<Button>>::iterator ButtonManager::end() {
    return _buttons.end();
}





