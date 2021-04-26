
#include "WorldView.h"

void WorldView::load(sf::RenderWindow &renderWindow) {
    if (Singleton::getInstance().debug) {
        fpsCounter.setFillColor(sf::Color::Red);
        fpsCounter.setSize(128);
        fpsCounter.setPosition(0, 64);

        mosPosXText.setFillColor(sf::Color::Red);
        mosPosXText.setSize(64);

        mosPosYText.setFillColor(sf::Color::Red);
        mosPosYText.setSize(64);
        mosPosYText.setPosition(0, 128);
    }
    quit.setFillColor(sf::Color::Green);
    resume.setFillColor(sf::Color::Green);
    save.setFillColor(sf::Color::Green);

    mapUpdater.setMapString(this->currentMapLoaded);
    mapUpdater.updateMap();
//    exit(-69);

    nearbyOldChunks.resize(25);

    window = &renderWindow;

    blurredBackground.setFillColor(sf::Color(140, 140, 140, 156));
    optionBox.setFillColor(sf::Color(0, 0, 0, 200));

    player.setView(gameView);
    player.updateCurrentMap(this->currentMapLoaded);


    quit.setString("quit");
    resume.setString("resume");
    save.setString("save");

    background.setVolume(10);

    std::pair<float, float> baseCoord = getEnterPositionInMap();
    gameView.setCenter(baseCoord.first, baseCoord.second);

}

void WorldView::windowLogic() {
    background.play();

    gameView.setSize(sf::Vector2f(window->getSize().x * Singleton::getInstance().zoomLevel,
                                  window->getSize().y * Singleton::getInstance().zoomLevel));
    window->setView(gameView);

    prevPos = curPos;
    Singleton::getInstance().dt = clock1.restart().asMilliseconds();
    if (this->escapedKeyPressed != State::popUpView::popup_ESCAPE) {

        player.move(Singleton::getInstance().dt);

        if (!player.getNextWorld().empty()) {
            this->currentMapLoaded = player.getNextWorld();
            mapUpdater.setMapString(player.getNextWorld());
            mapUpdater.updateMap();
            player.setNextWorld("");
            Singleton::getInstance().updateChunks = true;
            player.updateCurrentMap(this->currentMapLoaded);
            player.updateInteractionTiles();
            std::pair<float, float> baseCoord = getEnterPositionInMap();
            gameView.setCenter(baseCoord.first, baseCoord.second);

        }

        player.setPosition(gameView.getCenter().x - player.getSprite().getTexture()->getSize().x / 2,
                           gameView.getCenter().y - player.getSprite().getTexture()->getSize().y / 2);

        curPos = gameView.getCenter();
        deltaOffSet += curPos - prevPos;

        if (std::abs(deltaOffSet.x) >=
            (Singleton::chunkSize * Singleton::tileSize)) {
            prevPos.x = curPos.x;
            deltaOffSet.x = 0;
            Singleton::getInstance().updateChunks = true;
        }
        if (std::abs(deltaOffSet.y) >=
            (Singleton::chunkSize * Singleton::tileSize)) {
            prevPos.y = curPos.y;
            deltaOffSet.y = 0;
            Singleton::getInstance().updateChunks = true;
        }

        updateChunkInfo();
        if (Singleton::getInstance().debug) {
            updateFPS(gameView);
            updateChunkText(gameView);
        }

        if (Singleton::getInstance().updateChunks) {
            updateChunks();
            Singleton::getInstance().updateChunks = false;
        }

    } else {
        background.pause();

        optionBox.setSize(sf::Vector2f(
                1.f / 3.3f * gameView.getSize().x,
                gameView.getSize().y));

        optionBox.setPosition(
                gameView.getCenter().x - gameView.getSize().x / 6.5f,
                gameView.getCenter().y - gameView.getSize().y / 2.f);

        blurredBackground.setSize(sf::Vector2f(
                gameView.getSize().x,
                gameView.getSize().y)
        );

        blurredBackground.setPosition(
                gameView.getCenter().x - gameView.getSize().x / 2.f,
                gameView.getCenter().y - gameView.getSize().y / 2.f);

        quit.setSize(Singleton::getInstance().zoomLevel * 128.f);
        resume.setSize(Singleton::getInstance().zoomLevel * 128.f);
        save.setSize(Singleton::getInstance().zoomLevel * 128.f);


        quit.setPosition(gameView.getCenter().x - quit.getSize().width / 2.f,
                         gameView.getCenter().y + (Singleton::getInstance().zoomLevel * 200)
        );

        save.setPosition(gameView.getCenter().x - save.getSize().width / 2.f,
                         gameView.getCenter().y
        );

        resume.setPosition(gameView.getCenter().x - resume.getSize().width / 2.f,
                           gameView.getCenter().y - (Singleton::getInstance().zoomLevel * 400)
        );

        quitBox.left = quit.getPosition().x;
        quitBox.top = quit.getPosition().y;
        quitBox.width = quit.getSize().width;
        quitBox.height = quit.getSize().height;

        resumeBox.left = resume.getPosition().x;
        resumeBox.top = resume.getPosition().y;
        resumeBox.width = resume.getSize().width;
        resumeBox.height = resume.getSize().height;

        saveBox.left = save.getPosition().x;
        saveBox.top = save.getPosition().y;
        saveBox.width = save.getSize().width;
        saveBox.height = save.getSize().height;

        auto translated_pos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (quitBox.contains(translated_pos)) {
                updatePositionInWorldLeaving();
                this->setNextView(State::NONE);
            }
        }
    }
}

void WorldView::updateFPS(sf::View &view) {
    fpsCounter.setString(std::to_string(1.f / clock.restart().asSeconds()));
    fpsCounter.setPosition(view.getCenter().x, view.getCenter().y + 100);
}

void WorldView::updateChunkText(sf::View &gameFrame) {

    mosPosXText.setString(std::to_string(currentChunk.first) + "T");
    mosPosYText.setString(std::to_string(currentChunk.second));

    mosPosXText.setPosition
            (gameFrame.getCenter().x, gameFrame.getCenter().y);
    mosPosYText.setPosition
            (gameFrame.getCenter().x, gameFrame.getCenter().y + 50);
}

void WorldView::updateChunks() {
    nearbyNewChunks = find(3, currentChunk);
    std::vector<GameChunk>().swap(gameChunksAroundPlayer);

    for (auto &i : nearbyNewChunks) {
        gameChunksAroundPlayer.emplace_back(i, this->currentMapLoaded);
    }

}


void WorldView::updateChunkInfo() {
    currentChunk.first = (window->getView().getCenter().x) /
                         (Singleton::chunkSize * Singleton::tileSize);
    currentChunk.second = (window->getView().getCenter().y) /
                          (Singleton::chunkSize * Singleton::tileSize);

}

void WorldView::updateAnimationTiles() const {
    float timePass = animationClock.restart().asMilliseconds();
    for (auto &i : gameChunksAroundPlayer) {
        i.incrementUpdateTime(timePass);
        i.updateTilesIfNeeded();
    }
}



