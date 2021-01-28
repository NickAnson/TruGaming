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
    bool udapteChunks = true;

    sf::RenderWindow *window;

    void chunkManagement();

    std::vector<sf::Vector2i> conversion;
    const std::vector<sf::Vector2i> rulesInitial = {sf::Vector2i(3, 3)};

    std::vector<GameChunk> chunksVisible;

    std::string convertChunkLocationToName(sf::Vector2<int> chunk);

    void rules();

    void intitalRules();


};


#endif //TRUGAMING_APPLICATION_H
