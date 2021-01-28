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

unsigned short int const chunkSize = 32;

class GameChunk {
public:


    GameChunk(const std::string &fileName, sf::RenderWindow &test, sf::Vector2<int> &chunkNumber);

    void draw();

    sf::Vector2i getChunkNumber();

    void setChunkNumber(sf::Vector2i &number);

private:

    sf::Vector2i chunkNumber;
    std::string tileMap;
    bool update = true;
    char level[chunkSize * chunkSize];
    Tilemap map;
    sf::RenderWindow *tileMapRenderWindow;
    std::vector<Tile> chunks;
    sf::Vector2i tileMapLocation;

    static std::vector<Tile> convertToTile(const std::string &fileName);

    GameChunk() = default;

    static int getTexture(std::basic_string<char> textureName);

};


#endif //TRUGAMING_GAMECHUNK_H
