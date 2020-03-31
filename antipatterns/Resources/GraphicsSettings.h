//
// Created by dmitry on 3/30/20.
//

#ifndef ANTIPATTERNS_GRAPHICSSETTINGS_H
#define ANTIPATTERNS_GRAPHICSSETTINGS_H

#include "fstream"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class GraphicsSettings {
public:
    std::string _game_title;
    sf::VideoMode _resolution;
    std::vector<sf::VideoMode> _video_modes;
    sf::ContextSettings _settings;
    unsigned int _framerate_limit;
    bool _fullscreen;
    bool _v_sync_enabled;

    GraphicsSettings();

    bool LoadFromFile(const std::string& file_name);
};


#endif //ANTIPATTERNS_GRAPHICSSETTINGS_H
