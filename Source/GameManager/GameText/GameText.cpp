#include "GameText.h"

GameText::GameText(GameText::FONTS fontChoose) {
    if (fontChoose == ARIAL) {
        font.loadFromFile("../Dependencies/Fonts/arial.ttf");
    } else if (fontChoose == GAME_FONT_0) {
        font.loadFromFile("../Dependencies/Fonts/game_font_0.ttf");
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


void GameText::setString(std::string newText) {
    text.setString(newText);
}

sf::Rect<float> GameText::getSize() {
    return text.getGlobalBounds();
}

void GameText::setOutlineColor(sf::Color outlineCol) {
    text.setOutlineColor(outlineCol);
}

void GameText::setOutlineThickness(float size) {
    text.setOutlineThickness(size);
}




