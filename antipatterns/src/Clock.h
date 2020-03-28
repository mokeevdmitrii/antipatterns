//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_CLOCK_H
#define ANTIPATTERNS_CLOCK_H

#include <SFML/System.hpp>

class Clock {
private:
    sf::Clock _clock;
public:
    [[nodiscard]] float TimeElapsed() const;

    float Reset();
};


#endif //ANTIPATTERNS_CLOCK_H
