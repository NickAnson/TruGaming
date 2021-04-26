//
// Created by Nick on 3/9/2021.
//

#include "Animation.h"

void Animation::update(float time) {
    if (!animationTimes.empty()) {
        dt += time;
        if (dt > animationTimes.at(currentTileIndex)) {
            if (currentTileIndex == animationTiles.size() - 1) {
                currentTileIndex = 0;
            } else {
                currentTileIndex++;
            }
            dt = 0;
            currentTile = animationTiles.at(currentTileIndex);
        }
    }
}

unsigned long long &Animation::getCurrentTile() {
    return currentTile;
}

Animation::Animation(int tileID, std::string &file) {
    jsonInput = nlohmann::json::parse(file);

    for (auto &i : jsonInput["tileAnimation"]) {
        if (tileID == i["id"]) {

            for (auto &animationIDs : i["animation"]) {
                animationTiles.emplace_back(animationIDs["tileid"]);
                animationTimes.emplace_back(animationIDs["duration"]);
            }

            currentTile = animationTiles.front();
        }
    }
}
