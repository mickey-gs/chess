#include "wpawn.h"
#include "board.h"

WPawn::WPawn() {
    colour = "w";
    name = colour + "p";
}

std::vector<sf::Vector2u> WPawn::gen_moves(Board board) {
    
}