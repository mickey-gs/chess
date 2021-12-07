#ifndef __QUEEN_H_INCLUDED__
#define __QUEEN_H_INCLUDED__

#include "../piece/piece.h"
#include "../board/board.h"

class Queen: public Piece {
    public:
    Queen(std::string col);
    std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
};

#endif