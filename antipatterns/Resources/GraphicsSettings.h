//
// Created by dmitry on 3/30/20.
//

#ifndef ANTIPATTERNS_GRAPHICSSETTINGS_H
#define ANTIPATTERNS_GRAPHICSSETTINGS_H

#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <utility>
#include <unordered_map>
#include <string>
#include "random"
#include "Json.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class GraphicsSettings {
public:
    std::string game_title_;
    sf::VideoMode resolution_;
    std::vector<sf::VideoMode> video_modes_;
    sf::ContextSettings settings_;
    unsigned int framerate_limit_;
    bool fullscreen_;
    bool v_sync_enabled_;

    GraphicsSettings();

    bool LoadFromFile(const std::string& file_name);
};


#endif //ANTIPATTERNS_GRAPHICSSETTINGS_H
