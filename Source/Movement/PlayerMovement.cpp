
#include "PlayerMovement.h"

void PlayerMovement::moveDown () {
	playerMovement.down = ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ));
}

void PlayerMovement::moveLeft () {
	playerMovement.left = ( sf::Keyboard::isKeyPressed ( sf::Keyboard::A ));
}

void PlayerMovement::moveRight () {
	playerMovement.right = ( sf::Keyboard::isKeyPressed ( sf::Keyboard::D ));

}

void PlayerMovement::moveUp () {
	playerMovement.up = ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ));
}

void PlayerMovement::move () {
	moveUp ();
	moveDown ();
	moveRight ();
	moveLeft ();
}
