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
#include <map>
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
    bool in_check();
    std::string piece_colour(sf::Vector2u square);
    std::string get_name(sf::Vector2u square);
    sf::Vector2u en_passant_sq;
    std::map<std::string, bool> castling_rights;
    std::string gen_fen();
    char get_turn() {
        return turn;
    }
    bool in_checkmate();

    private:
    std::vector<std::vector<Piece*> > board;
    char turn;
    void save_to_strings(std::vector<std::vector<std::string> > &strings);
    void revert_from_strings(std::vector<std::vector<std::string> > &strings);
    void make_fake_move(MoveRequest move);
};

#endif