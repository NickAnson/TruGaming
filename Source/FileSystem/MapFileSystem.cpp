//
// Created by nicka on 1/1/2021.
//

#include <iostream>
#include "MapFileSystem.h"
#include "../TextureManager/Tilemap.h"

MapFileSystem::MapFileSystem(std::string fileName) {

    std::cout << fileName << std::endl;

    std::ifstream f;
    f.open(fileName);

    nlohmann::json jsonFile = nlohmann::json::parse(f);

    auto arrayOfTiles = jsonFile.at("ids");

    for (auto it = arrayOfTiles.begin(); it != arrayOfTiles.end();) {
        std::cout << "ID: " << it.value() << std::endl;
        it++;
        std::cout << "ANIMATED: " << it.value() << std::endl;
        it++;
        std::cout << "INDEX_LEVEL: " << it.value() << std::endl;
        it++;
        std::cout << "xChunkTile: " << it.value() << std::endl;
        it++;
        std::cout << "yChunkTile: " << it.value() << std::endl;
        it++;
    }


    if (jsonFile.is_null()) {
        std::cout << "FAILED TO OPEN JSON FILE" << std::endl;
        std::exit(-1);
    }

    short sqaure = 15;
    unsigned int level[sqaure * sqaure];

    for (int i = 0; i < arrayOfTiles.size(); i++) {
        level[i] = getTexture(arrayOfTiles[i]);
    }

    // create the tilemap from the level definition
    Tilemap map;
    if (!map.load("../Source/TextureManager/TileMap/atlas_48x.png",
                  sf::Vector2u(48, 48), level, sqaure, sqaure)) {

    }
}

int MapFileSystem::getTexture(std::string textureName) {
    if (textureName == "grass") {
        return 1;
    } else {
        return 0;
    }

}


void MapFileSystem::setTexture(
        int x, int y, int depth, std::string textureName) {
}
