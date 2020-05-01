//
// Created by dmitry on 4/30/20.
//

#ifndef ANTIPATTERNS_ROOM_H
#define ANTIPATTERNS_ROOM_H

#include "TileMap.h"
#include "EnemySystem.h"
#include "Player.h"
#include "Exit.h"

enum ROOM_ID {
    INIT_ROOM = 0,
    BOSS_ROOM
};

class Room {
public:
    explicit Room(const std::string &file_name);

    void Update(float time_elapsed);

    void Render(sf::RenderTarget &target);

    //идёт по всем exit-ам, спрашивает у них ROOM_ID, если не совпадает с текущим,
    //возвращает не совпадающий!
    ROOM_ID GetCurrentRoomID() const;

    ROOM_ID GetRoomID() const;

    void SetPlayer(std::shared_ptr<Creature> player);
private:
    void InitEnemySystem(const std::map<std::string, Json::Node>& enemy_settings);
    void InitTileMap(const std::map<std::string, Json::Node>& map_settings);

    void UpdateCollisions();

    //проверяет все выходы, если игрок стоит хоть на одном, делает этот выход
    //активным!!!
    //if Player.inside(exit.GetHitbox()) - exit.SetActive()
    void UpdatePlayerExit();

    std::shared_ptr<TileMap> map_;
    std::shared_ptr<Creature> player_{nullptr};
    std::vector<Exit> exits_;
    std::unique_ptr<EnemySystem> enemy_system_;
    ROOM_ID room_id_;
};


#endif //ANTIPATTERNS_ROOM_H
