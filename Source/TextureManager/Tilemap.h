//
// Created by nicka on 12/6/2020.
//

#ifndef TRUGAMING_TILEMAP_H
#define TRUGAMING_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "../Constants/Singleton.h"


class Tilemap : public sf::Drawable, public sf::Transformable {
public:

    bool load(const int *tiles, unsigned int width, unsigned int height) {
        // load the tileset texture


        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j) {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (Singleton::getInstance().m_tileset.getSize().x / Singleton::tileSize);
                int tv = tileNumber / (Singleton::getInstance().m_tileset.getSize().x / Singleton::tileSize);

                // get a pointer to the current tile's quad
                sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * Singleton::tileSize, j * Singleton::tileSize);
                quad[1].position = sf::Vector2f((i + 1) * Singleton::tileSize, j * Singleton::tileSize);
                quad[2].position = sf::Vector2f((i + 1) * Singleton::tileSize, (j + 1) * Singleton::tileSize);
                quad[3].position = sf::Vector2f(i * Singleton::tileSize, (j + 1) * Singleton::tileSize);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * Singleton::tileSize, tv * Singleton::tileSize);
                quad[1].texCoords = sf::Vector2f((tu + 1) * Singleton::tileSize, tv * Singleton::tileSize);
                quad[2].texCoords = sf::Vector2f((tu + 1) * Singleton::tileSize, (tv + 1) * Singleton::tileSize);
                quad[3].texCoords = sf::Vector2f(tu * Singleton::tileSize, (tv + 1) * Singleton::tileSize);
            }

        return true;
    }


private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
    const {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &Singleton::getInstance().m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);

    }
    sf::VertexArray m_vertices;
};

#endif //TRUGAMING_TILEMAP_H
