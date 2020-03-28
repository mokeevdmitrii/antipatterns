//
// Created by dmitry on 3/28/20.
//

#include "Clock.h"

float Clock::TimeElapsed() const {
    return _clock.getElapsedTime().asSeconds();

}

float Clock::Reset() {
    return _clock.restart().asSeconds();
}
