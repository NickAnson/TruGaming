
#ifndef TRUGAMING_MAPUPDATER_H
#define TRUGAMING_MAPUPDATER_H


#include <string>
#include <filesystem>
#include <iostream>

class MapUpdater {

public:


    MapUpdater() = default;

    void updateMap();

    void setMapString(std::string newMap) {
        basemapString = newMap;
        map = fileSystemPath + newMap;
    }

private:

    std::string basemapString;
    std::string map;

    const std::string fileSystemPath = "../Source/FileSystem/";
    const std::string mapEditorPath = "../Source/GameManager/MapEditor/";

    std::string jsonMap;

    void deleteDirectoryContents(const std::string &dir_path) {
        for (const auto &entry : std::filesystem::directory_iterator(dir_path)) {
            for (const auto &test : std::filesystem::directory_iterator(
                    dir_path + "/" + entry.path().stem().string())) {
                if (is_digits(test.path().stem().string())) {
                    std::filesystem::remove(test.path().string());
                }
            }
        }
    }

    bool is_digits(const std::string &str) {
        return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
    }

};


#endif //TRUGAMING_MAPUPDATER_H
