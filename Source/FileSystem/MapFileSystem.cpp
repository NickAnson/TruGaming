//
// Created by nicka on 1/1/2021.
//

#include <iostream>
#include "MapFileSystem.h"
#include "../TextureManager/Tilemap.h"
#include "../TextureManager/Tile.h"
#include "../TextureManager/TileMap/TileToNumberConverter.h"

unsigned int const chunkSize = 16;

MapFileSystem::MapFileSystem(const std::string &fileName,sf::RenderWindow * test) {

        //In future we will optimize this only when a chunk is updated and another is removed not every time .

        std::ifstream f;
        f.open(fileName);
        nlohmann::json jsonFile = nlohmann::json::parse(f);
        f.close();

        if (jsonFile.is_null()) {
            std::cout << "FAILED TO OPEN JSON FILE" << std::endl;
            std::exit(-1);
        }

        std::string idName;
        char animated;
        short int index;
        unsigned short int xTile;
        unsigned short int yTile;

        tileMap.clear();
        decTileMap.clear();

        bool collided = false;


        for (auto it = jsonFile.at("ids").begin(); it != jsonFile.at("ids").end();) {
            idName = it->get_ref<std::string &>();
            it++;
            animated = (it->get_ref<std::string &>())[0];
            it++;
            index = std::stoi(it->get_ref<std::string &>());
            it++;
            xTile = std::stoi(it->get_ref<std::string &>());
            it++;
            yTile = std::stoi(it->get_ref<std::string &>());
            it++;

            if (!tileMap.empty()) {
                for (auto &i : tileMap) {
                    if (i.getBlockNumberX() == xTile && i.getBlockNumberY() == yTile) {
                        //this will be decTileMap in the future, but for testing with copy and pasted data it is detected as repeated data so this is switched temporarily
                        tileMap.emplace_back(idName, animated, index, xTile, yTile);
                        collided = true;
                        break;
                    }
                }
            }
            if (!collided) {
                tileMap.emplace_back(idName, animated, index, xTile, yTile);
            } else {
                collided = false;
            }
    }
    unsigned int level[chunkSize * chunkSize];

    for(int i = 0; i < tileMap.size();i++) {
        level[i] = getTexture(tileMap.at(i).getTileName());
    }

    Tilemap map;
    if (!map.load("../Source/TextureManager/TileMap/atlas_48x.png",
                  sf::Vector2u(48, 48), level, chunkSize, chunkSize)) {
    }
    test->draw(map);
}



int MapFileSystem::getTexture(std::string textureName) {
    TileToNumberConverter & tileConverter = TileToNumberConverter::getInstance();
    return tileConverter.findValue(textureName);

}


void MapFileSystem::setTexture(
        int x, int y, int depth, std::string textureName) {
}
