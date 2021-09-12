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

    private:
    std::vector<std::vector<Piece*> > board;
};

#endif