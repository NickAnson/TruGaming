//
// Created by nicka on 1/1/2021.
//

#ifndef TRUGAMING_GAMECHUNK_H
#define TRUGAMING_GAMECHUNK_H


#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Dependencies/Nlohmann/json.hpp"
#include "../TextureManager/Tile.h"
#include "../TextureManager/Tilemap.h"


class GameChunk {
public:


    GameChunk(sf::RenderWindow &test, std::pair<signed short int, signed short int> chunkToLoadTemp);

    void draw();

    GameChunk() = default;

private:

    int level[Singleton::chunkSize * Singleton::chunkSize];
    Tilemap map;
    sf::RenderWindow *tileMapRenderWindow;
    std::vector<Tile> chunks;

    void convertToTile();

    std::string fileName;

};


#endif //TRUGAMING_GAMECHUNK_H
