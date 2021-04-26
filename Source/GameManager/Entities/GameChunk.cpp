//
// Created by nicka on 1/1/2021.
//

#include <iostream>
#include "GameChunk.h"

GameChunk::GameChunk(std::pair<int, int> chunkNum, const std::string &currentMap) {


    file = fileSystemPath + currentMap + "/"
           + std::to_string(chunkNum.first) + "_" +
           std::to_string(chunkNum.second) + "/";

    if (!std::filesystem::is_directory(file)) {
        gameChunkState = State::gameChunkStates::chunk_NOTFOUND;
        return;
    }
    std::vector<int> layerTiles{};
    auto layerCount = 0;
    for (const auto &entry : std::filesystem::directory_iterator(file)) {
        if (is_digits(entry.path().stem().string())) {
            layerCount++;
            layerTiles.emplace_back(std::stoi(entry.path().stem().string()));
        }
    }

    setChunkNum(chunkNum);

    const std::vector<float> startPoint = {};
    const std::vector<int> startPoint0 = {};


    auto numberOfFileLayers = layerCount;
    chunkWithLayers.resize(numberOfFileLayers);
    tilemap.resize(numberOfFileLayers);
    referenceToAnimatedTiles.resize(numberOfFileLayers);
    tiles.resize(numberOfFileLayers);

    int numberOfLayers = 0;


    for (auto &layer : layerTiles) {

        count = 0;

        fileInput.open(file + std::to_string(layer) + ".json");

        //TODO: Handle Empty Files
        if (!fileInput) {
            std::cout <<
                      "ERROR: TILE NOT AVAIABLE : " <<
                      chunkNum.first << " " << chunkNum.second <<
                      " " << numberOfFileLayers <<
                      std::endl;

            exit(-10001);
        }

        Singleton::getInstance().jsonInput = nlohmann::json::parse(fileInput);
        for (int index = 0; index < Singleton::chunkSize * Singleton::chunkSize; index++) {


            std::vector<int> animationTiles;
            std::vector<float> animationTimes;
            std::pair<double, double> position;

            unsigned long long tileID = (Singleton::getInstance().jsonInput["tileID"].at(index).get<int>());
            if (tileID > 0) {
                tileID--;
            }

            for (auto &i : Singleton::getInstance().jsonInput["tileAnimation"]) {

                if (tileID == i["id"]) {

                    for (auto &animationIDs : i["animation"]) {
                        animationTiles.emplace_back(animationIDs["tileid"]);
                        animationTimes.emplace_back(animationIDs["duration"]);
                    }

                    tileID = animationTiles.front();

                    referenceToAnimatedTiles.at(numberOfLayers).emplace_back().first = std::pair(0, index);
                    referenceToAnimatedTiles.at(numberOfLayers).at(count).second =
                            std::pair(
                                    animationTiles,
                                    std::pair(
                                            animationTimes, std::vector<float>(animationTimes.size(), 0))
                            );
                    count++;
                }
            }

            tiles.at(numberOfLayers).emplace_back(tileID);

            position.first =
                    Singleton::getInstance().jsonInput["x"].get<int>() + (int) (((index % 32) * 48));
            position.second =
                    Singleton::getInstance().jsonInput["y"].get<int>() + (int) (((index / 32) * 48));
            chunkWithLayers.at(numberOfLayers).emplace_back(
                    tileID,
                    startPoint0,
                    startPoint,
                    numberOfLayers,
                    position,
                    Singleton::getInstance().tilemap
            );


        }


        tilemap.at(numberOfLayers).load(
                sf::Vector2u(52, 52),
                tiles.at(numberOfLayers),
                32,
                32);
        tilemap.at(numberOfLayers).setPosition(
                chunkWithLayers.at(numberOfLayers).front().getPosition().first,
                chunkWithLayers.at(numberOfLayers).front().getPosition().second
        );


        fileInput.close();

        numberOfLayers++;
    }


}


void GameChunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (gameChunkState != State::gameChunkStates::chunk_NOTFOUND) {
        for (auto &i : tilemap) {
            target.draw(i, states);
        }
    }
}

void GameChunk::updateTilesIfNeeded() const {
    if (gameChunkState != State::gameChunkStates::chunk_NOTFOUND) {
        for (unsigned long long index = 0; index < referenceToAnimatedTiles.size(); index++) {
            for (auto &i: referenceToAnimatedTiles.at(index)) {
                if (i.second.second.first.at(i.first.first) <= i.second.second.second.at(i.first.first)) {
                    i.second.second.second.at(i.first.first) = 0;
                    if (i.first.first == i.second.first.size() - 1) {
                        i.first.first = 0;
                    } else {
                        i.first.first++;
                    }
                    tiles.at(index).at(i.first.second) = i.second.first.at(i.first.first);
                }
            }
            tilemap.at(index).load(
                    sf::Vector2u(52, 52),
                    tiles.at(index),
                    32,
                    32);
        }
    }
}




