//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_MAINMENUSTATE_H
#define ANTIPATTERNS_MAINMENUSTATE_H

#include "GameState.h"
#include "../Resources/Button.h"

class MainMenuState : public State {
public:
    MainMenuState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::unordered_map<std::string, int>> supported_keys);
    virtual ~MainMenuState();

    /* overrided functions */
    void Update(float time_elapsed) override;
    void UpdateInput(float time_elapsed) override;
    void Render(std::shared_ptr<sf::RenderTarget> target) override;
    void EndState() override;
private:
    /* initializers */
    void InitFonts();
    void InitKeybindings() override;

    /* variables */
    sf::Font _main_font;
    sf::RectangleShape _background;

    /* test */
    std::shared_ptr<Button> _main_menu_button;
};


#endif //ANTIPATTERNS_MAINMENUSTATE_H
