#include "knight.h"

Knight::Knight(std::string col) {
    colour = col;
    name = col + "N";
}

std::vector<sf::Vector2u> Knight::gen_moves(Board board, sf::Vector2u pos) {
    int file = pos.x;
    int rank = pos.y;
    std::vector<sf::Vector2u> moves;

    if (file >= 2) {
        if (rank <= 6) {
            if (board.piece_colour(sf::Vector2u(file-2, rank+1)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file - 2, rank + 1));
            }
        }

        if (rank >= 1) {
            if (board.piece_colour(sf::Vector2u(file-2, rank-1)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file - 2, rank - 1));
            }
        }
    }

    if (file >= 1) {
        if (rank <= 5) {
            if (board.piece_colour(sf::Vector2u(file-1, rank+2)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file - 1, rank + 2));
            }
        }

        if (rank >= 2) {
            if (board.piece_colour(sf::Vector2u(file-1, rank-2)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file - 1, rank - 2));
            }
        }
    }

    if (file <= 5) {
        if (rank <= 6) {
            if (board.piece_colour(sf::Vector2u(file+2, rank+1)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file + 2, rank + 1));
            }
        }

        if (rank >= 1) {
            if (board.piece_colour(sf::Vector2u(file+2, rank-1)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file + 2, rank - 1));
            }
        }
    }

    if (file <= 6) {
        if (rank <= 5) {
            if (board.piece_colour(sf::Vector2u(file+1, rank+2)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file + 1, rank + 2));
            }
        }

        if (rank >= 2) {
            if (board.piece_colour(sf::Vector2u(file+1, rank-2)) 
                    != colour) {
                moves.push_back(sf::Vector2u(file + 1, rank - 2));
            }
        }
    }

    return moves;
}