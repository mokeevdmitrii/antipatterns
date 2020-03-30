//
// Created by dmitry on 3/30/20.
//

#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
    _game_title = "antipatterns roguelike";
    _resolution = sf::VideoMode::getDesktopMode();
    _framerate_limit = 60;
    _fullscreen = false;
    _v_sync_enabled = false;
    _settings.antialiasingLevel = 0;
    _video_modes = sf::VideoMode::getFullscreenModes();
}


bool GraphicsSettings::LoadFromFile(const std::string &file_name) {
    std::ifstream in(file_name);
    bool flag = in.is_open();
    if (in.is_open()) {
        std::getline(in, _game_title);
        in >> _resolution.width >> _resolution.height;
        in >> _framerate_limit;
        in >> _fullscreen;
        in >> _v_sync_enabled;
        in >> _settings.antialiasingLevel;
    }
    in.close();
    return flag;
}

