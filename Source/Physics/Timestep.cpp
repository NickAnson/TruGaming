//
// Created by Nick on 2/16/2021.
//

#include "Timestep.h"

bool Timestep::update() {
    if (frameTime > 0.0) {
        return true;
    } else {
        return false;
    }
}
