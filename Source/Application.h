//
// Created by nicka on 12/2/2020.
//

#ifndef TRUGAMING_APPLICATION_H
#define TRUGAMING_APPLICATION_H


#include "FileSystem/GameChunk.h"

class Application {
public:
    Application(sf::RenderWindow &renderWindow) {
        window = &renderWindow;
    }
    void test();


private:

    sf::RenderWindow *window;

    void chunkManagement();

    std::vector<sf::Vector2i> conversion;

    GameChunk viewableChunk[48];

    void rules();

    bool insideView(const sf::View &view, sf::Vector2i point);

    sf::FloatRect viewCoorindates;

    sf::FloatRect &getViewCoordinates(const sf::View &view);

    bool newChunks = true;
    sf::Vector2i deltaOffSet{0, 0};
};


#endif //TRUGAMING_APPLICATION_H
