//
// Created by dmitry on 4/30/20.
//

#ifndef ANTIPATTERNS_EXIT_H
#define ANTIPATTERNS_EXIT_H

#include <string>
#include "iostream"
#include "../Components/HitboxComponent.h"
#include <SFML/Graphics.hpp>
#include <memory>

enum ROOM_ID {
    INIT_ROOM = 0,
    SECOND_ROOM
};

enum ExitType {
    DOOR = 0,
};

class Exit {
private:
    ROOM_ID id_from_;
    ROOM_ID id_to_;
    sf::Sprite sprite_{};
    sf::RectangleShape hitbox_;

    static std::shared_ptr<std::unordered_map<ExitType, std::unique_ptr<Exit>>> unique_exits_;

    void SetRoomIDs(ROOM_ID from, ROOM_ID to);
public:

    Exit(ROOM_ID from, ROOM_ID to);

    Exit(sf::RectangleShape hitbox, sf::Texture& texture_sheet, sf::IntRect texture_rect);

    ROOM_ID GetRoomIdFrom() const;

    ROOM_ID GetRoomIdTo() const;

    const sf::RectangleShape & GetHitbox() const;

    void Render(sf::RenderTarget &target) const;

    void LoadFromMap(const std::map<std::string, Json::Node> &settings);

    sf::Vector2f GetPosition() const;

    static void SetUniqueExits(std::shared_ptr<std::unordered_map<ExitType, std::unique_ptr<Exit>>> unique_exits);
};


#endif //ANTIPATTERNS_EXIT_H
