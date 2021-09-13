#include "bishop.h"

Bishop::Bishop(std::string col) {
    colour = col;
    name = col + "B";
}

std::vector<sf::Vector2u> Bishop::gen_moves(Board board, sf::Vector2u pos) {
    std::vector<sf::Vector2u> moves;
    std::string enemy_col = (colour == "w" ? "b" : "w");
    sf::Vector2u cursor = pos;

    while (cursor.x > 0 && cursor.y < 7) {
        cursor.x -= 1;
        cursor.y += 1;

        if (board.piece_colour(cursor) != colour) {
            moves.push_back(cursor);
        }

        if (board.piece_colour(cursor) != "none") {
            break;
        }
    }

    cursor = pos;
    while (cursor.x > 0 && cursor.y > 0) {
        cursor.x -= 1;
        cursor.y -= 1;

        if (board.piece_colour(cursor) != colour) {
            moves.push_back(cursor);
        }

        if (board.piece_colour(cursor) != "none") {
            break;
        }
    }

    cursor = pos;
    while (cursor.x < 7 && cursor.y < 7) {
        cursor.x += 1;
        cursor.y += 1;
        
        if (board.piece_colour(cursor) != colour) {
            moves.push_back(cursor);
        }

        if (board.piece_colour(cursor) != "none") {
            break;
        }
    }

    cursor = pos;
    while (cursor.x < 7 && cursor.y > 0) {
        cursor.x += 1;
        cursor.y -= 1;

        if (board.piece_colour(cursor) != colour) {
            moves.push_back(cursor);
        }

        if (board.piece_colour(cursor) != "none") {
            break;
        }
    }

    return moves;
}