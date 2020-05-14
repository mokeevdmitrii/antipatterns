//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_TILEMAP_H
#define ANTIPATTERNS_TILEMAP_H

#include "../Resources/Utility.h"
#include "Creature.h"
#include "Tile.h"

class TileMap {
  using Map = std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>>;

public:
  explicit TileMap(
      const std::string &map_tile_name,
      const std::unordered_map<TileType, std::unique_ptr<Tile>> &unique_tiles);

  ~TileMap() = default;

  template <typename T>

  void UpdateCreature(T &creature);

  void Render(sf::RenderTarget &target) const;

  static int GetGridSize();

  static void SetGridSize(int grid_size);

  sf::Vector2i GetGridPosition(sf::Vector2f global_position) const;

  sf::Vector2f GetGlobalPosition(sf::Vector2i grid_position) const;

  std::vector<std::vector<int>> GetCostMap() const;

private:
  void InitMap(
      const std::string &file_name,
      const std::unordered_map<TileType, std::unique_ptr<Tile>> &unique_tiles);
  void AddTileLayer(
      TileType type, int x_pos, int y_pos, sf::Vector2f shift,
      const std::unordered_map<TileType, std::unique_ptr<Tile>> &unique_tiles);
  bool CanMove(const sf::FloatRect &rect);

  std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>> map_;
  static int grid_size_;
  sf::Vector2i world_size_;
  sf::RectangleShape borders_;
};

template <typename T> void TileMap::UpdateCreature(T &creature) {
  if constexpr (std::is_same_v<T, std::shared_ptr<Creature>> ||
                std::is_same_v<T, std::unique_ptr<Creature>>) {
    sf::RectangleShape hitbox = creature->GetHitbox();
    sf::Vector2f left_up_pos = hitbox.getPosition();
    sf::Vector2f size = hitbox.getSize();
    sf::Vector2f borders_pos = borders_.getPosition();
    sf::Vector2f borders_size = borders_.getSize();
    PossibleDirections new_directions;
    new_directions = {left_up_pos.x >= borders_pos.x,
                      (left_up_pos.x + size.x) <=
                          borders_pos.x + borders_size.x,
                      left_up_pos.y >= borders_pos.y,
                      left_up_pos.y + size.y <= borders_pos.y + borders_size.y};
    PossibleDirections tile_directions;
    tile_directions.left = CanMove({left_up_pos, {0.1, size.y}});
    tile_directions.right =
        CanMove({{left_up_pos.x + size.x, left_up_pos.y}, {0.1, size.y}});
    tile_directions.up =
        CanMove({{left_up_pos.x, left_up_pos.y}, {size.x, 0.1}});
    tile_directions.down =
        CanMove({{left_up_pos.x, left_up_pos.y + size.y}, {size.x, 0.1}});
    new_directions = new_directions && tile_directions;
    creature->GetPhysicsComponent()->SetPossibleMoveDirections(new_directions);
    sf::Vector2f creature_c_pos =
        creature->GetHitboxComponent()->GetCenteredPosition();
    sf::Vector2i grid_pos = GetGridPosition(creature_c_pos);
    double move_cost = 1;
    for (const auto &layer : map_.at(grid_pos.y).at(grid_pos.x)) {
      move_cost = std::max(move_cost, layer->GetMoveCost());
    }
    creature->GetPhysicsComponent()->UpdateSpeedMultiplier(1 / move_cost);
  }
}

#endif // ANTIPATTERNS_TILEMAP_H
