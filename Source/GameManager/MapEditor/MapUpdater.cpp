#include "MapUpdater.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "../../../Dependencies/Nlohmann/json.hpp"
#include "../../Constants/Singleton.h"
#include <filesystem>


MapUpdater::MapUpdater(const std::string &mapToUpdate) {
    map = fileSystemPath + mapToUpdate;

    jsonMap = mapEditorPath + mapToUpdate + ".json";
}

void MapUpdater::updateMap() {
    nlohmann::json jsonInput;
    std::ifstream fileInput(jsonMap);
    fileInput >> jsonInput;

    long chunkXCoord;
    long chunkYCoord;

    std::ofstream chunkFile;

    nlohmann::json outputFile;

    int counter = 0;
    for (auto &i : jsonInput["layers"]) {
        for (auto &chunks : i["chunks"]) {
            chunkXCoord = chunks["x"].get<int>();
            chunkYCoord = chunks["y"].get<int>();

            if (!std::filesystem::exists(map + "/" +
                                         std::to_string(chunkXCoord / 32) +
                                         "_"
                                         + std::to_string(chunkYCoord / 32))) {

                std::filesystem::create_directory(map + "/" +
                                                  std::to_string(chunkXCoord / 32) +
                                                  "_"
                                                  + std::to_string(chunkYCoord / 32));
            }

            chunkFile.open(map + "/" +
                           std::to_string(chunkXCoord / 32) + "_" + std::to_string(chunkYCoord / 32)
                           + "/" + std::to_string(counter) + ".json");

            if (!chunkFile) {
                std::cout << "ERROR: CHUNK FILE CANT BE EDITED" << std::endl;
                exit(-1);
            }

            outputFile["tileID"] = chunks["data"];
            outputFile["x"] = chunkXCoord * 48;
            outputFile["y"] = chunkYCoord * 48;
            outputFile["tileAnimation"] = jsonInput["tilesets"].at(0)["tiles"];

            chunkFile << std::setw(4) << outputFile << std::endl;

            chunkFile.close();
        }
        counter++;
    }
}
