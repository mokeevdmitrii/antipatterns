//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_STATE_H
#define ANTIPATTERNS_STATE_H


#include "../src/Player.h"
#include "../Resources/PauseMenu.h"


struct MousePositions {
    sf::Vector2i screen;
    sf::Vector2i window;
    sf::Vector2f view;
};

/*
 * enum StateType {
 *      MAIN_MENU,
 *      GAME,
 *      ...
 *      нужно ли???
 * }
 */

class State {
public:
    State(std::shared_ptr<sf::RenderWindow> window,
          std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
          std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack);

    virtual ~State();

    /* tools for quitting */
    bool GetToQuit() const;

    /* State functions */
    void UpdateMousePositions();
    void Pause();
    void Unpause();
    void End();

    virtual void Render(std::shared_ptr<sf::RenderTarget> target) = 0;
    virtual void Update(float time_elapsed) = 0;
    virtual void UpdateInput(float time_elapsed) = 0;

protected:
    /* declarations */

    /* initializers */
    virtual void InitKeybindings() = 0;

    /* variables */
    std::shared_ptr<std::unordered_map<std::string, int>> _supported_keys;
    std::unordered_map<std::string, int> _keybindings;

    std::shared_ptr<sf::RenderWindow> _window;
    std::shared_ptr<std::stack<std::shared_ptr<State>>> _state_stack;

    bool _to_quit = false;
    bool _paused = false;
    MousePositions _mouse_positions;

    /* from resources */
    std::unordered_map<std::string, sf::Texture> _textures;
private:
    /* still nothing */

};

#endif //ANTIPATTERNS_STATE_H
