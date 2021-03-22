//
// Created by Nick on 2/16/2021.
//

#ifndef TRUGAMING_TIMESTEP_H
#define TRUGAMING_TIMESTEP_H

#include <chrono>

class Timestep {
public:
    bool update();

private:
    std::chrono::high_resolution_clock currentTime;
    double t = 0.0;
    double dt = 1.0 / 60.0;
    double frameTime = 0;

};


#endif //TRUGAMING_TIMESTEP_H
