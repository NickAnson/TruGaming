//
// Created by nicka on 12/6/2020.
//

#ifndef TRUGAMING_TILEMAP_H
#define TRUGAMING_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "TileMap/TileToNumberConverter.h"

class Tilemap : public sf::Drawable, public sf::Transformable {
public:

    bool load(const char *tiles) {

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(4096);

        // populate the vertex array, with one quad per tile
        for (unsigned short int i = 0; i < 32; ++i) {
            for (unsigned short int j = 0; j < 32; ++j) {
                // get the current tile number
                unsigned int tileNumber = tiles[i + j * 32];

                // find its position in the tileset texture
                unsigned int tu =
                        tileNumber % (TileToNumberConverter::getInstance().m_tileset.getSize().x / 48);
                unsigned int tv =
                        tileNumber / (TileToNumberConverter::getInstance().m_tileset.getSize().x / 48);

                // get a pointer to the current tile's quad
                sf::Vertex *quad = &m_vertices[(i + j * 32) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * 48,
                                                j * 48);
                quad[1].position = sf::Vector2f((i + 1) * 48,
                                                j * 48);
                quad[2].position = sf::Vector2f((i + 1) * 48,
                                                (j + 1) * 48);
                quad[3].position = sf::Vector2f(i * 48,
                                                (j + 1) * 48);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * 48,
                                                 tv * 48);
                quad[1].texCoords = sf::Vector2f((tu + 1) * 48,
                                                 tv * 48);
                quad[2].texCoords = sf::Vector2f((tu + 1) * 48,
                                                 (tv + 1) * 48);
                quad[3].texCoords = sf::Vector2f(tu * 48,
                                                 (tv + 1) * 48);
            }
        }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
    const {
        // apply the transform
        states.transform *= getTransform();


        // apply the tileset texture
        states.texture = &TileToNumberConverter::getInstance().m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
};

#endif //TRUGAMING_TILEMAP_H
