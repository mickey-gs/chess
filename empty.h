#ifndef __EMPTY_H_INCLUDED__
#define __EMPTY_H_INCLUDED__

#include "piece.h"
#include "board.h"

class Empty: public Piece {
    public:
    Empty();
    std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
};

#endif