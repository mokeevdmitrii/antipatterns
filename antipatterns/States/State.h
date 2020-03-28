//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_STATE_H
#define ANTIPATTERNS_STATE_H

#include "../src/GameObject.h"

class State {
public:
    State(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::unordered_map<std::string, int>> supported_keys);
    virtual ~State();

    /* tools for quitting */
    void CheckQuit();
    bool IsQuitting() const;

    /* State functions */
    virtual void EndState() = 0;
    virtual void Render(std::shared_ptr<sf::RenderTarget> target) = 0;
    virtual void Update(float time_elapsed) = 0;
    virtual void UpdateInput(float time_elapsed) = 0;
protected:
    /* functions */
    virtual void InitKeybindings() = 0;

    /* variables */
    std::vector<std::shared_ptr<sf::Texture>> _textures;
    std::shared_ptr<std::unordered_map<std::string, int>> _supported_keys;
    std::unordered_map<std::string, int> _keybindings;
    std::shared_ptr<sf::RenderWindow> _window;
    bool _to_quit = false;
private:

};


#endif //ANTIPATTERNS_STATE_H
