//
// Created by Nick on 1/19/2021.
//

#ifndef TRUGAMING_ENTITY_H
#define TRUGAMING_ENTITY_H


#include <string>
#include <SFML/Graphics.hpp>
#include <utility>
#include "../../Constants/Singleton.h"


class Entity : public sf::Drawable, public sf::Transformable {
public:

    Entity(unsigned short int tileIDTemp, std::vector<int> animationTilesTemp, std::vector<float> animationTimesTemp,
           int tileLayerTemp, std::pair<int, int> positionTemp, sf::Texture &textureMap)
            : textureMap(textureMap) {

        this->tileID = tileIDTemp;
        this->animationTiles = std::move(animationTilesTemp);
        this->animationTimes = std::move(animationTimesTemp);
        this->tileLayer = tileLayerTemp;
        this->position = positionTemp;
        this->spritePosition = {this->tileID % (this->textureMap.getSize().x / Singleton::tileSize),
                                this->tileID / (this->textureMap.getSize().y / Singleton::tileSize)
        };
    }

    Entity() = delete;

private:

    unsigned short int tileID{};
    std::vector<int> animationTiles{};
    std::vector<float> animationTimes{};
    unsigned short int tileLayer{};

    std::pair<double, double> position;

    std::pair<int, int> spritePosition;
    sf::Texture &textureMap;

    sf::VertexArray entity{sf::Quads, 4};

public:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        states.transform *= getTransform();

        states.texture = &textureMap;

        target.draw(entity, states);
    }

    std::pair<double, double> getPosition() {
        return position;
    }

    sf::Vector2<float> getPositionSFML() {
        return sf::Vector2f((position.first), (position.second));
    }

    unsigned short int getTileId() const {
        return tileID;
    }

    void setTileId(unsigned short tileId) {
        tileID = tileId;
    }

    const std::vector<int> &getAnimationTiles() const {
        return animationTiles;
    }

    void setAnimationTiles(const std::vector<int> &animationTilesTemp) {
        Entity::animationTiles = animationTilesTemp;
    }

    const std::vector<float> &getAnimationTimes() const {
        return animationTimes;
    }

    void setAnimationTimes(const std::vector<float> &animationTimesTemp) {
        Entity::animationTimes = animationTimesTemp;

    }

    unsigned short int getTileLayer() const {
        return tileLayer;
    }

    void setTileLayer(unsigned short tileLayerTemp) {
        Entity::tileLayer = tileLayerTemp;
    }

};

#endif //TRUGAMING_ENTITY_H
