#ifndef __WPAWN_H_INCLUDED__
#define __WPAWN_H_INCLUDED__

#include "piece.h"
#include "board.h"

class WPawn: public Piece {
    public:
    WPawn();
    std::vector<sf::Vector2u> gen_moves(Board board);
};

#endif