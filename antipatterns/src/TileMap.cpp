//
// Created by dmitry on 4/2/20.
//

#include "TileMap.h"

int TileMap::grid_size_ = 62;

std::shared_ptr<std::unordered_map<TileType, std::unique_ptr<Tile>>> TileMap::unique_tiles_ = nullptr;

TileMap::TileMap(const std::string &map_tile_name) {
    InitMap(map_tile_name);
}

void TileMap::UpdateTiles(std::unique_ptr<Creature> creature, float time_elapsed /*, EnemySystem& system */) {
    /* проверка, не вышло ли существо за границы */
    /* проверка всех плиток в определенном прямоугольнике */
}

void TileMap::Render(sf::RenderTarget &target) const {
    for (auto &vec_x : map_) {
        for (auto &vec_y : vec_x) {
            for (auto &tile_layer : vec_y) {
                tile_layer->Render(target);
            }
        }
    }
}

int TileMap::GetGridSize() {
    return grid_size_;
}

void TileMap::SetGridSize(int grid_size) {
    grid_size_ = grid_size;
}


sf::Vector2i TileMap::GetGridPosition(sf::Vector2f global_position) const {
    return sf::Vector2i(static_cast<int>(static_cast<int>(global_position.x) / grid_size_),
                        static_cast<int>(static_cast<int>(global_position.y)) / grid_size_);
}

sf::Vector2f TileMap::GetGlobalPosition(sf::Vector2i grid_position) const {
    return sf::Vector2f(static_cast<float>(grid_position.x * grid_size_),
                        static_cast<float>(grid_position.y * grid_size_));
}


/* initializers */

void TileMap::InitMap(const std::string &file_name) {
    const std::vector<Json::Node> map_layers = Json::Load(file_name).GetRoot().AsArray();
    world_size_.y = map_layers.empty() ? 0 : map_layers.front().AsArray().size();
    world_size_.x = world_size_.y == 0 ? 0 : map_layers.front().AsArray().front().AsArray().size();
    //настраиваем размеры карты
    map_.resize(world_size_.x);
    for (auto &sub_vec : map_) {
        sub_vec.resize(world_size_.y);
    }
    for (const auto &layer_node : map_layers) {
        const std::vector<Json::Node>& layer = layer_node.AsArray();
        for (int y_pos = 0; y_pos < world_size_.y; ++y_pos) {
            const std::vector<Json::Node> &row = layer[y_pos].AsArray();
            for (int x_pos = 0; x_pos < world_size_.x; ++x_pos) {
                auto type = static_cast<TileType>(row[x_pos].AsDouble());
                map_[y_pos][x_pos].push_back(
                        unique_tiles_->at(type)->Clone(GetGlobalPosition(sf::Vector2i(x_pos, y_pos))));
            }
        }
    }
}

void TileMap::SetUniqueTiles(std::shared_ptr<std::unordered_map<TileType, std::unique_ptr<Tile>>> unique_tiles) {
    unique_tiles_ = std::move(unique_tiles);
}








