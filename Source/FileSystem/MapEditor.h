//
// Created by Nick on 1/25/2021.
//

#ifndef TRUGAMING_MAPEDITOR_H
#define TRUGAMING_MAPEDITOR_H

#include "string"

class MapEditor {

    void editMap();

    void changeTile(unsigned short blockNumber, const std::string &chunk, const std::string &newTileObject);
};


#endif //TRUGAMING_MAPEDITOR_H
