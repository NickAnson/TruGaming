
#ifndef TRUGAMING_MAPUPDATER_H
#define TRUGAMING_MAPUPDATER_H


#include <string>

class MapUpdater {

public:

    MapUpdater(const std::string &mapToUpdate);

    MapUpdater() = delete;

    void updateMap();

private:

    std::string map;

    const std::string fileSystemPath = "../Source/FileSystem/";
    const std::string mapEditorPath = "../Source/GameManager/MapEditor/";

    std::string jsonMap;


};


#endif //TRUGAMING_MAPUPDATER_H
