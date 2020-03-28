//
// Created by dmitry on 3/28/20.
//

#include "MainMenuState.h"

/* constructors and destructors */

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window,
                             std::shared_ptr<std::unordered_map<std::string, int>> supported_keys) :
        State(std::move(window), std::move(supported_keys)) {
    MainMenuState::InitKeybindings();
    InitFonts();

    /* testing */
    _main_menu_button = std::make_shared<Button>(400, 300, 100, 100, std::make_shared<sf::Font>(_main_font),
                                                 "Start game", sf::Color(10, 200, 200, 200),
                                                 sf::Color(100, 100, 150, 150),
                                                 sf::Color(180, 100, 100, 230));

    _background.setSize(static_cast<sf::Vector2f>(_window->getSize()));
    _background.setFillColor(sf::Color::Green);
}

MainMenuState::~MainMenuState() {

}

/* overrided functions */

void MainMenuState::EndState() {
    std::cout << "MainMenuState ending" << std::endl;
}

void MainMenuState::Update(const float time_elapsed) {
    UpdateMousePositions();
    UpdateInput(time_elapsed);

    /* testing */
    _main_menu_button->Update(_mouse_positions.view);
}

void MainMenuState::UpdateInput(const float time_elapsed) {
    CheckQuit();
}

void MainMenuState::Render(std::shared_ptr<sf::RenderTarget> target) {
    if (target == nullptr) {
        target = _window;
    }
    target->draw(_background);

    /* testing */
    _main_menu_button->Render(target);
}

void MainMenuState::InitFonts() {
    if (!_main_font.loadFromFile("../Config/lobster.otf")) {
        throw std::runtime_error("MainMenuState cannot load font");
    }
}

void MainMenuState::InitKeybindings() {
    std::ifstream in("../Config/gamestate_keybindings.txt");
    if (in.is_open()) {
        std::string key_str;
        std::string key_bind;
        while (in >> key_str >> key_bind) {
            _keybindings.try_emplace(key_str, _supported_keys->at(key_bind));
        }
    }
}


