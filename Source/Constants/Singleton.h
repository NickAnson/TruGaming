//
// Created by Nick on 1/21/2021.
//

#ifndef TRUGAMING_SINGLETON_H
#define TRUGAMING_SINGLETON_H


#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

class Singleton {

public:
    template<typename T>
    T roundFloorMultiple(T value, T multiple) {
        if (multiple == 0) return value;
        return static_cast<T>(std::floor(static_cast<double>(value) / static_cast<double>(multiple)) *
                              static_cast<double>(multiple));
    }

    static Singleton &getInstance() {
        static Singleton instance;
        return instance;
    }

    sf::Texture m_tileset;

    static const int chunkSize = 32;
    static const int tileSize = 48;
    bool tileToEdit = false;
    bool quitEditing = false;
    \

    bool updateChunks = true;

private:

    Singleton() {
        m_tileset.loadFromFile("../Source/TextureManager/TileMap/atlas_" + std::to_string(tileSize) + "x.png");
    };
    static Singleton instance;

public:
    Singleton(Singleton const &) = delete;

    void operator=(Singleton const &) = delete;

    sf::VideoMode computerScreen = sf::VideoMode::getDesktopMode();

};


#endif //TRUGAMING_SINGLETON_H
