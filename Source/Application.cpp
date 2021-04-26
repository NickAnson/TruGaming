#include <SFML/Graphics.hpp>

#include "GameManager/Views/TitleScreen.h"
#include "GameManager/Views/WorldView.h"

//this makes our program use high performance graphics by default on systems with more than one gpu
#ifdef _WIN32
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
__declspec(dllexport) unsigned int AmdPowerXpressRequestHighPerformance = 0x1;
}
#endif


int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(
            Singleton::getInstance().computerScreen,
            "TruGame",
            sf::Style::None,
            settings);

    window.setVerticalSyncEnabled(true);

    TitleScreen titleScreen(std::pair(window.getSize().x, window.getSize().y), window);
    WorldView worldView(std::pair(window.getSize().x, window.getSize().y), window, "map_0");


    sf::Event event{};
    State::viewOpened viewOpened = State::viewOpened::screen_TITLE;

    Singleton::getInstance().zoomLevel = 0.5;
    while (viewOpened != State::NONE) {
        if (viewOpened == State::screen_TITLE) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear();
            titleScreen.windowLogic();
            window.draw(titleScreen);
            window.display();
            viewOpened = titleScreen.getNextView();
        } else if (viewOpened == State::screen_WORLD) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (worldView.getEscapeState() != State::popUpView::popup_ESCAPE) {
                    if (event.type == sf::Event::MouseWheelScrolled) {
                        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                            if (event.mouseWheelScroll.delta < 0) {
                                if (Singleton::getInstance().zoomLevel < 1) {
                                    Singleton::getInstance().zoomLevel *= 2;
                                }
                            } else {
                                if (Singleton::getInstance().zoomLevel > 0.50) {
                                    Singleton::getInstance().zoomLevel /= 2;
                                }
                            }
                        }
                    }
                }
                if (event.type == sf::Event::KeyPressed || (event.type == sf::Event::LostFocus)) {
                    if (event.key.code == sf::Keyboard::Escape || (event.type == sf::Event::LostFocus)) {
                        if (worldView.getEscapeState() == State::popUpView::popup_NONE &&
                            (event.type != sf::Event::GainedFocus)) {
                            worldView.setEscapeKeyState(State::popUpView::popup_ESCAPE);
                        } else {
                            if (event.type != sf::Event::LostFocus) {
                                worldView.setEscapeKeyState(State::popUpView::popup_NONE);
                            }
                        }
                    }
                }
            }
            window.clear();
            worldView.windowLogic();
            window.draw(worldView);
            window.display();
            viewOpened = worldView.getNextView();

        }
    }

    return 0;
}