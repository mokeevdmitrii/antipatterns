//
// Created by dmitry on 4/30/20.
//

#include "Room.h"

Room::Room(const std::string &file_name) {
  const std::map<std::string, Json::Node> room_settings =
      Json::Load(file_name).GetRoot().AsMap();
  InitEnemySystem(room_settings.at("enemy_system").AsMap());
  InitTileMap(room_settings.at("tile_map").AsMap());
}

void Room::Update(float time_elapsed) {
  UpdateCollisions();
  if (player_ != nullptr) {
    player_->Update(time_elapsed);
  }
  enemy_system_->Update(time_elapsed);
}

void Room::Render(sf::RenderTarget &target) {
  map_->Render(target);
  for (const auto &exit : exits_) {
    exit->Render(target);
  }
  enemy_system_->Render(target);
  player_->Render(target);
}

const Exit *Room::GetActiveExit() const {
  for (const auto &exit : exits_) {
    const sf::RectangleShape &hitbox = exit->GetHitbox();
    if (player_->GetHitboxComponent()->ContainedIn(hitbox)) {
      return exit.get();
    }
  }
  return nullptr;
}

ROOM_ID Room::GetRoomID() const { return room_id_; }

void Room::AddExit(std::unique_ptr<Exit> exit) {
  exits_.push_back(std::move(exit));
}

void Room::SetPlayer(std::shared_ptr<Creature> player) {
  player_ = std::move(player);
  enemy_system_->SetPlayer(player_);
}

void Room::InitEnemySystem(
    const std::map<std::string, Json::Node> &enemy_settings) {
  enemy_system_ = std::make_unique<EnemySystem>(
      enemy_settings, UniqueDatabase::Instance().GetData().enemies);
}

void Room::InitTileMap(const std::map<std::string, Json::Node> &map_settings) {
  map_ = std::make_unique<TileMap>(map_settings.at("tiles").AsString(),
                                   UniqueDatabase::Instance().GetData().tiles);
}

void Room::UpdateCollisions() {
  if (player_ != nullptr) {
    map_->UpdateCreature<std::shared_ptr<Creature>>(player_);
  }
}
