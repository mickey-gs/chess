#ifndef __BISHOP_H_INCLUDED__
#define __BISHOP_H_INCLUDED__

#include "piece.h"
#include "board.h"

class Bishop: public Piece {
    public:
    Bishop(std::string col);
    std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
};

#endif