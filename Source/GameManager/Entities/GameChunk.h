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
    void incrementUpdateTime(double time) {
        for (auto &i : referenceToAnimatedTiles) {
            for (auto &ii : i) {
                ii.second.second.second.at(ii.first.first) += time;
            }
        }
    }

//    double getUpdateTime() {
//        return this->passedTime;
//    }

    void updateTilesIfNeeded();

private:

    double timeToUpdate;
    bool updated = false;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::string fileSystemPath = "../Source/FileSystem/";

    static std::size_t number_of_files_in_directory(const std::filesystem::path &path);

    std::string fileName;

    std::vector<std::vector<Entity>> chunkWithLayers;

    std::vector<
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

    unsigned long long tileID;
    std::vector<int> animationTiles;
    std::vector<float> animationTimes;
    std::pair<double, double> position;
    sf::Texture *texture;

    std::vector<std::vector<int>> tiles;
    std::vector<Tilemap> tilemap;

    std::ifstream fileInput;
    std::string file;

    bool animate = false;
};


#endif //TRUGAMING_GAMECHUNK_H
