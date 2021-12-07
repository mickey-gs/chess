#ifndef __PIECE_H_INCLUDED__
#define __PIECE_H_INCLUDED__

class Board;

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class Piece {
    public: 
    Piece();
    Piece(int rank, int file);
    std::vector<sf::Vector2u> gen_moves();
    virtual std::vector<sf::Vector2u> gen_moves(Board board, sf::Vector2u pos);
    std::string getColour() { return colour; };
    std::string name;

    protected:
    std::string colour;
};

#endif