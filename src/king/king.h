#ifndef __KING_H_INCLUDED__
#define __KING_H_INCLUDED__

#include "../piece/piece.h"
#include "../board/board.h"

class King: public Piece {
    public:
    King(std::string col);
    std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
};

#endif