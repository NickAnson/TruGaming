
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

    Player(
            std::vector<sf::Sprite> &upSpriteTEMP = Singleton::getInstance().defaultCharacterUpSprites,
            std::vector<sf::Sprite> &downSpriteTEMP = Singleton::getInstance().defaultCharacterDownSprites,
            std::vector<sf::Sprite> &leftSpriteTEMP = Singleton::getInstance().defaultCharacterLeftSprites,
            std::vector<sf::Sprite> &rightSpriteTEMP = Singleton::getInstance().defaultCharacterRightSprites,
            sf::Vector2f positionTemp = sf::Vector2f(0, 0), CurrentDirection playerDirectionTEMP = DOWN,
            double animationTimeTEMP = 500, sf::View &currentViewTemp = Singleton::getInstance().defaultPlayerView) {

        this->spriteDraw = downSpriteTEMP.at(1);
        this->position = positionTemp;

        this->upSprite = upSpriteTEMP;
        this->downSprite = downSpriteTEMP;
        this->leftSprite = leftSpriteTEMP;
        this->rightSprite = rightSpriteTEMP;

        this->playerOldDirection.emplace_back(playerDirectionTEMP);

        playerAnimationTime = animationTimeTEMP;

        currentView = &currentViewTemp;
    }


private:
    double playerAnimationTime;
    double animationUpTime = 0;
    double animationDownTime = 0;
    double animationLeftTime = 0;
    double animationRightTime = 0;
    unsigned short int currentStateOfAnimationUp = 1;
    unsigned short int currentStateOfAnimationDown = 1;
    unsigned short int currentStateOfAnimationLeft = 1;
    unsigned short int currentStateOfAnimationRight = 1;

    bool erased = false;
    std::vector<CurrentDirection> playerNewDirection;
    std::vector<CurrentDirection> playerOldDirection;

    std::vector<sf::Sprite> upSprite;
    std::vector<sf::Sprite> downSprite;
    std::vector<sf::Sprite> rightSprite;
    std::vector<sf::Sprite> leftSprite;

    sf::Sprite upResting;
    sf::Sprite downResting;
    sf::Sprite leftResting;
    sf::Sprite rightResting;

    sf::View *currentView;

    sf::Vector2f lastPosition{0.f, 0.f};

    sf::Sprite spriteDraw;

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
    void setView(sf::View &view) {
        currentView = &view;
    }

    sf::Sprite &getSprite() {
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
        for (unsigned long long i = 0; i < directionToElapse.size(); i++) {
            if (directionToElapse.at(i) == UP) {
                animationUpTime += timeElapsed;
            } else if (directionToElapse.at(i) == DOWN) {
                animationDownTime += timeElapsed;
            } else if (directionToElapse.at(i) == LEFT) {
                animationLeftTime += timeElapsed;
            } else if (directionToElapse.at(i) == RIGHT) {
                animationRightTime += timeElapsed;
            }
        }
    }

    void truncatePos() {
        spriteDraw.setPosition(std::floor(spriteDraw.getPosition().x), std::floor(spriteDraw.getPosition().y));
        lastPosition.x = std::floor(lastPosition.x);
        lastPosition.y = std::floor(lastPosition.y);
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

            if (playerNewDirection.front() == UP) {
                if (animationUpTime >= playerAnimationTime) {

                    if (currentStateOfAnimationUp == 3) {
                        currentStateOfAnimationUp = 0;
                    } else {
                        currentStateOfAnimationUp++;
                    }

                    spriteDraw = upSprite.at(currentStateOfAnimationUp);
                    currentView->move(0, -Singleton::movementSpeed * Singleton::getInstance().dt);
                    animationUpTime = 0;
                } else {
                    spriteDraw = upSprite.at(currentStateOfAnimationUp);
                    currentView->move(0, -Singleton::movementSpeed * Singleton::getInstance().dt);
                }

            } else if (playerNewDirection.front() == DOWN) {
                if (animationDownTime >= playerAnimationTime) {
                    if (currentStateOfAnimationDown == 3) {
                        currentStateOfAnimationDown = 0;
                    } else {
                        currentStateOfAnimationDown++;
                    }
                    spriteDraw = downSprite.at(currentStateOfAnimationDown);
                    currentView->move(0, Singleton::movementSpeed * Singleton::getInstance().dt);
                    animationDownTime = 0;
                } else {
                    spriteDraw = downSprite.at(currentStateOfAnimationDown);
                    currentView->move(0, Singleton::movementSpeed * Singleton::getInstance().dt);
                }

            } else if (playerNewDirection.front() == LEFT) {
                if (animationLeftTime >= playerAnimationTime) {
                    if (currentStateOfAnimationLeft == 3) {
                        currentStateOfAnimationLeft = 0;
                    } else {
                        currentStateOfAnimationLeft++;
                    }
                    spriteDraw = leftSprite.at(currentStateOfAnimationLeft);
                    currentView->move(-Singleton::movementSpeed * Singleton::getInstance().dt, 0);
                    animationLeftTime = 0;
                } else {
                    spriteDraw = leftSprite.at(currentStateOfAnimationLeft);
                    currentView->move(-Singleton::movementSpeed * Singleton::getInstance().dt, 0);
                }
            } else if (playerNewDirection.front() == RIGHT) {
                if (animationRightTime >= playerAnimationTime) {
                    if (currentStateOfAnimationRight == 3) {
                        currentStateOfAnimationRight = 0;
                    } else {
                        currentStateOfAnimationRight++;
                    }
                    spriteDraw = rightSprite.at(currentStateOfAnimationRight);
                    currentView->move(Singleton::movementSpeed * Singleton::getInstance().dt, 0);
                    animationRightTime = 0;
                } else {
                    spriteDraw = rightSprite.at(currentStateOfAnimationRight);
                    currentView->move(Singleton::movementSpeed * Singleton::getInstance().dt, 0);
                }
            }
        }
        playerOldDirection = playerNewDirection;
        std::vector<CurrentDirection>().swap(playerNewDirection);

    }

};


#endif //TRUGAMING_PLAYER_H
