//
// Created by nicka on 1/1/2021.
//

#ifndef TRUGAMING_MAPFILESYSTEM_H
#define TRUGAMING_MAPFILESYSTEM_H


#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Dependencies/Nlohmann/json.hpp"
#include "../TextureManager/Tile.h"

class MapFileSystem {
public:


    MapFileSystem(const std::string &fileName, sf::RenderWindow *test);

    void setTexture(int x, int y, int depth, std::string textureName);

    ~MapFileSystem() {
        fileOpened.close();
    }
    bool changed = false;

private:

    std::vector<Tile> tileMap;
    std::vector<Tile> decTileMap;

    std::fstream fileOpened;
    std::vector<int> test;

    MapFileSystem() = default;

    int getTexture(std::string textureName);
};


#endif //TRUGAMING_MAPFILESYSTEM_H
