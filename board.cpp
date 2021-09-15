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

char Board::promotion_prompt() {
    std::cout
    << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl
    << "What do you want to promote to? (q/r/b/n) ";
    char response;
    std::cin >> response;
    std::cout 
    << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
    << std::endl;

    return response;
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

    if (board[origin.x][origin.y]->name == "wp"
    && (dest.y - origin.y == 2)) {
        en_passant_sq = sf::Vector2u(dest.x, dest.y - 1);
    }
    if (board[origin.x][origin.y]->name == "bp"
    && (origin.y - dest.y == 2)) {
        en_passant_sq = sf::Vector2u(dest.x, dest.y + 1);
    }

    std::swap(board[origin.x][origin.y], board[dest.x][dest.y]);

    if (board[dest.x][dest.y]->name[1] == 'p'
    && dest.x - origin.x != 0
    && board[origin.x][origin.y]->getColour() == "none") {
        if (board[dest.x][dest.y]->name == "wp") {
            delete board[dest.x][dest.y-1];
            board[dest.x][dest.y-1] = new Empty();
        }
        else {
            delete board[dest.x][dest.y+1];
            board[dest.x][dest.y+1] = new Empty();
        }
    }

    if (piece_colour(origin) != piece_colour(dest)) {
        delete board[origin.x][origin.y];
        board[origin.x][origin.y] = new Empty();
    }

    if (board[dest.x][dest.y]->name != "wp"
    && board[dest.x][dest.y]->name != "bp") {
        en_passant_sq = sf::Vector2u(10, 10);
    }

    for (int file = 0; file != 8; file++) {
        if (board[file][7]->name == "wp"
        || board[file][0]->name == "bp") {
            char piece = promotion_prompt();

            switch (piece) {
                case 'q':
                if (board[file][7]->name == "wp") {
                    delete board[file][7];
                    board[file][7] = new Queen("w");
                }
                else {
                    delete board[file][0];
                    board[file][0] = new Queen("b");
                }
                break;

                case 'r':
                if (board[file][7]->name == "wp") {
                    delete board[file][7];
                    board[file][7] = new Rook("w");
                }
                else {
                    delete board[file][0];
                    board[file][0] = new Rook("b");
                }
                break;

                case 'b':
                if (board[file][7]->name == "wp") {
                    delete board[file][7];
                    board[file][7] = new Bishop("w");
                }
                else {
                    delete board[file][0];
                    board[file][0] = new Bishop("b");
                }
                break;

                case 'n':
                if (board[file][7]->name == "wp") {
                    delete board[file][7];
                    board[file][7] = new Knight("w");
                }
                else {
                    delete board[file][0];
                    board[file][0] = new Knight("b");
                }
                break;
            }
        }
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