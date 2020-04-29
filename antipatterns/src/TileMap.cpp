//
// Created by dmitry on 4/2/20.
//

#include "TileMap.h"

TileMap::TileMap(const std::string &settings_file_name, const std::string &map_tile_name) {
    InitUniqueTiles(settings_file_name);
    InitMap(map_tile_name);
}

void TileMap::UpdateTiles(std::unique_ptr<Creature> creature, float time_elapsed /*, EnemySystem& system */) {
    /* проверка, не вышло ли существо за границы */
    /* проверка всех плиток в определенном прямоугольнике */
}

void TileMap::Render(sf::RenderTarget &target) const {
    for (auto &vec_x : map_) {
        for (auto& vec_y : vec_x) {
            for (auto &tile_layer : vec_y) {
                tile_layer->Render(target);
            }
        }
    }
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

void TileMap::InitUniqueTiles(const std::string &file_name) {
    std::map<std::string, Json::Node> settings = Json::Load(file_name).GetRoot().AsMap();
    std::string texture_file = settings.at("file_name").AsString();
    tile_sheet_.loadFromFile(texture_file);
    grid_size_ = static_cast<int>(settings.at("grid_size").AsDouble());
    world_size_.x = static_cast<int>(settings.at("world_size_x").AsDouble());
    world_size_.y = static_cast<int>(settings.at("world_size_y").AsDouble());
    for (const auto &settings_map : settings.at("tiles").AsArray()) {
        sf::IntRect curr_rect;
        TileType curr_type;
        curr_rect.height = curr_rect.width = grid_size_;
        curr_rect.left = static_cast<int>(settings_map.AsMap().at("x").AsDouble()) * grid_size_;
        curr_rect.top = static_cast<int>(settings_map.AsMap().at("y").AsDouble()) * grid_size_;
        curr_type = static_cast<TileType>(settings_map.AsMap().at("type").AsDouble());
        unique_tiles_[curr_type] = std::make_unique<Tile>(curr_type, tile_sheet_, curr_rect);
    }
}

void TileMap::InitMap(const std::string &file_name) {
    map_.resize(world_size_.x);
    for (auto &sub_vec : map_) {
        sub_vec.resize(world_size_.y);
    }
    const std::vector<Json::Node> map = Json::Load(file_name).GetRoot().AsArray();
    for (int i = 0; i < world_size_.x; ++i) {
        const std::vector<Json::Node> &map_x = map[i].AsArray();
        for (int j = 0; j < world_size_.y; ++j) {
            const std::vector<Json::Node> &map_y = map_x[j].AsArray();
            for (const Json::Node &type : map_y) {
                map_[i][j].push_back(unique_tiles_.at(static_cast<TileType>(type.AsDouble()))->Clone(
                        GetGlobalPosition(sf::Vector2i(i, j))));
            }
        }
    }
}







