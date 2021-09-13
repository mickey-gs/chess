#ifndef __BPAWN_H_INCLUDED__
#define __BPAWN_H_INCLUDED__

#include "piece.h"
#include "board.h"

class BPawn: public Piece {
    public:
    BPawn();
    std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
};

#endif