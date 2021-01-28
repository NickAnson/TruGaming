//
// Created by nicka on 1/1/2021.
//

#include <sstream>
#include <filesystem>
#include "GameChunk.h"
#include "../TextureManager/TileMap/TileToNumberConverter.h"


std::vector<Tile> GameChunk::convertToTile(const std::string &fileName) {
    std::vector<Tile> chunkTiles;

    std::ifstream f(fileName);
    std::string line;
    int i = 0;
    while (getline(f, line)) {

        std::string item;
        std::istringstream ss(line);

        getline(ss, item, ' ');
        std::string param1 = item;
        getline(ss, item, ' ');
        char param2 = item[0];
        getline(ss, item, ' ');
        signed short int param3 = std::stoi(item);

        chunkTiles.emplace_back(Tile(param1, param2, param3, i));
        i++;

        ss.clear();
    }


    f.close();

    return chunkTiles;
}


GameChunk::GameChunk(const std::string &fileName, sf::RenderWindow &test, sf::Vector2i &chunkNumberTemp) {

    if (!std::filesystem::exists(fileName)) {
        std::filesystem::copy("../Source/FileSystem/x_x.chunk", fileName);
    }

    tileMapRenderWindow = &test;
    tileMapLocation = {chunkNumberTemp.x * 1536, chunkNumberTemp.y * 1536};
    tileMap = fileName;

    map.setPosition(tileMapLocation.x, tileMapLocation.y);
    setChunkNumber(chunkNumberTemp);
}


void GameChunk::draw() {

    if (update) {
        chunks = convertToTile(tileMap);
        for (int i = 0; i < chunks.size(); i++) {
            level[i] = getTexture(chunks.at(i).getTileName());
        }
        if (!map.load("../Source/TextureManager/TileMap/atlas_48x.png",
                      sf::Vector2u(48, 48), level, chunkSize, chunkSize)) {
        }
        update = false;
    }
    tileMapRenderWindow->draw(map);
}

int GameChunk::getTexture(std::basic_string<char> textureName) {
    TileToNumberConverter &tileConverter = TileToNumberConverter::getInstance();
    return tileConverter.findValue(std::move(textureName));

}

sf::Vector2i GameChunk::getChunkNumber() {
    return chunkNumber;
}

void GameChunk::setChunkNumber(sf::Vector2i &number) {
    chunkNumber = number;
}

