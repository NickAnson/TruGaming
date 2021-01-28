//
// Created by Nick on 1/19/2021.
//

#ifndef TRUGAMING_TILE_H
#define TRUGAMING_TILE_H


#include <string>

class Tile {
public:

    Tile(std::string tileNameTemp, char animatedTemp, signed short int zHeightTemp,
         unsigned short int blockNumberTemp) {
        tileName = tileNameTemp;
        animated = animatedTemp;
        zHeight = zHeightTemp;
        blockNumber = blockNumberTemp;

    }

    std::string getTileName() const {
        return tileName;
    }

    void setTileName(std::string tileNameTemp) {
        Tile::tileName = tileNameTemp;
    }

    char getAnimated() const {
        return animated;
    }

    void setAnimated(char animatedTemp) {
        Tile::animated = animatedTemp;
    }

    short getZHeight() const {
        return zHeight;
    }

    void setZHeight(short zHeightTemp) {
        Tile::zHeight = zHeightTemp;
    }

    unsigned short getBlockNumber() const {
        return blockNumber;
    }

    void setBlockNumber(unsigned short blockNumber) {
        Tile::blockNumber = blockNumber;
    }


private:
    Tile() = delete;

    char animated;
    signed short int zHeight;
    unsigned short int blockNumber;
    std::string tileName;

};


#endif //TRUGAMING_TILE_H
