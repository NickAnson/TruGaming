//
// Created by nicka on 1/1/2021.
//

#include <filesystem>
#include <iostream>
#include "GameChunk.h"


void GameChunk::convertToTile() {

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

        chunks.emplace_back(Tile(param1, param2, param3, i));
        i++;

    }
    f.close();

}


GameChunk::GameChunk(sf::RenderWindow &renderWindow, std::pair<signed short int, signed short int> chunkToLoadTemp) {
    tileMapRenderWindow = &renderWindow;


    fileName = "../Source/FileSystem/" +
               std::to_string(int(renderWindow.getView().getCenter().x / 1536) + chunkToLoadTemp.first) + "_" +
               std::to_string(int(renderWindow.getView().getCenter().y / 1536) + chunkToLoadTemp.second) +
               ".chunk";


    if (!std::filesystem::exists(fileName)) {
        std::filesystem::copy("../Source/FileSystem/x_x.chunk", fileName);
    }

    convertToTile();

    for (unsigned short int i = 0; i < chunks.size(); i++) {
        level[i] = TileToNumberConverter::getInstance().findValue(chunks.at(i).getTileName());
    }

    map.load(level);
    map.setPosition(int(renderWindow.getView().getCenter().x / 1536 + chunkToLoadTemp.first) * 1536,
                    int(renderWindow.getView().getCenter().y / 1536 + chunkToLoadTemp.second) * 1536);

}


void GameChunk::draw() {
    tileMapRenderWindow->draw(map);
}




