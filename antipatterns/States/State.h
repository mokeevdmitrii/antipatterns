//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_STATE_H
#define ANTIPATTERNS_STATE_H

#include "../src/GameObject.h"

class State {
public:
    State(std::shared_ptr<sf::RenderWindow> window);
    virtual ~State();

    void CheckQuit();

    bool IsQuitting() const;

    virtual void EndState() = 0;
    virtual void Render(std::shared_ptr<sf::RenderTarget> target) = 0;
    virtual void Update(float time_elapsed) = 0;
    virtual void UpdateKeyBinds(float time_elapsed) = 0;
private:
    std::vector<std::shared_ptr<sf::Texture>> _textures;
    std::shared_ptr<sf::RenderWindow> _window;
    bool _to_quit = false;
};


#endif //ANTIPATTERNS_STATE_H
