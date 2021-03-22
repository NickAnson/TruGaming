//
// Created by Nick on 2/24/2021.
//

#include <iostream>
#include "GameText.h"

GameText::GameText(GameText::FONTS fontChoose) {
    if (fontChoose == ARIAL) {
        font.loadFromFile("../Dependencies/Fonts/arial.ttf");
    }

    text.setFont(font);
}

sf::Text &GameText::getText() {
    return text;
}

void GameText::setFillColor(sf::Color fontColor) {
    text.setFillColor(fontColor);
}

void GameText::setSize(int size) {
    text.setCharacterSize(size);

}

void GameText::setPosition(sf::Vector2i point) {
    text.setPosition(point.x, point.y);
}

void GameText::setString(std::string newText) {
    text.setString(newText);
}
