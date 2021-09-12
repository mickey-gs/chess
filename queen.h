#ifndef __QUEEN_H_INCLUDED__
#define __QUEEN_H_INCLUDED__

#include "piece.h"
#include "board.h"

class Queen: public Piece {
    public:
    Queen(std::string col);
    std::vector<sf::Vector2u> gen_moves(Board board);
};

#endif