//
// Created by dmitry on 3/28/20.
//

#include "MainMenuState.h"

/* constructors and destructors */

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window,
                             std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
                             std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack) :
        State(std::move(window), std::move(supported_keys), std::move(state_stack)),
        _btn_manager("../Config/main_menu_buttons.txt", "../Config/lobster.otf") {
    InitBackground();
    MainMenuState::InitKeybindings();
}

MainMenuState::~MainMenuState() {

}

/* overrided functions */


void MainMenuState::Update(const float time_elapsed) {
    UpdateMousePositions();
    UpdateInput(time_elapsed);
    _btn_manager.Update(_mouse_positions.view);

    /* updating all the buttons */
    /* quit the game */
    if (_btn_manager["END_GAME"]->IsActive()) {
        _to_quit = true;
    }

    /* new game */
    /* pushing a state */
    if (_btn_manager["START_GAME"]->IsActive()) {
        _state_stack->push(std::make_shared<GameState>(_window, _supported_keys, _state_stack));
    }
}

void MainMenuState::UpdateInput(const float time_elapsed) {

}


void MainMenuState::Render(std::shared_ptr<sf::RenderTarget> target) {
    /* временный костыль */
    if (target == nullptr) {
        target = _window;
    }
    target->draw(_background._image);
    _btn_manager.Render(*target);
}

void MainMenuState::InitKeybindings() {
    std::ifstream in("../Config/main_menu_state_keybindings.txt");
    if (in.is_open()) {
        std::string key_str;
        std::string key_bind;
        while (in >> key_str >> key_bind) {
            _keybindings.try_emplace(key_str, _supported_keys->at(key_bind));
        }
    }
}

void MainMenuState::InitBackground() {
    _background._image.setSize(static_cast<sf::Vector2f>(_window->getSize()));
    if (!_background._back_texture.loadFromFile("../Images/Backgrounds/main_menu.png")) {
        throw std::runtime_error("cannot load texture for main menu background");
    }
    _background._image.setTexture(&_background._back_texture);
}





