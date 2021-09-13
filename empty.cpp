#include "empty.h"

Empty::Empty() {
    colour = "none";
    name = "  ";
}

std::vector<sf::Vector2u> Empty::gen_moves(Board board, sf::Vector2u pos) {
    return {};    
}