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
    while (getline(f, line) && i < Singleton::getInstance().chunkSize * Singleton::getInstance().chunkSize) {

        std::string item;
        std::istringstream ss(line);

        getline(ss, item, ' ');
        unsigned short int param1 = std::stoi(item);
        getline(ss, item, ' ');
        unsigned short int param2 = std::stoi(item);
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
               std::to_string(int(renderWindow.getView().getCenter().x /
                                  (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)) +
                              chunkToLoadTemp.first) + "_" +
               std::to_string(int(renderWindow.getView().getCenter().y /
                                  (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)) +
                              chunkToLoadTemp.second) +
               ".chunk";


    if (!std::filesystem::exists(fileName)) {
        std::filesystem::copy("../Source/FileSystem/x_x.chunk", fileName);
    }

    convertToTile();

    for (unsigned short int i = 0; i < chunks.size(); i++) {
        level[i] = chunks.at(i).getTileName();
    }

    map.load(level, 32, 32);


    map.setPosition((int(renderWindow.getView().getCenter().x /
                         (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)) +
                     chunkToLoadTemp.first) * (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize),
                    (int(renderWindow.getView().getCenter().y /
                         (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)) +
                     chunkToLoadTemp.second) *
                    (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize));


}


void GameChunk::draw() {
    tileMapRenderWindow->draw(map);
}




