#include "king.h"

King::King(std::string col) {
    colour = col;
    name = col + "K";
}

std::vector<sf::Vector2u> King::gen_moves(Board board, sf::Vector2u pos) {
    sf::Vector2u cursor = pos;
    std::vector<sf::Vector2u> moves;

    if (cursor.y < 7) {
        cursor.y += 1;
        cursor.x -= 1;
        for (int i = -1; i <= 1; i++) {
            if (cursor.x >= 0 && cursor.x <= 7) {
                if (board.piece_colour(cursor) != colour) {
                    moves.push_back(sf::Vector2u(cursor.x, cursor.y));
                }
            }
            cursor.x++;
            if (cursor.x < 0 || cursor.x > 7) { break; }
        }
    }

    cursor = pos;
    cursor.x -= 1;
    for (int i = -1; i <= 1; i++) {
        if (cursor.x >= 0 && cursor.x <= 7) {
            if (board.piece_colour(cursor) != colour) {
                moves.push_back(sf::Vector2u(cursor.x, cursor.y));
            }
        }
        cursor.x++;
        if (cursor.x < 0 || cursor.x > 7) { break; }
    }

    cursor = pos;
    if (cursor.y > 0) {
        cursor.y -= 1;
        cursor.x -= 1;
        for (int i = -1; i <= 1; i++) {
            if (cursor.x >= 0 && cursor.x <= 7) {
                if (board.piece_colour(cursor) != colour) {
                    moves.push_back(sf::Vector2u(cursor.x, cursor.y));
                }
            }
            cursor.x++;
            if (cursor.x < 0 || cursor.x > 7) { break; }
        }
    }

    return moves;
}