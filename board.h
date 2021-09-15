#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

class Piece;
class Bishop;
class Knight;
class King;
class Queen;
class Rook;
class BPawn;
class WPawn;
class MoveRequest;

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

class Board {
    public:
    static sf::Vector2u to_program_coords(char file, int rank);
    static std::string to_chess_coords(sf::Vector2u input);
    void display();
    void setup();
    bool request_move(MoveRequest move);
    void make_move(MoveRequest move);
    char promotion_prompt();
    std::string piece_colour(sf::Vector2u square);
    sf::Vector2u en_passant_sq;

    private:
    std::vector<std::vector<Piece*> > board;
};

#endif