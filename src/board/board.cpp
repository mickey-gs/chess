#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "board.h"
#include "../piece/piece.h"
#include "../bishop/bishop.h"
#include "../rook/rook.h"
#include "../queen/queen.h"
#include "../king/king.h"
#include "../wpawn/wpawn.h"
#include "../bpawn/bpawn.h"
#include "../knight/knight.h"
#include "../empty/empty.h"
#include "../moverequest/moverequest.h"

void Board::display() {
    std::cout << std::endl << std::endl;
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            std::cout << board[file][rank]->name << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Castling rights: " << std::endl;
    std::cout << "White: " << "         " << "Black: " << std::endl;
    std::cout << "Kingside: ";
    std::cout << (castling_rights["wK"] ? "Yes" : "No ");
    std::cout << "   ";
    std::cout << (castling_rights["bK"] ? "Yes" : "No");
    std::cout << std::endl;
    std::cout << "Queenside: ";
    std::cout << (castling_rights["wQ"] ? "Yes  " : "No   ");
    std::cout << (castling_rights["bQ"] ? "Yes" : "No");
    std::cout << std::endl;
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

std::string Board::get_name(sf::Vector2u square) {
    return board[square.x][square.y]->name;
}

bool Board::in_check() {
    std::vector<sf::Vector2u> total_moves;
    std::vector<sf::Vector2u> buffer;
    for (int file = 0; file != 8; file++) {
        for (int rank = 0; rank != 8; rank++) {
            buffer = 
            board[file][rank]->gen_moves(*this, sf::Vector2u(file, rank));
            for (int i = 0; i != buffer.size(); i++) {
                total_moves.push_back(buffer[i]);
            }
            buffer.clear();
        }
    }

    for (int i = 0; i != total_moves.size(); i++) {
        if (board[total_moves[i].x][total_moves[i].y]->name == std::string(1, turn) + "K") {
            return true;
        }
    }

    return false;
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

    if (board[origin.x][origin.y]->name[0] != turn) {
        return false;
    }

    std::vector<sf::Vector2u> moves = 
        board[origin.x][origin.y]->gen_moves(*this, origin);

    std::cout << "list of all legal moves for piece:" << std::endl;
    for (int i = 0; i != moves.size(); i++) {
        std::cout << to_chess_coords(moves[i]) << std::endl;
    }

    if (std::find(moves.begin(), moves.end(), move.destination) ==
    moves.end()) {
        return false;
    }
    
    else {
        std::vector<std::vector<std::string> > strings;
        std::vector<std::string> vec;
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                vec.push_back("");
            }
            strings.push_back(vec);
            vec.clear();
        }
        save_to_strings(strings);

        if (board[move.origin.x][move.origin.y]->name[1] == 'K' 
        && (move.destination.x - move.origin.x > 1 || move.destination.x - move.origin.x > 1)) {
            if (in_check()) {
                return false;
            }
            if (move.destination.x > move.origin.x) {
                MoveRequest half_castle;
                half_castle.origin = move.origin;
                half_castle.destination = move.destination;
                half_castle.destination.x -= 1;
                make_fake_move(half_castle);
                turn = (turn == 'b' ? 'w' : 'b');
                if (in_check()) {
                    revert_from_strings(strings);
                    return false;
                }
            }
            else {
                MoveRequest half_castle;
                half_castle.origin = move.origin;
                half_castle.destination = move.destination;
                half_castle.destination.x += 1;
                make_fake_move(half_castle);
                turn = (turn == 'b' ? 'w' : 'b');
                if (in_check()) {
                    revert_from_strings(strings);
                    return false;
                }
            }
        }

        make_fake_move(move);
        turn = (turn == 'b' ? 'w' : 'b');
        bool flag = !in_check();

        revert_from_strings(strings);
        return flag;
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

    if (board[origin.x][origin.y]->name[1] == 'K') {
        castling_rights[board[origin.x][origin.y]->name] = false;
        castling_rights[std::string(1, turn) + "Q"] = false;
    }
    else if (board[origin.x][origin.y]->name[1] == 'R') {
        if (origin.y == 0) {
            if (origin.x == 0) {
                castling_rights["wQ"] = false;
            }
            else if (origin.x == 7) {
                castling_rights["wK"] = false;
            }
        }
        else if (origin.y == 7) {
            if (origin.x == 0) {
                castling_rights["bQ"] = false;
            }
            else if (origin.x == 7) {
                castling_rights["bK"] = false;
            }
        }
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

    if (board[dest.x][dest.y]->name != "wp"
    && board[dest.x][dest.y]->name != "bp") {
        en_passant_sq = sf::Vector2u(10, 10);
    }

    if (sf::Vector2u(dest.x, dest.y + 1) != en_passant_sq &&
    sf::Vector2u(dest.x, dest.y - 1) != en_passant_sq) {
        en_passant_sq = sf::Vector2u(10, 10);
    }

    if ((dest.x - origin.x > 1 || dest.x - origin.x > 1) && 
    board[dest.x][dest.y]->name[1] == 'K') {
        if (dest.x == 2) {
            std::swap(board[0][dest.y], board[dest.x+1][dest.y]);
        }
        else {
            std::swap(board[7][dest.y], board[dest.x-1][dest.y]);
        }
    }

    turn = (turn == 'w' ? 'b' : 'w');
}

void Board::make_fake_move(MoveRequest move) {
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

    if (board[dest.x][dest.y]->name != "wp"
    && board[dest.x][dest.y]->name != "bp") {
        en_passant_sq = sf::Vector2u(10, 10);
    }

    if (sf::Vector2u(dest.x, dest.y + 1) != en_passant_sq &&
    sf::Vector2u(dest.x, dest.y - 1) != en_passant_sq) {
        en_passant_sq = sf::Vector2u(10, 10);
    }
    turn = (turn == 'w' ? 'b' : 'w');
}

void Board::setup() {
    turn = 'w';
    castling_rights["wQ"] = true;
    castling_rights["wK"] = true;
    castling_rights["bQ"] = true;
    castling_rights["bK"] = true;
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


void Board::save_to_strings(std::vector<std::vector<std::string> > &strings) {
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            strings[rank][file] = board[rank][file]->name;
        }
    }
}

void Board::revert_from_strings(std::vector<std::vector<std::string> > &strings) {
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            delete board[rank][file];
            Piece* p;

            if (strings[rank][file][1] == 'N') {
                p = new Knight(std::string(1, strings[rank][file][0]));
            }
            else if (strings[rank][file][1] == 'B') {
                p = new Bishop(std::string(1, strings[rank][file][0]));
            }
            else if (strings[rank][file][1] == 'R') {
                p = new Rook(std::string(1, strings[rank][file][0]));
            }
            else if (strings[rank][file][1] == 'Q') {
                p = new Queen(std::string(1, strings[rank][file][0]));
            }
            else if (strings[rank][file][1] == 'K') {
                p = new King(std::string(1, strings[rank][file][0]));
            }
            else if (strings[rank][file] == "wp") {
                p = new WPawn();
            }
            else if (strings[rank][file] == "bp") {
                p = new BPawn();
            }
            else {
                p = new Empty();
            }

            board[rank][file] = p;
        }
    }
}

std::string Board::gen_fen() {
    std::string data;
    for (int rank = 7; rank >= 0; rank--) {
        int blanks = 0;
        for (int file = 0; file < 8; file++) {
            if (board[file][rank]->name[1] == 'K') {
                if (blanks > 0) {
                    data += std::to_string(blanks);
                    blanks = 0;
                }
                if (board[file][rank]->name[0] == 'w') {
                    data += "K";
                }
                else {
                    data += "k";
                }
            }
            else if (board[file][rank]->name[1] == 'Q') {
                if (blanks > 0) {
                    data += std::to_string(blanks);
                    blanks = 0;
                }
                if (board[file][rank]->name[0] == 'w') {
                    data += "Q";
                }
                else {
                    data += "q";
                }
            }
            else if (board[file][rank]->name[1] == 'R') {
                if (blanks > 0) {
                    data += std::to_string(blanks);
                    blanks = 0;
                }
                if (board[file][rank]->name[0] == 'w') {
                    data += "R";
                }
                else {
                    data += "r";
                }
            }
            else if (board[file][rank]->name[1] == 'N') {
                if (blanks > 0) {
                    data += std::to_string(blanks);
                    blanks = 0;
                }
                if (board[file][rank]->name[0] == 'w') {
                    data += "N";
                }
                else {
                    data += "n";
                }
            }
            else if (board[file][rank]->name[1] == 'B') {
                if (blanks > 0) {
                    data += std::to_string(blanks);
                    blanks = 0;
                }
                if (board[file][rank]->name[0] == 'w') {
                    data += "B";
                }
                else {
                    data += "b";
                }
            }
            else if (board[file][rank]->name[1] == 'p') {
                if (blanks > 0) {
                    data += std::to_string(blanks);
                    blanks = 0;
                }
                if (board[file][rank]->name[0] == 'w') {
                    data += "P";
                }
                else {
                    data += "p";
                }
            }
            else {
                blanks++;
            }
        }
        if (blanks > 0) {
            data += std::to_string(blanks);
        }
        
        if (rank != 0) {
            data += "/";
        }
    }

    data += " " + std::string(1, turn);

    data += " ";

    bool flag = true;
    if (castling_rights["wK"]) {
        data += "K";
        flag = false;
    }
    if (castling_rights["wQ"]) {
        data += "Q";
        flag = false;
    }
    if (castling_rights["bK"]) {
        data += "k";
        flag = false;
    }
    if (castling_rights["bQ"]) {
        data += "q";  
        flag = false;      
    }
    if (flag) {
        data += "-";
    }

    data += " ";
    if (en_passant_sq.x != 10) {
        data += to_chess_coords(en_passant_sq);
    }
    else {
        data += "-";
    }

    data += " 20 20";

    return data;
}

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
        char buffer[1024];
        std::string result = "";
        while (fgets(buffer, 1024, pipe) != NULL) {
          result += buffer;
        }
        pclose(pipe);
        return result;
}

bool Board::in_checkmate() {
 //   turn = ('w' ? 'b' : 'w');
    std::fstream file;
    file.open("cmds.txt");
    file << "position fen " << gen_fen() << "\n" << "go" << std::endl;
    std::string analysis = exec("stockfish < cmds.txt");
    // turn = ('w' ? 'b' : 'w');

    // if (analysis.find("score mate 0") != std::string::npos) {
    //     return true;
    // }

    // file.open("cmds.txt");
    // file << "position fen " << gen_fen() << "\n" << "go" << std::endl;
    // analysis = exec("stockfish < cmds.txt");

    return (analysis.find("score mate 0") != std::string::npos);
}

char Board::get_colour(sf::Vector2u square) {
    return board[square.x][square.y]->name[0];
}


std::vector<sf::Vector2u> Board::gen_moves(sf::Vector2u square) {
    return board[square.x][square.y]->gen_moves();
}

bool Board::in_stalemate() {
    std::fstream file;
    file.open("cmds.txt");
    file << "position fen " << gen_fen() << "\n" << "go" << std::endl;
    std::string analysis = exec("stockfish < cmds.txt");
    
    return (analysis.find("score cp 0") != std::string::npos &&
        analysis.find("bestmove (none)") != std::string::npos);
}