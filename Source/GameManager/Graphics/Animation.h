#ifndef TRUGAMING_ANIMATION_H
#define TRUGAMING_ANIMATION_H

#include "../../../Dependencies/Nlohmann/json.hpp"
#include "../../Constants/Singleton.h"


class Animation {
public:
    explicit Animation(int tileToAnimate, std::string &file);

    Animation() = delete;

    unsigned long long &getCurrentTile();

    void update(float time);

private:
    unsigned long long currentTileIndex = 0;
    unsigned long long currentTile = 0;
    float dt = 0;
    std::vector<int> animationTiles;
    std::vector<float> animationTimes;

    nlohmann::json jsonInput;
};

#endif //TRUGAMING_ANIMATION_H
