//
// Created by Nick on 1/19/2021.
//

#ifndef TRUGAMING_TILE_H
#define TRUGAMING_TILE_H


#include <string>

class Tile {
public:

    Tile(unsigned short int tileNameTemp, unsigned short int animatedTemp, signed short int zHeightTemp,
         unsigned short int blockNumberTemp) {
        tileName = tileNameTemp;
        animated = animatedTemp;
        zHeight = zHeightTemp;
        blockNumber = blockNumberTemp;

    }

    unsigned short int getTileName() const {
        return tileName;
    }

    void setTileName(unsigned short int tileNameTemp) {
        Tile::tileName = tileNameTemp;
    }

    unsigned short int getAnimated() const {
        return animated;
    }

    void setAnimated(char animatedTemp) {
        Tile::animated = animatedTemp;
    }

    signed short int getZHeight() const {
        return zHeight;
    }

    void setZHeight(short zHeightTemp) {
        Tile::zHeight = zHeightTemp;
    }

    unsigned short int getBlockNumber() const {
        return blockNumber;
    }

    void setBlockNumber(unsigned short blockNumber) {
        Tile::blockNumber = blockNumber;
    }


private:
    Tile() = delete;

    unsigned short int tileName;
    unsigned short int animated;
    signed short int zHeight;
    unsigned short int blockNumber;

};


#endif //TRUGAMING_TILE_H
