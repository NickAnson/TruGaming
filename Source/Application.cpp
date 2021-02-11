#include <SFML/Graphics.hpp>
#include <thread>
#include <unordered_set>
#include "Application.h"
#include "Movement/PlayerMovement.h"
#include "GameManager/MapEditor/MapEditor.h"

//this makes our program use high performance graphics by default on systems with more than one gpu
#ifdef _WIN32
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
__declspec(
        dllexport) unsigned int AmdPowerXpressRequestHighPerformance = 0x1;
}
#endif


int main() {

    sf::ContextSettings settings;

    sf::RenderWindow window(
            Singleton::getInstance().computerScreen,
            "SFML works!",
            sf::Style::Default,
            settings);

    Application application(window);
    window.setVerticalSyncEnabled(false);
    application.test();


    return 0;
}

void Application::test() {

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("../Dependencies/Fonts/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(128);
    text.setPosition(0, 64);

    sf::Text currentMosPosX;
    currentMosPosX.setFont(font);
    currentMosPosX.setFillColor(sf::Color::Red);
    currentMosPosX.setCharacterSize(64);

    sf::Text currentMosPosY;
    currentMosPosY.setFont(font);
    currentMosPosY.setFillColor(sf::Color::Red);
    currentMosPosY.setCharacterSize(64);
    currentMosPosY.setPosition(
            currentMosPosX.getPosition().x,
            currentMosPosX.getPosition().y + 32
    );

    sf::Event event{};


    sf::View view;
    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

    MapEditor mapEditor(*window);
    mapEditor.setup();

    window->setView(view);
    PlayerMovement player1;


    while (window->isOpen()) {
        window->setView(view);
        window->clear(sf::Color(sf::Color::White));

        chunkManagement();

        window->draw(text);
        window->draw(currentMosPosX);
        window->draw(currentMosPosY);

        mapEditor.draw();
        window->setView(view);
        window->display();

        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta < 0) {
                        if (view.getSize().x <
                            (Singleton::getInstance().chunkSize * Singleton::getInstance().chunkSize) * 4) {
                            view.zoom(1.1);
                        }
                    } else {
                        if (view.getSize().x >
                            Singleton::getInstance().chunkSize * Singleton::getInstance().chunkSize) {
                            view.zoom(0.9);
                        }

                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Singleton::getInstance().tileToEdit = true;
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    if (!Singleton::getInstance().quitEditing) {
                        Singleton::getInstance().quitEditing = true;
                    } else {
                        Singleton::getInstance().quitEditing = false;
                    }
                }
            }
        }


        player1.move();

        if (player1.playerMovement.right) {
            view.move(10, 0);
            deltaOffSet.x += 10;
        }
        if (player1.playerMovement.left) {
            view.move(-10, 0);
            deltaOffSet.x -= 10;
        }
        if (player1.playerMovement.up) {
            view.move(0, -10);
            deltaOffSet.y -= 10;
        }
        if (player1.playerMovement.down) {
            view.move(0, 10);
            deltaOffSet.y += 10;
        }
        if (std::abs(deltaOffSet.x) >= (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize) ||
            std::abs(deltaOffSet.y) >= (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)) {
            Singleton::getInstance().updateChunks = true;
            deltaOffSet.x = 0;
            deltaOffSet.y = 0;
        }

        text.setString(std::to_string(1.f / clock.restart().asSeconds()));
        text.setPosition(view.getCenter().x, view.getCenter().y + 100);

        sf::Vector2f mouse_world = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        currentMosPosX.setString(std::to_string(
                (mouse_world.x) / (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)));
        currentMosPosY.setString(std::to_string(
                mouse_world.y / (Singleton::getInstance().chunkSize * Singleton::getInstance().tileSize)));
        currentMosPosX.setPosition(view.getCenter().x, view.getCenter().y);
        currentMosPosY.setPosition(view.getCenter().x, view.getCenter().y + 50);

        mapEditor.editTile();
    }
}

void Application::chunkManagement() {

    rules();

    for (auto &i : viewableChunk) {
        i.draw();
    }
}

void Application::rules() {

    if (Singleton::getInstance().updateChunks) {

        viewableChunk[0] = GameChunk(*(window), std::pair(-4, 0));

        viewableChunk[1] = GameChunk(*(window), std::pair(-3, 0));
        viewableChunk[2] = GameChunk(*(window), std::pair(-2, 0));
        viewableChunk[3] = GameChunk(*(window), std::pair(-1, 0));
        viewableChunk[4] = GameChunk(*(window), std::pair(0, 0));
        viewableChunk[5] = GameChunk(*(window), std::pair(1, 0));
        viewableChunk[6] = GameChunk(*(window), std::pair(2, 0));
        viewableChunk[7] = GameChunk(*(window), std::pair(3, 0));

        viewableChunk[8] = GameChunk(*(window), std::pair(-4, -3));
        viewableChunk[9] = GameChunk(*(window), std::pair(-3, -3));
        viewableChunk[10] = GameChunk(*(window), std::pair(-2, -3));
        viewableChunk[11] = GameChunk(*(window), std::pair(-1, -3));
        viewableChunk[12] = GameChunk(*(window), std::pair(0, -3));
        viewableChunk[13] = GameChunk(*(window), std::pair(1, -3));
        viewableChunk[14] = GameChunk(*(window), std::pair(2, -3));
        viewableChunk[15] = GameChunk(*(window), std::pair(3, -3));

        viewableChunk[16] = GameChunk(*(window), std::pair(-4, -2));
        viewableChunk[17] = GameChunk(*(window), std::pair(-3, -2));
        viewableChunk[18] = GameChunk(*(window), std::pair(-2, -2));
        viewableChunk[19] = GameChunk(*(window), std::pair(-1, -2));
        viewableChunk[20] = GameChunk(*(window), std::pair(0, -2));
        viewableChunk[21] = GameChunk(*(window), std::pair(1, -2));
        viewableChunk[22] = GameChunk(*(window), std::pair(2, -2));
        viewableChunk[23] = GameChunk(*(window), std::pair(3, -2));

        viewableChunk[24] = GameChunk(*(window), std::pair(-4, -1));
        viewableChunk[25] = GameChunk(*(window), std::pair(-3, -1));
        viewableChunk[26] = GameChunk(*(window), std::pair(-2, -1));
        viewableChunk[27] = GameChunk(*(window), std::pair(-1, -1));
        viewableChunk[28] = GameChunk(*(window), std::pair(0, -1));
        viewableChunk[29] = GameChunk(*(window), std::pair(1, -1));
        viewableChunk[30] = GameChunk(*(window), std::pair(2, -1));
        viewableChunk[31] = GameChunk(*(window), std::pair(3, -1));

        viewableChunk[32] = GameChunk(*(window), std::pair(-4, 1));
        viewableChunk[33] = GameChunk(*(window), std::pair(-3, 1));
        viewableChunk[34] = GameChunk(*(window), std::pair(-2, 1));
        viewableChunk[35] = GameChunk(*(window), std::pair(-1, 1));
        viewableChunk[36] = GameChunk(*(window), std::pair(0, 1));
        viewableChunk[37] = GameChunk(*(window), std::pair(1, 1));
        viewableChunk[38] = GameChunk(*(window), std::pair(2, 1));
        viewableChunk[39] = GameChunk(*(window), std::pair(3, 1));

        viewableChunk[40] = GameChunk(*(window), std::pair(-4, 2));
        viewableChunk[41] = GameChunk(*(window), std::pair(-3, 2));
        viewableChunk[42] = GameChunk(*(window), std::pair(-2, 2));
        viewableChunk[43] = GameChunk(*(window), std::pair(-1, 2));
        viewableChunk[44] = GameChunk(*(window), std::pair(0, 2));
        viewableChunk[45] = GameChunk(*(window), std::pair(1, 2));
        viewableChunk[46] = GameChunk(*(window), std::pair(2, 2));
        viewableChunk[47] = GameChunk(*(window), std::pair(3, 2));
        Singleton::getInstance().updateChunks = false;
    }
}
