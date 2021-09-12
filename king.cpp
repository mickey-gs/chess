#include "king.h"

King::King(std::string col) {
    colour = col;
    name = col + "K";
}

std::vector<sf::Vector2u> King::gen_moves(Board board) {
    
}