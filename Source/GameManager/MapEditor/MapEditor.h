//
// Created by Nick on 1/25/2021.
//

#ifndef TRUGAMING_MAPEDITOR_H
#define TRUGAMING_MAPEDITOR_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "string"
#include "../../Constants/Singleton.h"
#include "../../TextureManager/Tilemap.h"


class MapEditor {

public:
    MapEditor(sf::RenderWindow &renderWindowTemp) {

        renderWindow = &renderWindowTemp;

        if (!tileMap.loadFromFile("../Source/TextureManager/TileMap/atlas_48x.png")) {
            std::cout << " OUCH " << std::endl;
        }
        for (int i = 0; i < Singleton::getInstance().m_tileset.getSize().x / 48 *
                            Singleton::getInstance().m_tileset.getSize().y / 48; i++) {
            level.push_back(i);
        }
        arr1 = level.data();
    }

    sf::Vector2f editTile();

    void setup();

    void draw();

    int move = 20;

private:
    sf::RectangleShape rectangle;
    sf::RectangleShape currentShapeSelected;
    sf::Vector2f editingTile = {-1, -1};
    sf::Vector2f mapTile = {-1, -1};

    bool runOnce = true;
    int *arr1;
    std::vector<int> level;
    sf::Event event;

    sf::FloatRect viewCoordinates;

    MapEditor() = delete;

    void changeTile(unsigned short blockNumber, const std::string &chunk, const std::string &newTileObject);

    sf::RenderWindow *renderWindow;

    sf::FloatRect &getViewCoordinates() {
        viewCoordinates.left = (renderWindow->getView().getCenter().x - renderWindow->getView().getSize().x / 2.f);
        viewCoordinates.top = renderWindow->getView().getCenter().y - renderWindow->getView().getSize().y / 2.f;
        viewCoordinates.width = renderWindow->getView().getSize().x;
        viewCoordinates.height = renderWindow->getView().getSize().y;
        return viewCoordinates;
    }

    sf::Texture tileMap;

    Tilemap entireTileMap;
};


#endif //TRUGAMING_MAPEDITOR_H
