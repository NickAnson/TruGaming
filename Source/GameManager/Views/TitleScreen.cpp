
#include "TitleScreen.h"

void TitleScreen::load(sf::RenderWindow &renderWindowMAIN) {

    title.setSize(256);
    startGame.setSize(96);
    exit.setSize(96);

    title.setFillColor(sf::Color(255, 0, 0));
    startGame.setFillColor(sf::Color(255, 0, 0));
    exit.setFillColor(sf::Color(255, 0, 0));

    title.setOutlineColor(sf::Color::Green);
    title.setOutlineThickness(0.75);

    startGame.setOutlineColor(sf::Color::Green);
    startGame.setOutlineThickness(0.75);

    exit.setOutlineColor(sf::Color::Green);
    exit.setOutlineThickness(0.75);

    title.setString("TruGaming");
    startGame.setString("Start");
    exit.setString("Exit");

    title.setPosition(sizeOfView.first / 2.f - title.getSize().width / 2.f, 200.f * (sizeOfView.second / 2560.f));
    startGame.setPosition(sizeOfView.first / 2.f - startGame.getSize().width / 2.f,
                          1600.f * (sizeOfView.second / 2560.f));
    exit.setPosition(sizeOfView.first / 2.f - exit.getSize().width / 2.f, 2000.f * (sizeOfView.second / 2560.f));

    titleBox.left = title.getPosition().x;
    titleBox.top = title.getPosition().y;
    titleBox.width = title.getSize().width;
    titleBox.height = title.getSize().height;

    startGameBox.left = startGame.getPosition().x;
    startGameBox.top = startGame.getPosition().y;
    startGameBox.width = startGame.getSize().width;
    startGameBox.height = startGame.getSize().height;

    exitGameBox.left = exit.getPosition().x;
    exitGameBox.top = exit.getPosition().y;
    exitGameBox.width = exit.getSize().width;
    exitGameBox.height = exit.getSize().height;

    this->renderWindow = &renderWindowMAIN;

    background.setVolume(20);

    texture.loadFromFile(bgTitle + "bg_1.png");
    std::cout << bgTitle + "bg_2.png" << std::endl;
    backgroundImage.setTexture(texture);
    backgroundImage.setScale({
                                     (Singleton::getInstance().computerScreen.width /
                                      static_cast<float>(texture.getSize().x)),
                                     (Singleton::getInstance().computerScreen.height /
                                      static_cast<float>(texture.getSize().y))
                             });

}

void TitleScreen::windowLogic() {
    background.play();

    auto translated_pos = this->renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->renderWindow));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (startGameBox.contains(translated_pos)) {
            setNextView(State::screen_WORLD);
            background.pause();
        } else if (exitGameBox.contains(translated_pos)) {
            setNextView(State::NONE);
            background.pause();
        }
    }
}
