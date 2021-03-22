//
// Created by Nick on 2/24/2021.
//

#ifndef TRUGAMING_GAMETEXT_H
#define TRUGAMING_GAMETEXT_H


#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameText {
public:
    enum FONTS {
        ARIAL
    };

    explicit GameText(FONTS fontChoose);

    void setFillColor(sf::Color fontColor);

    void setSize(int size);

    void setPosition(sf::Vector2i point);

    void setString(std::string newText);


    sf::Text &getText();

    GameText() = delete;

private:
    sf::Font font;
    sf::Text text;

};


#endif //TRUGAMING_GAMETEXT_H
