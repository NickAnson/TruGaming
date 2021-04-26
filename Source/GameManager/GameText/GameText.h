#ifndef TRUGAMING_GAMETEXT_H
#define TRUGAMING_GAMETEXT_H


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

class GameText : public sf::Drawable, public sf::Transformable {
public:
    enum FONTS {
        ARIAL, GAME_FONT_0
    };

    explicit GameText(FONTS fontChoose);

    void setFillColor(sf::Color fontColor);

    void setSize(int size);

    void setString(std::string newText);

    void setOutlineColor(sf::Color outlineCol);

    void setOutlineThickness(float size);

    sf::Rect<float> getSize();

    sf::Text &getText();

    GameText() = delete;

private:
    sf::Font font;
    sf::Text text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(text, states);
    }
};


#endif //TRUGAMING_GAMETEXT_H
