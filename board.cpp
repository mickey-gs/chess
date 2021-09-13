#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "board.h"
#include "piece.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "wpawn.h"
#include "bpawn.h"
#include "knight.h"
#include "empty.h"
#include "moverequest.h"

void Board::display() {
    std::cout << std::endl << std::endl;
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            std::cout << board[file][rank]->name << " ";
        }
        std::cout << std::endl;
    }
}

sf::Vector2u Board::to_program_coords(char file, int rank) {
    return sf::Vector2u(int(file - 97), rank -1);
}

std::string Board::to_chess_coords(sf::Vector2u input) {
    return (char(input.x + 97) + std::to_string(input.y + 1));
}

std::string Board::piece_colour(sf::Vector2u square) {
    return board[square.x][square.y]->getColour();
}

bool Board::request_move(MoveRequest move) {
    sf::Vector2u origin = move.origin;
    std::vector<sf::Vector2u> moves = 
        board[origin.x][origin.y]->gen_moves(*this, origin);

    std::cout << "list of all legal moves for piece:" << std::endl;
    for (int i = 0; i != moves.size(); i++) {
        std::cout << to_chess_coords(moves[i]) << std::endl;
    }

    if (std::find(moves.begin(), moves.end(), move.destination) !=
    moves.end()) {
        return true;
    }
    
    else {
        return false;
    }
}

void Board::make_move(MoveRequest move) {
    sf::Vector2u origin = move.origin;
    sf::Vector2u dest = move.destination;

    std::swap(board[origin.x][origin.y], board[dest.x][dest.y]);

    if (piece_colour(origin) != piece_colour(dest)) {
        delete board[origin.x][origin.y];
        board[origin.x][origin.y] = new Empty();
    }
}

void Board::setup() {
    std::vector<Piece*> buffer;
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            Piece* p;
            if (rank == 1) {
                p = new WPawn();
            }

            else if (rank == 6) {
                p = new BPawn();
            }

            else if (rank == 0 || rank == 7) {
                switch (file) {
                    case 0:
                    p = new Rook((rank == 0 ? "w" : "b"));
                    break;

                    case 1:
                    p = new Knight((rank == 0 ? "w" : "b"));
                    break;

                    case 2:
                    p = new Bishop((rank == 0 ? "w" : "b"));
                    break;

                    case 3:
                    p = new Queen((rank == 0 ? "w" : "b"));
                    break;

                    case 4:
                    p = new King((rank == 0 ? "w" : "b"));
                    break;

                    case 5:
                    p = new Bishop((rank == 0 ? "w" : "b"));
                    break;

                    case 6:
                    p = new Knight((rank == 0 ? "w" : "b"));
                    break;

                    case 7:
                    p = new Rook((rank == 0 ? "w" : "b"));
                    break;
                } 
            }

            else {
                p = new Empty();
            }

            buffer.push_back(p);
        }

        board.push_back(buffer);
        buffer.clear();
    }
}