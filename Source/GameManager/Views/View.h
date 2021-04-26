
#ifndef TRUGAMING_VIEW_H
#define TRUGAMING_VIEW_H

#include <SFML/Graphics.hpp>
#include "../../Constants/Singleton.h"

class View : public sf::Drawable, public sf::Transformable {

public:
    virtual void load(sf::RenderWindow &renderWindow) = 0;

    virtual void windowLogic() = 0;

private:
};

#endif //TRUGAMING_VIEW_H
