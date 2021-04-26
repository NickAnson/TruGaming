#include "MapUpdater.h"
#include <iostream>
#include <fstream>
#include "../../../Dependencies/Nlohmann/json.hpp"


void MapUpdater::updateMap() {
    if (!std::filesystem::is_directory(map)) {
        std::filesystem::create_directory(map);
    }
    jsonMap = mapEditorPath + basemapString + ".json";
    if (!std::filesystem::exists(jsonMap)) {
        std::cout << "MAP DATA NOT AVAILABLE!" << std::endl;
        std::exit(-101);
    }

    std::ifstream testInput(jsonMap);
    deleteDirectoryContents(map);
    nlohmann::json jsonInput;
    testInput >> jsonInput;
    std::ifstream fileInput;

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
                exit(-132);
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


    std::ofstream customFileOutput;
    std::ifstream infileAlready;

    nlohmann::json customOutput;


    int count = 0;
    bool found = false;
    for (auto &i : jsonInput["layers"]) {
        if (i["name"].get<std::string>() == "walk_false") {
            for (auto &objects : i["objects"]) {

                if (!std::filesystem::exists(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                             std::to_string(objects["y"].get<int>() / 1536))) {
                    std::filesystem::create_directory(map + "/" +
                                                      std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                                      std::to_string(objects["y"].get<int>() / 1536));
                }

                if (!std::filesystem::exists(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                             std::to_string(objects["y"].get<int>() / 1536) + "/" + "custom" +
                                             ".json")) {
                    std::ofstream outfile(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                          std::to_string(objects["y"].get<int>() / 1536) + "/" + "custom" + ".json");
                    outfile << "{}" << std::endl;
                    outfile.close();
                }
                infileAlready.open(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                   std::to_string(objects["y"].get<int>() / 1536) + "/" + "custom" + ".json");


                infileAlready >> customOutput;

                customFileOutput.open(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                      std::to_string(objects["y"].get<int>() / 1536) + "/" + "custom" + ".json");


                if (!infileAlready) {
                    std::cout << "ERROR: CHUNK FILE CANT BE EDITED" << std::endl;
                    exit(-154);
                }


                customOutput["walk_false"][count] = {
                        {"x",      objects["x"].get<double>()},
                        {"y",      objects["y"].get<double>()},
                        {"width",  objects["width"].get<double>()},
                        {"height", objects["height"].get<double>()}
                };

                customFileOutput << std::setw(4) << customOutput << std::endl;


                customFileOutput.close();
                infileAlready.close();

                count++;

            }
        } else if (i["name"].get<std::string>() == "enter_building") {
            count = 0;
            for (auto &objects : i["objects"]) {

                if (!std::filesystem::exists(map + "/" +
                                             std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                             std::to_string(objects["y"].get<int>() / 1536))) {

                    std::filesystem::create_directory(map + "/" +
                                                      std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                                      std::to_string(objects["y"].get<int>() / 1536));
                }


                infileAlready.open(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                   std::to_string(objects["y"].get<int>() / 1536) + "/" + "custom" + ".json");

                infileAlready >> customOutput;

                customFileOutput.open(map + "/" + std::to_string(objects["x"].get<int>() / 1536) + "_" +
                                      std::to_string(objects["y"].get<int>() / 1536) + "/" + "custom" + ".json");

                if (!customFileOutput) {
                    std::cout << "ERROR: CHUNK FILE CANT BE EDITED" << std::endl;
                    exit(-195);
                }
                customOutput["enter_building"][count] = {
                        {"map",    objects["name"].get<std::string>()},
                        {"x",      objects["x"].get<double>()},
                        {"y",      objects["y"].get<double>()},
                        {"width",  objects["width"].get<double>()},
                        {"height", objects["height"].get<double>()},
                };
                customFileOutput << std::setw(4) << customOutput << std::endl;

                customFileOutput.close();
                infileAlready.close();

                count++;

            }
        }
    }
}

bool is_empty(std::ifstream &pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

