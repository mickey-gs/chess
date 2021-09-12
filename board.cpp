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

void Board::display() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            std::cout << board[j][i]->name << " ";
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