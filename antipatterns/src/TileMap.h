//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_TILEMAP_H
#define ANTIPATTERNS_TILEMAP_H

#include "Tile.h"
#include "Creature.h"

/* Были мысли насчёт того, чтобы использовать здесь шаблон приспособленец, то есть хранить
 * массив не с уникальными указателями на плитки, а с shared_ptr<Tile>, при этом объектов типа Tile
 * у нас было бы столько же, сколько всего существует различных типов плиток, то есть мы получили
 * бы огромный выигрыш в памяти и немного в производительности, но после оказалось, что
 * библиотека SFML is a very Simple library, поэтому она не смогла бы по одной текстуре нарисовать
 * в куче мест на экране одну и ту же плитку, в общем так мы потеряли неплохой
 * порождающий паттерн :(
 */


/* переделать всю карту в вектор комнат (class Room), каждый раз при обновлении TileMap и прочего, обновлять только комнату!!! */

class TileMap {
    using Map = std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>>;
public:
    TileMap(const std::string& settings_file_name, const std::string& map_tile_name);
    ~TileMap() = default;

    /* updating all the map */
    /* this function will be implemented later */
    /* идея этой функции в том, чтобы в будущем не выпускать существ за пределы карты, проверяются только те плитки,
     * которые сейчас есть на экране */
    void UpdateTiles(std::unique_ptr<Creature> creature, float time_elapsed);
    void Render(sf::RenderTarget& target) const;

    /* not static because what about different grid_sizes ? */
    sf::Vector2i GetGridPosition(sf::Vector2f global_position) const;
    sf::Vector2f GetGlobalPosition(sf::Vector2i grid_position) const;

private:
    /* initializers */
    /* initialize unique tiles parameters from a tile */
    void InitUniqueTiles(const std::string& file_name);
    void InitMap(const std::string& file_name);
    std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>> _map;
    std::unordered_map<TileType, std::unique_ptr<Tile>> _unique_tiles;
    int _grid_size;
    sf::Vector2i _world_size;
    sf::Texture _tile_sheet;
};


#endif //ANTIPATTERNS_TILEMAP_H
