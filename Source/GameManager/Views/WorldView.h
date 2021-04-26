//
// Created by Nick on 3/25/2021.
//

#ifndef TRUGAMING_WORLDVIEW_H
#define TRUGAMING_WORLDVIEW_H


#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../GameText/GameText.h"
#include "../Entities/GameChunk.h"
#include "View.h"
#include "../MapEditor/MapUpdater.h"
#include "../Entities/Player.h"
#include "../../Audio/Audio.h"

class WorldView : public View {
public:

    WorldView(std::pair<int, int> viewSize, sf::RenderWindow &renderWindow, const std::string &currentMap) {
        this->sizeOfView = viewSize;
        this->currentMapLoaded = currentMap;
        load(renderWindow);
    }


    void load(sf::RenderWindow &renderWindow) override;

    void windowLogic() override;

    State::viewOpened getView() {
        return this->currentView;
    }

    void setView(State::viewOpened newView) {
        this->currentView = newView;
    }

    void setEscapeKeyState(State::popUpView escapeState) {
        this->escapedKeyPressed = escapeState;
    }

    State::popUpView getEscapeState() {
        return this->escapedKeyPressed;
    }

    State::viewOpened &getNextView() {
        return this->nextView;
    }

    void setNextView(State::viewOpened newState) {
        this->nextView = newState;
    }

private:
    const std::string fileSystemPath = "../Source/FileSystem";

    std::string currentMapLoaded = "";
    Audio background{"world/background.ogg", true};

    mutable State::popUpView escapedKeyPressed = {State::popUpView::popup_NONE};
    mutable sf::RectangleShape blurredBackground;
    mutable sf::RectangleShape optionBox;

    State::viewOpened currentView{State::viewOpened::screen_WORLD};

    sf::Event event{};

    sf::View gameView;

    std::pair<int, int> sizeOfView{};


    void updateFPS(sf::View &view);

    void updateChunkInfo();

    void updateChunkText(sf::View &gameFrame);

    void updateChunks();

    std::vector<GameChunk> gameChunksAroundPlayer;

    sf::RenderWindow *window;

    std::vector<sf::Vector2i> conversion;

    std::pair<int, int> currentChunk{0, 0};


    mutable sf::Clock animationClock;

    sf::Vector2f deltaOffSet{0, 0};

    sf::Vector2f prevPos{0, 0};
    sf::Vector2f curPos{0, 0};
    sf::Clock clock;

    sf::Clock clock1;

    std::vector<std::pair<int, int>> nearbyOldChunks;
    std::vector<std::pair<int, int>> nearbyNewChunks;

    Player player;

    MapUpdater mapUpdater;


    GameText fpsCounter{GameText::FONTS::ARIAL};
    GameText mosPosXText{GameText::FONTS::ARIAL};
    GameText mosPosYText{GameText::FONTS::ARIAL};

    GameText quit{GameText::FONTS::GAME_FONT_0};
    GameText resume{GameText::FONTS::GAME_FONT_0};
    GameText save{GameText::FONTS::GAME_FONT_0};

    sf::Rect<float> quitBox;
    sf::Rect<float> resumeBox;
    sf::Rect<float> saveBox;

    State::viewOpened nextView{State::viewOpened::screen_WORLD};

    void updateAnimationTiles() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        window->setView(gameView);


        for (auto &i : gameChunksAroundPlayer) {
            target.draw(i, states);
        }
        target.draw(player.getSprite());


        if (this->escapedKeyPressed == State::popUpView::popup_ESCAPE) {

            target.draw(fpsCounter);
            target.draw(mosPosXText);
            target.draw(mosPosYText);

            target.draw(blurredBackground);
            target.draw(optionBox);
            target.draw(quit);
            target.draw(resume);
            target.draw(save);
        } else {
            updateAnimationTiles();
            target.draw(fpsCounter);
            target.draw(mosPosXText);
            target.draw(mosPosYText);
        }


    };

    std::vector<std::pair<int, int>> find(int radius, std::pair<int, int> currentChunk) {
        std::vector<std::pair<int, int>> chunks;
        for (int row = 0; row <= radius; row++) {
            for (int column = 0; column <= radius; column++) {
                if (row == 0 && column == 0) {
                    chunks.emplace_back(currentChunk.first + column, currentChunk.second + row);
                    continue;
                }
                if (column == 0) {
                    chunks.emplace_back(currentChunk.first + column, currentChunk.second + row);
                    chunks.emplace_back(currentChunk.first + column, currentChunk.second - row);
                } else if (row == 0) {
                    chunks.emplace_back(currentChunk.first + column, currentChunk.second - row);
                    chunks.emplace_back(currentChunk.first - column, currentChunk.second - row);
                } else {
                    chunks.emplace_back(currentChunk.first + column, currentChunk.second + row);
                    chunks.emplace_back(currentChunk.first - column, currentChunk.second + row);
                    chunks.emplace_back(currentChunk.first + column, currentChunk.second - row);
                    chunks.emplace_back(currentChunk.first - column, currentChunk.second - row);
                }
            }
        }
        return chunks;
    }

    void updatePositionInWorldLeaving() {

        std::ifstream chunkFile;
        nlohmann::json jsonInput;
        std::ofstream outputFile;

        if (!std::filesystem::exists(
                fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                std::to_string(currentChunk.second))) {
            std::filesystem::create_directory(
                    fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                    std::to_string(currentChunk.second) + "/" + "custom.json");
        }

        chunkFile.open(fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                       std::to_string(currentChunk.second) + "/" + "custom.json");
        chunkFile >> jsonInput;
        outputFile.open(fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                        std::to_string(currentChunk.second) + "/" + "custom.json");

        if (!chunkFile) {
            std::cout << "ERROR: CHUNK FILE CANT BE EDITED" << std::endl;
            exit(-132);
        }

        jsonInput["playerPosition"] = {
                {"x", gameView.getCenter().x},
                {"y", gameView.getCenter().y}
        };

        outputFile << std::setw(4) << jsonInput << std::endl;

        chunkFile.close();
        outputFile.close();
    }

    std::pair<float, float> getEnterPositionInMap() {
        std::ifstream chunkFile;
        nlohmann::json jsonInput;

        if (!std::filesystem::exists(
                fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                std::to_string(currentChunk.second))) {
            std::filesystem::create_directory(
                    fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                    std::to_string(currentChunk.second));
        }

        chunkFile.open(fileSystemPath + "/" + currentMapLoaded + "/" + std::to_string(currentChunk.first) + "_" +
                       std::to_string(currentChunk.second) + "/" + "custom.json");
        chunkFile >> jsonInput;

        if (!chunkFile) {
            std::cout << "ERROR: CHUNK FILE CANT BE EDITED" << std::endl;
            exit(-133);
        }
        int x;
        int y;
        if (jsonInput["playerPosition"]["x"].is_null()) {
            x = 0;
            y = 0;
        } else {

            x = jsonInput["playerPosition"]["x"].get<float>();
            y = jsonInput["playerPosition"]["y"].get<float>();
        }

        chunkFile.close();

        return std::pair(x, y);
    }


};


#endif //TRUGAMING_WORLDVIEW_H