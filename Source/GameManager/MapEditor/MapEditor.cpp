//
// Created by Nick on 1/25/2021.
//

#include <fstream>
#include <sstream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "MapEditor.h"

void MapEditor::changeTile(unsigned short blockNumber, const std::string &chunk, const std::string &newTileObject) {


    std::string tempFileName = chunk + "_temp";

    std::fstream file(chunk);
    std::ofstream tempFile(tempFileName);

    std::string line;

    int i = 0;
    file.seekg(std::ios::beg);
    while (getline(file, line) && i < blockNumber - 1) {
        tempFile << line;
        tempFile << '\n';
        i++;
    }

    std::istringstream ss(newTileObject);
    getline(ss, line, ' ');
    std::string param1 = line;
    getline(ss, line, ' ');
    char param2 = line[0];
    getline(ss, line, ' ');
    signed short int param3 = std::stoi(line);
    getline(ss, line, ' ');

    tempFile << param1;
    tempFile << ' ';
    tempFile << param2;
    tempFile << ' ';
    tempFile << param3;
    tempFile << '\n';

    while (getline(file, line)) {
        tempFile << line;
        tempFile << '\n';
    }

    ss.clear();
    file.close();
    tempFile.close();

    std::remove(chunk.c_str());
    std::rename(tempFileName.c_str(), chunk.c_str());

}

void MapEditor::setup() {

    rectangle.setSize(sf::Vector2f(Singleton::getInstance().tileSize * 20, 425));
    rectangle.setFillColor(sf::Color(220, 220, 220, 200));


    currentShapeSelected.setFillColor(sf::Color::Transparent);
    currentShapeSelected.setOutlineColor(sf::Color::Yellow);
    currentShapeSelected.setOutlineThickness(2);

    entireTileMap.load(arr1, 48, 16);
    entireTileMap.setScale(0.44, 0.44);
    currentShapeSelected.setSize(sf::Vector2f(entireTileMap.getScale().x * 48, entireTileMap.getScale().y * 48));

}

void MapEditor::draw() {
    if (!Singleton::getInstance().quitEditing) {
        getViewCoordinates();

        rectangle.setPosition(viewCoordinates.left,
                              viewCoordinates.top +
                              (renderWindow->getView().getSize().y - rectangle.getSize().y));
        renderWindow->draw(rectangle);
        entireTileMap.setPosition(rectangle.getPosition().x, rectangle.getPosition().y);
        renderWindow->draw(entireTileMap);
        renderWindow->draw(currentShapeSelected);
    }
}

sf::Vector2f MapEditor::editTile() {
    //NOTE: This code below is not optimal in the slightest this is a proof of concept to make it work
    //TODO: Clean this code up and be more maintainable / optimal

    sf::Vector2f mosLoc = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow));

    if (Singleton::getInstance().tileToEdit == true) {


        if (rectangle.getGlobalBounds().contains(mosLoc)) {

            editingTile.x = (int) ((mosLoc.x - rectangle.getPosition().x) /
                                   (Singleton::tileSize * entireTileMap.getScale().x));
            editingTile.y = (int) ((mosLoc.y - rectangle.getPosition().y) /
                                   (Singleton::tileSize * entireTileMap.getScale().x));

            currentShapeSelected.setPosition(Singleton::getInstance().roundFloorMultiple(mosLoc.x, Singleton::tileSize *
                                                                                                   entireTileMap.getScale().x),
                                             Singleton::getInstance().roundFloorMultiple(mosLoc.y, Singleton::tileSize *
                                                                                                   entireTileMap.getScale().y));
            currentShapeSelected.setSize(sf::Vector2f((Singleton::tileSize * entireTileMap.getScale().x) - 2,
                                                      (Singleton::tileSize * entireTileMap.getScale().y) - 2));
            Singleton::getInstance().tileToEdit = false;

            return editingTile;

        } else {
            if (mosLoc.x >= 0) {
                mapTile.x = ((int) mosLoc.x % 1536) / 48;
            } else {
                mapTile.x = ((int) (mosLoc.x + (1536 * (1 + std::abs(int(((mosLoc.x) /
                                                                          (Singleton::chunkSize *
                                                                           Singleton::tileSize))))))) %
                             1536) / 48;

            }
            if (mosLoc.y >= 0) {
                mapTile.y = ((int) mosLoc.y % 1536) / 48;

            } else {
                mapTile.y = (((int) mosLoc.y + (1536 * (1 + std::abs(int(((mosLoc.y) /
                                                                          (Singleton::chunkSize *
                                                                           Singleton::tileSize))))))) %
                             1536) / 48;
            }
            float tileX = ((mosLoc.x) / (Singleton::chunkSize * Singleton::tileSize));

            float tileY = ((mosLoc.y) / (Singleton::chunkSize *
                                         Singleton::tileSize));

            int finTileX;
            int finTileY;

            if (tileX < 0) {
                finTileX = (int) tileX - 1;
            } else {
                finTileX = (int) tileX;
            }
            if (tileY < 0) {
                finTileY = (int) tileY - 1;

            } else {
                finTileY = (int) tileY;

            }

            changeTile(mapTile.y * Singleton::chunkSize + mapTile.x + 1,
                       "../Source/FileSystem/"
                       + std::to_string(finTileX)
                       + "_"
                       + std::to_string(finTileY)
                       + ".chunk",
                       std::to_string(editingTile.y * 48 + editingTile.x) + " 0 0");

            Singleton::getInstance().tileToEdit = false;
            Singleton::getInstance().updateChunks = true;
        }
    }

    return sf::Vector2f(-1, -1);

}
