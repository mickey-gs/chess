#ifndef __MOVEREQUEST_H_INCLUDED__
#define __MOVEREQUEST_H_INCLUDED__

#include <SFML/Graphics.hpp>

class MoveRequest {
    public:
    sf::Vector2u origin;
    sf::Vector2u destination;
};

#endif