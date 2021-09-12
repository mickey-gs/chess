#include "bishop.h"

Bishop::Bishop(std::string col) {
    colour = col;
    name = col + "B";
}

std::vector<sf::Vector2u> Bishop::gen_moves(Board board) {
    
}