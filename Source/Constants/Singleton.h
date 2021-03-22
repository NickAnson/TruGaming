
#ifndef TRUGAMING_SINGLETON_H
#define TRUGAMING_SINGLETON_H


#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "../../Dependencies/Nlohmann/json.hpp"

class Singleton {

public:
//    template<typename T>
//    T roundFloorMultiple(T value, T multiple) {
//        if (multiple == 0) return value;
//        return static_cast<T>(std::floor(static_cast<double>(value) / static_cast<double>(multiple)) *
//                              static_cast<double>(multiple));
//    }

    static Singleton &getInstance() {
        static Singleton instance;
        return instance;
    }

    sf::Texture tilemap;

    std::vector<sf::Sprite> defaultCharacterDownSprites;
    std::vector<sf::Sprite> defaultCharacterUpSprites;
    std::vector<sf::Sprite> defaultCharacterRightSprites;
    std::vector<sf::Sprite> defaultCharacterLeftSprites;


    std::vector<sf::Texture> tempTexture;

    nlohmann::json jsonInput;

    static const int chunkSize = 32;
    static const int tileSize = 48;

    float dt = 20.f;

    bool quitEditing = false;

    constexpr static const float movementSpeed = 100.f;

    sf::View defaultPlayerView;

    bool updateChunks = true;

private:

    Singleton() {
        tilemap.loadFromFile("../Source/TextureManager/TileMap/atlas_" + std::to_string(tileSize) + "x.png");

        defaultCharacterDownSprites.resize(4);
        defaultCharacterUpSprites.resize(4);
        defaultCharacterLeftSprites.resize(4);
        defaultCharacterRightSprites.resize(4);
        tempTexture.resize(16);

        tempTexture.at(0).loadFromFile("../Source/TextureManager/DefaultCharacter/left/left0.png");;
        defaultCharacterLeftSprites.at(0).setTexture(tempTexture.at(0));

        tempTexture.at(1).loadFromFile("../Source/TextureManager/DefaultCharacter/left/left1.png");;
        defaultCharacterLeftSprites.at(1).setTexture(tempTexture.at(1));

        tempTexture.at(2).loadFromFile("../Source/TextureManager/DefaultCharacter/left/left2.png");;
        defaultCharacterLeftSprites.at(2).setTexture(tempTexture.at(2));

        tempTexture.at(3).loadFromFile("../Source/TextureManager/DefaultCharacter/left/left3.png");;
        defaultCharacterLeftSprites.at(3).setTexture(tempTexture.at(3));


        tempTexture.at(4).loadFromFile("../Source/TextureManager/DefaultCharacter/right/right0.png");;
        defaultCharacterRightSprites.at(0).setTexture(tempTexture.at(4));

        tempTexture.at(5).loadFromFile("../Source/TextureManager/DefaultCharacter/right/right1.png");;
        defaultCharacterRightSprites.at(1).setTexture(tempTexture.at(5));

        tempTexture.at(6).loadFromFile("../Source/TextureManager/DefaultCharacter/right/right2.png");;
        defaultCharacterRightSprites.at(2).setTexture(tempTexture.at(6));

        tempTexture.at(7).loadFromFile("../Source/TextureManager/DefaultCharacter/right/right3.png");;
        defaultCharacterRightSprites.at(3).setTexture(tempTexture.at(7));


        tempTexture.at(8).loadFromFile("../Source/TextureManager/DefaultCharacter/up/up0.png");;
        defaultCharacterUpSprites.at(0).setTexture(tempTexture.at(8));

        tempTexture.at(9).loadFromFile("../Source/TextureManager/DefaultCharacter/up/up1.png");;
        defaultCharacterUpSprites.at(1).setTexture(tempTexture.at(9));

        tempTexture.at(10).loadFromFile("../Source/TextureManager/DefaultCharacter/up/up2.png");;
        defaultCharacterUpSprites.at(2).setTexture(tempTexture.at(10));

        tempTexture.at(11).loadFromFile("../Source/TextureManager/DefaultCharacter/up/up3.png");;
        defaultCharacterUpSprites.at(3).setTexture(tempTexture.at(11));


        tempTexture.at(12).loadFromFile("../Source/TextureManager/DefaultCharacter/down/down0.png");;
        defaultCharacterDownSprites.at(0).setTexture(tempTexture.at(12));

        tempTexture.at(13).loadFromFile("../Source/TextureManager/DefaultCharacter/down/down1.png");;
        defaultCharacterDownSprites.at(1).setTexture(tempTexture.at(13));

        tempTexture.at(14).loadFromFile("../Source/TextureManager/DefaultCharacter/down/down2.png");;
        defaultCharacterDownSprites.at(2).setTexture(tempTexture.at(14));

        tempTexture.at(15).loadFromFile("../Source/TextureManager/DefaultCharacter/down/down3.png");;
        defaultCharacterDownSprites.at(3).setTexture(tempTexture.at(15));

    };
    static Singleton instance;

    int currentError = 0;

public:
    Singleton(Singleton const &) = delete;

    void operator=(Singleton const &) = delete;

    sf::VideoMode computerScreen = sf::VideoMode::getDesktopMode();

    void print_err(std::string index = "") {
        std::cout << "HERE " << index << " : " << currentError << std::endl;
        currentError++;
    }

};

#endif //TRUGAMING_SINGLETON_H
