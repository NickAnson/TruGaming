//
// Created by nicka on 1/1/2021.
//

#ifndef TRUGAMING_GAMECHUNK_H
#define TRUGAMING_GAMECHUNK_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Constants/Singleton.h"
#include "Entity.h"
#include "Tilemap.h"
#include <filesystem>
#include <fstream>
#include "../States/State.h"


class GameChunk : public sf::Drawable {
public:
    GameChunk(std::pair<int, int> chunkNum, const std::string &map);

    std::pair<int, int> getChunkNum() const {
        return this->chunkIndex;
    }

    void setChunkNum(std::pair<int, int> chunkNum) {
        this->chunkIndex = chunkNum;
    }

//    void setUpdateDelay(double time) {
//        this->passedTime = time;
//    }
    void incrementUpdateTime(double time) const {
        for (auto &i : referenceToAnimatedTiles) {
            for (auto &ii : i) {
                ii.second.second.second.at(ii.first.first) += time;
            }
        }
    }

    bool is_digits(const std::string &str) {
        return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
    }

//    double getUpdateTime() {
//        return this->passedTime;
//    }

    void updateTilesIfNeeded() const;

private:


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::string fileSystemPath = "../Source/FileSystem/";


    std::string fileName;

    std::vector<std::vector<Entity>> chunkWithLayers;

    mutable std::vector<
            std::vector<
                    std::pair<
                            std::pair<unsigned long long, unsigned long long>,
                            std::pair<
                                    std::vector<int>,
                                    std::pair<
                                            std::vector<float>,
                                            std::vector<float>
                                    >
                            >
                    >
            >
    > referenceToAnimatedTiles;

    int count = 0;
    std::pair<int, int> chunkIndex;

//    std::vector<std::vector<std::reference_wrapper<Entity>>> animatedTiles;


    mutable std::vector<std::vector<int>> tiles;
    mutable std::vector<Tilemap> tilemap;

    State::gameChunkStates gameChunkState{State::gameChunkStates::chunk_NORMAL};

    std::ifstream fileInput;
    std::string file;

};


#endif //TRUGAMING_GAMECHUNK_H