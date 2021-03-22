//
// Created by nicka on 12/2/2020.
//

#ifndef TRUGAMING_APPLICATION_H
#define TRUGAMING_APPLICATION_H


#include "GameManager/GameText/GameText.h"
#include "GameManager/Entities/GameChunk.h"

class Application {
public:
    Application(sf::RenderWindow &renderWindow) {
        window = &renderWindow;
    }

    void run();


    void setup();

private:

    sf::View gameView;

    void updateFPS(sf::Clock &clock, sf::View &view);

    void updateChunkInfo();

    void updateChunkText(sf::View &gameFrame);

    void updateChunks();

    void drawChunks(sf::RenderWindow *renderWindow);

    std::vector<GameChunk> gameChunksAroundPlayer;

    sf::RenderWindow *window;

    std::vector<sf::Vector2i> conversion;

    std::pair<int, int> currentChunk{0, 0};

    sf::Vector2f mouse_world;

    sf::Clock animationClock;

    sf::Vector2f deltaOffSet{0, 0};

    std::vector<std::pair<int, int>> nearbyOldChunks;
    std::vector<std::pair<int, int>> nearbyNewChunks;


    GameText fpsCounter{GameText::FONTS::ARIAL};
    GameText mosPosXText{GameText::FONTS::ARIAL};
    GameText mosPosYText{GameText::FONTS::ARIAL};

    void updateAnimationTiles();


};


#endif //TRUGAMING_APPLICATION_H
