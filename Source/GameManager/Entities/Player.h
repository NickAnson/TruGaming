
#ifndef TRUGAMING_PLAYER_H
#define TRUGAMING_PLAYER_H


#include <string>
#include <SFML/Graphics.hpp>
#include "../../Constants/Singleton.h"


class Player {
public:
    enum CurrentDirection {
        UP, DOWN, LEFT, RIGHT
    };

    explicit Player(
            std::vector<sf::Sprite> &upSpriteTEMP = Singleton::getInstance().defaultCharacterUpSprites,
            std::vector<sf::Sprite> &downSpriteTEMP = Singleton::getInstance().defaultCharacterDownSprites,
            std::vector<sf::Sprite> &leftSpriteTEMP = Singleton::getInstance().defaultCharacterLeftSprites,
            std::vector<sf::Sprite> &rightSpriteTEMP = Singleton::getInstance().defaultCharacterRightSprites,
            sf::Vector2f positionTemp = sf::Vector2f(0, 0), CurrentDirection playerDirectionTEMP = DOWN,
            double animationTimeTEMP = 500,
            sf::View &currentViewTemp = Singleton::getInstance().defaultPlayerView) {

        this->spriteDraw = downSpriteTEMP.at(1);
        this->position = positionTemp;

        this->upSprite = upSpriteTEMP;
        this->downSprite = downSpriteTEMP;
        this->leftSprite = leftSpriteTEMP;
        this->rightSprite = rightSpriteTEMP;

        this->playerOldDirection.emplace_back(playerDirectionTEMP);

        playerAnimationTime = animationTimeTEMP;

        currentView = &currentViewTemp;

        newChunk = {0, 0};
        oldChunk = {INT32_MAX, INT32_MAX};
    }


private:
    const std::string fileSystemPath = "../Source/FileSystem/";
    std::string currentMap = "";

    double playerAnimationTime;
    double animationUpTime = 0;
    double animationDownTime = 0;
    double animationLeftTime = 0;
    double animationRightTime = 0;
    unsigned short int currentStateOfAnimationUp = 1;
    unsigned short int currentStateOfAnimationDown = 1;
    unsigned short int currentStateOfAnimationLeft = 1;
    unsigned short int currentStateOfAnimationRight = 1;

    std::string nextWorld = "";

    bool erased = false;
    std::vector<CurrentDirection> playerNewDirection;
    std::vector<CurrentDirection> playerOldDirection;

    std::vector<sf::Sprite> upSprite;
    std::vector<sf::Sprite> downSprite;
    std::vector<sf::Sprite> rightSprite;
    std::vector<sf::Sprite> leftSprite;

    std::vector<std::pair<sf::Rect<float>, std::string>> newWorld;
    std::vector<sf::Rect<float>> unwalkable;
    std::pair<float, float> newPos;
    std::pair<int, int> oldChunk;
    std::pair<int, int> newChunk;

    std::ifstream interactionFile;
    nlohmann::json jsonInteractionFile;

    sf::View *currentView;


    mutable sf::Sprite spriteDraw;

    sf::Vector2f position;

    bool downCheck() {
        return (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)));
    }

    bool leftCheck() {
        return (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)));
    }

    bool rightCheck() {
        return (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)));

    }

    bool upCheck() {
        return (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)));
    }

public:
    std::string getNextWorld() {
        return this->nextWorld;
    }

    void setNextWorld(std::string nextWorldTemp) {
        this->nextWorld = nextWorldTemp;
    }

    void setView(sf::View &view) {
        currentView = &view;
    }

    sf::Sprite &getSprite() const {
        return spriteDraw;
    }

    sf::Vector2f getPosition() {
        return spriteDraw.getPosition();
    }

    void setPosition(sf::Vector2f pos) {
        Player::position = pos;
        spriteDraw.setPosition(pos);
    }

    void setPosition(const float x, const float y) {
        Player::position.x = x;
        Player::position.y = y;
        spriteDraw.setPosition(x, y);
    }

    void movePlayer(float x, float y) {
        position.x += x;
        position.y += y;
        spriteDraw.move(x, y);
    }

    void addElapsedTime(double timeElapsed, std::vector<CurrentDirection> &directionToElapse) {
        for (auto &i : directionToElapse) {
            if (i == UP) {
                animationUpTime += timeElapsed;
            } else if (i == DOWN) {
                animationDownTime += timeElapsed;
            } else if (i == LEFT) {
                animationLeftTime += timeElapsed;
            } else if (i == RIGHT) {
                animationRightTime += timeElapsed;
            }
        }
    }

    void truncatePos() {
        spriteDraw.setPosition(std::floor(spriteDraw.getPosition().x), std::floor(spriteDraw.getPosition().y));
    }

    void updatePos(const std::pair<float, float> &newPosTemp) {
        this->newPos = newPosTemp;
        newChunk.first = this->newPos.first / 1536.f;
        newChunk.second = this->newPos.second / 1536.f;
    }

    bool isNewChunk() {
        if (newChunk.first - oldChunk.first != 0 && newChunk.second - oldChunk.second) {
            return true;
        } else {
            return false;
        }
    }

    void updateInteractionTiles() {
        if (!std::filesystem::exists(fileSystemPath + "/" + currentMap + "/" +
                                     std::to_string(newChunk.first) + "_" + std::to_string(newChunk.second))) {

            std::filesystem::create_directory(fileSystemPath + "/" + currentMap + "/" +
                                              std::to_string(newChunk.first) + "_" + std::to_string(newChunk.second));
        }
        interactionFile.open(fileSystemPath + "/" + currentMap + "/" +
                             std::to_string(newChunk.first) + "_" + std::to_string(newChunk.second) + "/" +
                             "custom.json");

        if (!interactionFile) {
            std::cout << "ERROR: CHUNK FILE CANT BE EDITED" << std::endl;
            exit(-1);
        }

        interactionFile >> jsonInteractionFile;

        std::vector<sf::Rect<float>>().swap(this->unwalkable);
        for (auto &i : jsonInteractionFile["walk_false"]) {
            unwalkable.emplace_back(sf::Rect<float>(i["x"], i["y"], i["width"], i["height"]));
        }

        std::vector<std::pair<sf::Rect<float>, std::string>>().swap(this->newWorld);
        for (auto &i : jsonInteractionFile["enter_building"]) {
            newWorld.emplace_back(std::pair(sf::Rect<float>(i["x"], i["y"], i["width"], i["height"]), i["map"]));
        }

        interactionFile.close();
    }

    bool validNextPos(sf::Vector2f nextPos) {
        for (auto &i : unwalkable) {
            if (
                    i.contains({nextPos.x + 24, nextPos.y})
                    || i.contains({nextPos.x - 24, nextPos.y})
                    //                    || i.contains({nextPos.x + 24, nextPos.y})
                    //                    || i.contains({nextPos.x - 24, nextPos.y })
                    || i.contains({nextPos.x, nextPos.y})) {
                return false;
            }
        }
        return true;
    }

    bool toANewWorld(sf::Vector2f currentPos) {
        for (auto &i : newWorld) {
            if (i.first.contains(currentPos)) {
                this->nextWorld = i.second;
                return true;
            }
        }
        return false;
    }

    void updateCurrentMap(std::string currentNewMap) {
        this->currentMap = currentNewMap;
    }

    void move(double timeElapsed) {
        addElapsedTime(timeElapsed, playerOldDirection);
        std::vector<CurrentDirection>().swap(playerOldDirection);

        if (upCheck()) {
            playerNewDirection.emplace_back(UP);
        }
        if (downCheck()) {
            if (playerNewDirection.empty()) {
                playerNewDirection.emplace_back(DOWN);
            } else {
                playerNewDirection.erase(playerNewDirection.begin());
            }
        }
        if (leftCheck()) {
            playerNewDirection.emplace_back(LEFT);
        }
        if (rightCheck()) {
            for (unsigned long long index = 0; index < playerNewDirection.size(); index++) {
                if (playerNewDirection.at(index) == LEFT) {
                    playerNewDirection.erase(playerNewDirection.begin() + index);
                    erased = true;
                }
            }
            if (!erased) {
                playerNewDirection.emplace_back(RIGHT);
            }
            erased = false;
        }

        if (playerNewDirection.empty()) {

        } else if (playerNewDirection.size() == 1) {
            updatePos({currentView->getCenter().x, currentView->getCenter().y});
            if (isNewChunk()) {
                oldChunk = newChunk;
                updateInteractionTiles();
            }

            if (playerNewDirection.front() == UP) {
                if (animationUpTime >= playerAnimationTime) {

                    if (currentStateOfAnimationUp == 3) {
                        currentStateOfAnimationUp = 0;
                    } else {
                        currentStateOfAnimationUp++;
                    }

                    spriteDraw = upSprite.at(currentStateOfAnimationUp);

                    if (validNextPos(
                            {currentView->getCenter().x + 0,
                             currentView->getCenter().y + (-Singleton::movementSpeed * Singleton::getInstance().dt)
                            }
                    )) {
                        currentView->move(0, -Singleton::movementSpeed * Singleton::getInstance().dt);


                    }
                    animationUpTime = 0;

                    toANewWorld(currentView->getCenter());

                } else {
                    spriteDraw = upSprite.at(currentStateOfAnimationUp);
                    if (validNextPos(
                            {currentView->getCenter().x + 0,
                             currentView->getCenter().y + (-Singleton::movementSpeed * Singleton::getInstance().dt)
                            }
                    )) {

                        currentView->move(0, -Singleton::movementSpeed * Singleton::getInstance().dt);
                    }

                    toANewWorld(currentView->getCenter());

                }

            } else if (playerNewDirection.front() == DOWN) {
                if (animationDownTime >= playerAnimationTime) {
                    if (currentStateOfAnimationDown == 3) {
                        currentStateOfAnimationDown = 0;
                    } else {
                        currentStateOfAnimationDown++;
                    }
                    spriteDraw = downSprite.at(currentStateOfAnimationDown);
                    if (validNextPos(
                            {currentView->getCenter().x + 0,
                             currentView->getCenter().y + (Singleton::movementSpeed * Singleton::getInstance().dt)
                            }
                    )) {

                        currentView->move(0, Singleton::movementSpeed * Singleton::getInstance().dt);
                    }
                    animationDownTime = 0;

                    toANewWorld(currentView->getCenter());

                } else {
                    spriteDraw = downSprite.at(currentStateOfAnimationDown);
                    if (validNextPos(
                            {currentView->getCenter().x + 0,
                             currentView->getCenter().y + (Singleton::movementSpeed * Singleton::getInstance().dt)
                            }
                    )) {

                        currentView->move(0, Singleton::movementSpeed * Singleton::getInstance().dt);
                    }

                    toANewWorld(currentView->getCenter());
                }

            } else if (playerNewDirection.front() == LEFT) {
                if (animationLeftTime >= playerAnimationTime) {
                    if (currentStateOfAnimationLeft == 3) {
                        currentStateOfAnimationLeft = 0;
                    } else {
                        currentStateOfAnimationLeft++;
                    }
                    spriteDraw = leftSprite.at(currentStateOfAnimationLeft);

                    if (validNextPos(
                            {currentView->getCenter().x + (-Singleton::movementSpeed * Singleton::getInstance().dt),
                             currentView->getCenter().y + 0,
                            }
                    )) {

                        currentView->move((-Singleton::movementSpeed * Singleton::getInstance().dt),
                                          0);
                    }
                    animationLeftTime = 0;

                    toANewWorld(currentView->getCenter());

                } else {
                    spriteDraw = leftSprite.at(currentStateOfAnimationLeft);
                    if (validNextPos(
                            {currentView->getCenter().x + (-Singleton::movementSpeed * Singleton::getInstance().dt),
                             currentView->getCenter().y + 0,
                            }
                    )) {

                        currentView->move((-Singleton::movementSpeed * Singleton::getInstance().dt),
                                          0);
                    }

                    toANewWorld(currentView->getCenter());

                }
            } else if (playerNewDirection.front() == RIGHT) {
                if (animationRightTime >= playerAnimationTime) {
                    if (currentStateOfAnimationRight == 3) {
                        currentStateOfAnimationRight = 0;
                    } else {
                        currentStateOfAnimationRight++;
                    }
                    spriteDraw = rightSprite.at(currentStateOfAnimationRight);
                    if (validNextPos(
                            {currentView->getCenter().x + (Singleton::movementSpeed * Singleton::getInstance().dt),
                             currentView->getCenter().y + 0,
                            }
                    )) {

                        currentView->move((Singleton::movementSpeed * Singleton::getInstance().dt),
                                          0);
                    }
                    animationRightTime = 0;

                    toANewWorld(currentView->getCenter());

                } else {
                    spriteDraw = rightSprite.at(currentStateOfAnimationRight);
                    if (validNextPos(
                            {currentView->getCenter().x + (Singleton::movementSpeed * Singleton::getInstance().dt),
                             currentView->getCenter().y + 0,
                            }
                    )) {

                        currentView->move((Singleton::movementSpeed * Singleton::getInstance().dt),
                                          0);
                    }

                    toANewWorld(currentView->getCenter());

                }
            }
        }
        playerOldDirection = playerNewDirection;
        std::vector<CurrentDirection>().swap(playerNewDirection);

    }

};


#endif //TRUGAMING_PLAYER_H
