#ifndef TRUGAMING_TILEMAP_H
#define TRUGAMING_TILEMAP_H

#include "../../Constants/Singleton.h"

class Tilemap : public sf::Drawable, public sf::Transformable {
public:

    bool load(sf::Vector2u tileSize, const std::vector<int> tiles, unsigned int width, unsigned int height) {

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j) {
                // get the current tile number
                unsigned int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                unsigned int tu = tileNumber % (Singleton::getInstance().tilemap.getSize().x / tileSize.x);
                unsigned int tv = tileNumber / (Singleton::getInstance().tilemap.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f((i * (48)), (j * 48));
                quad[1].position = sf::Vector2f(((i + 1) * 48), (j * 48));
                quad[2].position = sf::Vector2f(((i + 1) * 48), ((j + 1) * 48));
                quad[3].position = sf::Vector2f((i * 48), ((j + 1) * 48));

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f((tu * (tileSize.x)) + 3.f, (tv * tileSize.y) + 3.f);
                quad[1].texCoords = sf::Vector2f(((tu + 1.f) * (tileSize.x)) - 3.f, (tv * tileSize.y) + 3.f);
                quad[2].texCoords = sf::Vector2f(((tu + 1.f) * (tileSize.x)) - 3.f, ((tv + 1) * tileSize.y) - 3.f);
                quad[3].texCoords = sf::Vector2f((tu * (tileSize.x)) + 3.f, ((tv + 1) * tileSize.y) - 3.f);
            }

        return true;
    }

private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // apply the transform
        states.transform *= getTransform();

        // apply the tile_set texture
        states.texture = &Singleton::getInstance().tilemap;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;

};

#endif //TRUGAMING_TILEMAP_H