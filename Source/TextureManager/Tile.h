//
// Created by Nick on 1/19/2021.
//

#ifndef TRUGAMING_TILE_H
#define TRUGAMING_TILE_H


#include <string>

class Tile {
public:

    Tile(std::string tileNameTemp, char animatedTemp, signed short int zHeightTemp, unsigned short int blockNumberXTemp,
         unsigned short int blockNumberYTemp) {
        tileName = tileNameTemp;
        animated = animatedTemp;
        zHeight = zHeightTemp;
        blockNumberX = blockNumberXTemp;
        blockNumberY = blockNumberYTemp;

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

    unsigned short getBlockNumberX() const {
        return blockNumberX;
    }

    void setBlockNumberX(unsigned short blockNumberXTemp) {
        Tile::blockNumberX = blockNumberXTemp;
    }

    unsigned short getBlockNumberY() const {
        return blockNumberY;
    }

    void setBlockNumberY(unsigned short blockNumberYTemp) {
        Tile::blockNumberY = blockNumberYTemp;
    }
    Tile() = delete;

private:

    char animated;
    signed short int zHeight;
    unsigned short int blockNumberX;
    unsigned short int blockNumberY;
    std::string tileName;
};


#endif //TRUGAMING_TILE_H
