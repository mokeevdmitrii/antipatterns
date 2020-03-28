#include "Game.h"

int main() {
    Game game;
    game.Run();
    sf::Clock clock1;
    for (int i = 0; i < 1000000; ++i) {
        if (i % 100000 == 0) {
            std::cout << clock1.getElapsedTime().asMicroseconds() << std::endl;
        }
    }
}
