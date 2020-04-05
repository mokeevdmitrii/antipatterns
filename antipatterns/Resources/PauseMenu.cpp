//
// Created by dmitry on 4/1/20.
//

#include "PauseMenu.h"


PauseMenu::PauseMenu(const std::shared_ptr<sf::RenderWindow>& window) : _btn_manager("../Config/pause_menu_buttons.txt",
                                                              "../Config/lobster.otf") {
    _inner.setSize(sf::Vector2f(window->getSize().x * _inner_ratio_x,
                                window->getSize().y * _inner_ratio_y));
    _background.setSize(sf::Vector2f(window->getSize().x * _outer_ratio_x,
                                     window->getSize().y * _outer_ratio_y));
    _background.setFillColor(sf::Color(20, 20, 20, 100));
    _inner.setFillColor(sf::Color(20, 20, 20, 200));

    /* goddamn center everything lmao */
    _background.setPosition(window->getSize().x / 2.f - _background.getSize().x / 2.f,
                            window->getSize().y / 2.f - _background.getSize().y / 2.f);
    _inner.setPosition(window->getSize().x / 2.f - _inner.getSize().x / 2.f,
                       window->getSize().y / 2.f - _inner.getSize().y / 2.f);
    _menu_text = sf::Text("Game paused", _btn_manager.GetFont(), 30);
    _menu_text.setPosition(window->getSize().x * 0.5 - _menu_text.getGlobalBounds().width * 0.5,
            window->getSize().y * 0.1 - _menu_text.getGlobalBounds().height * 0.5);
    _menu_text.setFillColor(sf::Color(200, 200, 200, 200));
}

PauseMenu::~PauseMenu() {

}

/* functions */

void PauseMenu::Update(const sf::Vector2f& mouse_pos) {
    _btn_manager.Update(mouse_pos);
}

void PauseMenu::Render(sf::RenderTarget &target) const {
    target.draw(_background);
    target.draw(_inner);
    target.draw(_menu_text);
    _btn_manager.Render(target);
}

bool PauseMenu::IsButtonActive(const std::string& button_key) const {
    return _btn_manager[button_key]->IsActive();
}
