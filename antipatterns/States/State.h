//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_STATE_H
#define ANTIPATTERNS_STATE_H

#include "../src/GameObject.h"

struct MousePositions {
    sf::Vector2i screen;
    sf::Vector2i window;
    sf::Vector2f view;
};

class State {
public:
    State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::unordered_map<std::string, int>> supported_keys);
    virtual ~State();

    /* tools for quitting */
    void CheckQuit();
    bool IsQuitting() const;

    /* State functions */
    void UpdateMousePositions();
    virtual void EndState() = 0;
    virtual void Render(std::shared_ptr<sf::RenderTarget> target) = 0;
    virtual void Update(float time_elapsed) = 0;
    virtual void UpdateInput(float time_elapsed) = 0;
protected:
    /* declarations */
    /* functions */
    virtual void InitKeybindings() = 0;

    /* variables */
    std::shared_ptr<std::unordered_map<std::string, int>> _supported_keys;
    std::unordered_map<std::string, int> _keybindings;
    std::shared_ptr<sf::RenderWindow> _window;
    bool _to_quit = false;
    MousePositions _mouse_positions;

    /* from resources */
    std::vector<std::shared_ptr<sf::Texture>> _textures;
private:
    /* still nothing */

};







#endif //ANTIPATTERNS_STATE_H
