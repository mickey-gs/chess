#include "bpawn.h"

BPawn::BPawn() {
    colour = "b";
    name = colour + "p";
}

std::vector<sf::Vector2u> BPawn::gen_moves(Board board, sf::Vector2u pos) {
    std::vector<sf::Vector2u> moves;

    if (pos.y > 0) {
        if (board.piece_colour(sf::Vector2u(pos.x, pos.y - 1)) == "none") {
            moves.push_back(sf::Vector2u(pos.x, pos.y - 1));
        }

        if (pos.y == 6 &&
            board.piece_colour(sf::Vector2u(pos.x, pos.y - 2)) == "none") {
            moves.push_back(sf::Vector2u(pos.x, pos.y - 2));
        }

        if (pos.x < 7 &&
            (board.piece_colour(sf::Vector2u(pos.x + 1, pos.y - 1)) == "w"
            || board.en_passant_sq == sf::Vector2u(pos.x+1, pos.y-1))) {
            moves.push_back(sf::Vector2u(pos.x + 1, pos.y - 1));
        }

        if (pos.x > 0 && 
            (board.piece_colour(sf::Vector2u(pos.x - 1, pos.y - 1)) == "w"
            || board.en_passant_sq == sf::Vector2u(pos.x-1, pos.y-1))) {
            moves.push_back(sf::Vector2u(pos.x - 1, pos.y - 1));
        }
    }

    return moves;
}