#ifndef TRUGAMING_TITLESCREEN_H
#define TRUGAMING_TITLESCREEN_H


#include "View.h"
#include "../States/State.h"
#include "../GameText/GameText.h"
#include "../../Audio/Audio.h"

class TitleScreen : public View {
public:
    explicit TitleScreen(std::pair<int, int> viewSize, sf::RenderWindow &renderWindowMAIN) {
        this->sizeOfView = viewSize;
        this->nextView = State::screen_TITLE;
        load(renderWindowMAIN);
    }

    void load(sf::RenderWindow &renderWindow) override;

    void windowLogic() override;

    State::viewOpened &getNextView() {
        return this->nextView;
    }

    void setNextView(State::viewOpened newState) {
        this->nextView = newState;
    }

//    State::windowStates state = State::window_CLOSED;
    State::viewOpened nextView;

private:
    Audio background{"title/background.ogg", true};
    const std::string bgTitle = "../res/backgrounds/title/";

    std::pair<int, int> sizeOfView;

    GameText title{GameText::FONTS::GAME_FONT_0};
    GameText startGame{GameText::FONTS::GAME_FONT_0};
    GameText exit{GameText::FONTS::GAME_FONT_0};

    sf::Rect<float> titleBox;
    sf::Rect<float> startGameBox;
    sf::Rect<float> exitGameBox;

    sf::Texture texture;
    sf::Sprite backgroundImage;

    sf::RenderWindow *renderWindow;


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {

        target.draw(backgroundImage);
        target.draw(title, states);
        target.draw(startGame, states);
        target.draw(exit, states);

    }
};


#endif //TRUGAMING_TITLESCREEN_H
