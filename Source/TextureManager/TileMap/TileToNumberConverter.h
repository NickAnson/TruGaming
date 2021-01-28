//
// Created by Nick on 1/21/2021.
//

#ifndef TRUGAMING_TILETONUMBERCONVERTER_H
#define TRUGAMING_TILETONUMBERCONVERTER_H


#include <map>
#include <string>

class TileToNumberConverter {

public:
    static TileToNumberConverter &getInstance() {
        static TileToNumberConverter instance;
        return instance;
    }

private:
    std::ifstream f;
    std::string tileMapToNumberLocation = "../Source/TextureManager/TileMap/tileToNumber.json";

    bool initialized = false;
    TileToNumberConverter() {

        setup();

    };
    static TileToNumberConverter instance;

public:
    TileToNumberConverter(TileToNumberConverter const &) = delete;
    void operator=(TileToNumberConverter const &) = delete;

    void setup() {
        f.open(tileMapToNumberLocation);
        nlohmann::json converter = nlohmann::json::parse(f);
        f.close();
        if(converter.is_null()) {
//            std::cout << "BAD FILE PATH 1001" << std::endl;
        }

        for (auto it = converter.begin(); it != converter.end();it++) {
            test[it.key()] = it.value();
        }
    }

    int findValue(std::string valueToFind) {
        if(test.contains(valueToFind)) {
            return test.at(valueToFind);
        } else {
            return 18;
        }
    }


    std::map<std::string, int> test;

};


#endif //TRUGAMING_TILETONUMBERCONVERTER_H
