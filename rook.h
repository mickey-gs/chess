#ifndef __ROOK_H_INCLUDED__
#define __ROOK_H_INCLUDED__

#include "piece.h"
#include "board.h"

class Rook: public Piece {
    public:
    Rook(std::string col);
    std::vector<sf::Vector2u> gen_moves(Board board);
};

#endif