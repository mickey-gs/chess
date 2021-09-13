#include <SFML/Graphics.hpp>
#include "board.h"
#include "moverequest.h"

int main()
{
    Board board;
    board.setup();
    board.display();
    MoveRequest move;
    do {
        char file_0, file_1;
        int rank_0, rank_1;
        
        std::cout << "Origin square? ";
        std::cin >> file_0 >> rank_0;
        move.origin = Board::to_program_coords(file_0, rank_0);
        
        std::cout << "Destination square? ";
        std::cin >> file_1 >> rank_1;
        move.destination = Board::to_program_coords(file_1, rank_1);

        if (board.request_move(move)) {
            board.make_move(move);
        }

        board.display();
    } while (true);

    return 0;
}