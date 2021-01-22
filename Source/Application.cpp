#include <SFML/Graphics.hpp>
#include "Application.h"
#include "TextureManager/Tilemap.h"
#include "Movement/PlayerMovement.h"
#include "FileSystem/MapFileSystem.h"

//this makes our program use high performance graphics by default

#ifdef _WIN32
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
__declspec(
        dllexport) unsigned int AmdPowerXpressRequestHighPerformance = 0x1;
}
#endif


int main() {


    std::srand(
            std::time(nullptr)); // use current time as seed for random generator
    sf::ContextSettings settings;

    sf::RenderWindow window(
            sf::VideoMode(
                    sf::VideoMode::getDesktopMode().width,
                    sf::VideoMode::getDesktopMode().height
            ),
            "SFML works!",
            sf::Style::Default, settings);

    window.setFramerateLimit(190);

    Application application;
    application.test(window);


    return 0;
}

void Application::test(sf::RenderWindow &window) {

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("../Dependencies/Fonts/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(32);
    text.setPosition(0, 64);

    sf::Text currentMosPosX;
    currentMosPosX.setFont(font);
    currentMosPosX.setFillColor(sf::Color::Red);
    currentMosPosX.setCharacterSize(32);

    sf::Text currentMosPosY;
    currentMosPosY.setFont(font);
    currentMosPosY.setFillColor(sf::Color::Red);
    currentMosPosY.setCharacterSize(32);
    currentMosPosY.setPosition(
            currentMosPosX.getPosition().x,
            currentMosPosX.getPosition().y + 32
    );

    sf::Event event{};


    sf::View view;
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    window.setView(view);
    PlayerMovement player1;


    while (window.isOpen()) {
        window.clear();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        player1.move();

        if (player1.playerMovement.right) {
            view.move(2, 0);
        }
        if (player1.playerMovement.left) {
            view.move(-2, 0);
        }
        if (player1.playerMovement.up) {
            view.move(0, -2);
        }
        if (player1.playerMovement.down) {
            view.move(0, 2);
        }

        text.setString(std::to_string(1.f / clock.restart().asSeconds()));

        sf::Vector2f mouse_world = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        currentMosPosX.setString(std::to_string(mouse_world.x));
        currentMosPosY.setString(std::to_string(mouse_world.y));

        window.setView(view);
        MapFileSystem map1{"../Source/FileSystem/chunk_1_1.json",&window};
        window.draw(text);
        window.draw(currentMosPosX);
        window.draw(currentMosPosY);
        window.display();

    }
}