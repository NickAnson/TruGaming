#include <SFML/Graphics.hpp>

#include "Application.h"
#include "GameManager/MapEditor/MapUpdater.h"
#include "GameManager/GameChunks/ChunkFinder.h"
#include "GameManager/Entities/Player.h"




//this makes our program use high performance graphics by default on systems with more than one gpu



int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    //    settings.sRgbCapable = false;
    //    settings.depthBits = 8;
    //    settings.minorVersion = 3;

    sf::RenderWindow window(
            Singleton::getInstance().computerScreen,
            "TruGame",
            sf::Style::Fullscreen,
            settings);

    Application application(window);

//    window.setVerticalSyncEnabled(true);
//

    application.setup();

    application.run();

    return 0;
}


void Application::setup() {
    fpsCounter.setFillColor(sf::Color::Red);
    fpsCounter.setSize(128);
    fpsCounter.setPosition(sf::Vector2i(0, 64));

    mosPosXText.setFillColor(sf::Color::Red);
    mosPosXText.setSize(64);

    mosPosYText.setFillColor(sf::Color::Red);
    mosPosYText.setSize(64);
    mosPosYText.setPosition(sf::Vector2i(0, 128));

    gameView.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    Singleton::getInstance().defaultPlayerView = gameView;

}


void Application::run() {
    nearbyOldChunks.resize(25);

    MapUpdater mapUpdater("map_0");
    mapUpdater.updateMap();

    mouse_world = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
//    std::vector<sf::Sprite> playerSprites;


    Player player;
    player.setPosition(0, 0);
    player.setView(gameView);

    sf::Clock clock;

    sf::Event event{};
    sf::Clock clock1;

    sf::Vector2f prevPos{0, 0};
    sf::Vector2f curPos{0, 0};
    curPos = gameView.getCenter();

    sf::Clock clock3;

    animationClock.restart();

    while (window->isOpen()) {
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta < 0) {
                        gameView.zoom(2);
                    } else {
                        gameView.zoom(0.5);

                    }
                }
            }
        }

        prevPos = curPos;
        Singleton::getInstance().dt = clock1.restart().asSeconds();
        player.move(Singleton::getInstance().dt * 1000.0);
        player.setPosition(gameView.getCenter().x - player.getSprite().getTexture()->getSize().x / 2,
                           gameView.getCenter().y - player.getSprite().getTexture()->getSize().y / 2);
        curPos = gameView.getCenter();
        deltaOffSet += curPos - prevPos;


        if (std::abs(deltaOffSet.x) >=
            (Singleton::chunkSize * Singleton::tileSize)) {
            deltaOffSet.x = 0;
            Singleton::getInstance().updateChunks = true;
        }
        if (std::abs(deltaOffSet.y) >=
            (Singleton::chunkSize * Singleton::tileSize)) {
            deltaOffSet.y = 0;
            Singleton::getInstance().updateChunks = true;
        }

        updateChunkInfo();

        updateFPS(clock, gameView);

        updateChunkText(gameView);

        if (Singleton::getInstance().updateChunks) {
            updateChunks();
            Singleton::getInstance().updateChunks = false;
        }

        window->clear();
        window->setView(gameView);

        updateAnimationTiles();

        drawChunks(window);

//
        window->draw(fpsCounter.getText());
        window->draw(mosPosXText.getText());
        window->draw(mosPosYText.getText());

        window->draw(player.getSprite());

        window->display();

//        dt = clock.restart();

    }
}

void Application::updateFPS(sf::Clock &clock, sf::View &view) {
    fpsCounter.setString(std::to_string(1.f / clock.restart().asSeconds()));
    fpsCounter.setPosition(sf::Vector2i(view.getCenter().x, view.getCenter().y + 100));
}

void Application::updateChunkText(sf::View &gameFrame) {

    mouse_world = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    mosPosXText.setString(std::to_string(currentChunk.first) + "T");
    mosPosYText.setString(std::to_string(currentChunk.second));

    mosPosXText.setPosition(
            sf::Vector2i(gameFrame.getCenter().x, gameFrame.getCenter().y));
    mosPosYText.setPosition(
            sf::Vector2i(gameFrame.getCenter().x, gameFrame.getCenter().y + 50));
}

void Application::updateChunks() {
    nearbyNewChunks = ChunkFinder::find(4, currentChunk);
    std::vector<GameChunk>().swap(gameChunksAroundPlayer);

    for (auto &i : nearbyNewChunks) {
        gameChunksAroundPlayer.emplace_back(i, "map_0");
    }

}

void Application::drawChunks(sf::RenderWindow *renderWindow) {
    for (auto &i : gameChunksAroundPlayer) {
        renderWindow->draw(i);
    }
}

void Application::updateChunkInfo() {
    currentChunk.first = (window->getView().getCenter().x) /
                         (Singleton::chunkSize * Singleton::tileSize);
    currentChunk.second = (window->getView().getCenter().y) /
                          (Singleton::chunkSize * Singleton::tileSize);

}

void Application::updateAnimationTiles() {
    float timePass = animationClock.restart().asMilliseconds();
    for (auto &i : gameChunksAroundPlayer) {
        i.incrementUpdateTime(timePass);
        i.updateTilesIfNeeded();
    }
}

