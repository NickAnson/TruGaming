#include <SFML/Graphics.hpp>
#include <thread>
#include <unordered_set>
#include "Application.h"
#include "Movement/PlayerMovement.h"

//this makes our program use high performance graphics by default on systems with more than one gpu
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
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(
            sf::VideoMode(
                    sf::VideoMode::getDesktopMode().width,
                    sf::VideoMode::getDesktopMode().height
            ),
            "SFML works!",
            sf::Style::Default, settings);

//    window.setFramerateLimit(165);
    Application application(window);
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
    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

    window->setView(view);
    PlayerMovement player1;


    while (window->isOpen()) {
        window->clear();

        window->setView(view);
        chunkManagement();

        window->draw(text);
        window->draw(currentMosPosX);
        window->draw(currentMosPosY);


        window->display();

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta > 0) {
                        view.zoom(1.1);
                    } else {
                        view.zoom(0.9);
                    }
                }
            }
        }

        player1.move();

        if (player1.playerMovement.right) {
            view.move(4, 0);
        }

        if (player1.playerMovement.left) {
            view.move(-4, 0);
        }
        if (player1.playerMovement.up) {
            view.move(0, -4);
        }
        if (player1.playerMovement.down) {
            view.move(0, 4);
        }

        text.setString(std::to_string(1.f / clock.restart().asSeconds()));

        sf::Vector2f mouse_world = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        currentMosPosX.setString(std::to_string(mouse_world.x));
        currentMosPosY.setString(std::to_string(mouse_world.y));

    }
}

void Application::chunkManagement() {

    rules();

    if (chunksVisible.empty()) {
        chunksVisible.emplace_back(GameChunk(convertChunkLocationToName(sf::Vector2i(0, 0)), *window,
                                             conversion.at(0)));
    } else {
        for (auto i = 0; i < (chunksVisible.size() - 1); i++) {
            conversion.erase(
                    std::remove_if(
                            conversion.begin(),
                            conversion.end(),
                            [&](sf::Vector2i &p) {
                                return p == chunksVisible.at(i).getChunkNumber();
                            }
                    ),
                    conversion.end()
            );
        }

        if (!conversion.empty()) {
            for (int j = 0; j < conversion.size() - 1; j++) {
                chunksVisible.emplace_back(
                        GameChunk(convertChunkLocationToName(conversion.at(j)), *window, conversion.at(j)));
            }
        }
    }


    for (int i = 0; i < chunksVisible.size() - 1; i++) {
        for (int j = 0; j < chunksVisible.size() - 1; j++) {
            if (i != j && chunksVisible.at(j).getChunkNumber() == chunksVisible.at(i).getChunkNumber()) {
                chunksVisible.erase(chunksVisible.begin() + j);
                j--;
            }
        }
    }

    for (auto &i : chunksVisible) {
        i.draw();
    }

}


std::string Application::convertChunkLocationToName(sf::Vector2<int> chunk) {
    return std::string("../Source/FileSystem/" + std::to_string(chunk.x) + "_" + std::to_string(chunk.y) + ".chunk");
}

void Application::rules() {
    intitalRules();

//    big performance boost here! ~around 2x
    for (int i = 0; i < conversion.size() - 1; i++) {
        for (int j = 0; j < conversion.size() - 1; j++) {
            if (i != j && conversion.at(j) == conversion.at(i)) {
                conversion.erase(conversion.begin() + j);
                j--;
            }
        }
    }

}

void Application::intitalRules() {

    //note these magic numbers the size of the chunk blocks (x/y = 32(tiles amount)*48(legnth of each tile) = 1536)
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));


    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x + 1536.f + 1536.f + 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536.f) / 1536.f)));


    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));

    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f - 1536) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y + 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f - 1536.f) / 1536.f)));
    conversion.emplace_back(sf::Vector2i(((window->getView().getCenter().x - 1536.f - 1536.f - 1536.f) / 1536.f),
                                         ((window->getView().getCenter().y - 1536.f) / 1536.f)));

}

