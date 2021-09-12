#ifndef __PIECE_H_INCLUDED__
#define __PIECE_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class Piece {
    public: 
    Piece();
    Piece(int rank, int file);
    std::string name;

    protected:
    std::string colour;
};

#endif