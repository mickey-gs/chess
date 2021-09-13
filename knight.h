#ifndef __KNIGHT_H_INCLUDED__
#define __KNIGHT_H_INCLUDED__

#include "piece.h"
#include "board.h"

class Knight: public Piece {
    public:
    Knight(std::string col);
    std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
};

#endif