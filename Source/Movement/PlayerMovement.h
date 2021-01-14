//
// Created by nicka on 12/29/2020.
//

#ifndef TRUGAMING_PLAYERMOVEMENT_H
#define TRUGAMING_PLAYERMOVEMENT_H


#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class PlayerMovement{


private:


    void moveUp();
    void moveRight();
    void moveLeft();
    void moveDown();
public:
    struct movementDirection {
        bool up = false,
            right = false,
            left = false ,
            down = false,
            upRight = false,
            upLeft = false,
            downLeft = false,
            downRight = false;
    } playerMovement;



    void move();

    void printCurrentDirection() const {
      std::cout <<
      playerMovement.down << "\n" <<
      playerMovement.left << "\n" <<
      playerMovement.right << "\n" <<
      playerMovement.up << "\n" << std::endl;
    }

};


#endif //TRUGAMING_PLAYERMOVEMENT_H
