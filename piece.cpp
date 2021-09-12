#include "piece.h"
#include <string>
#include <SFML/Graphics.hpp>

Piece::Piece() {
    colour = 'a';
    name = "";
}

Piece::Piece(int rank, int file) {
    if (rank == 1 || rank == 6) {
        name = "p";
    }

    else if (rank == 0 || rank == 7) {
        switch (file) {
            case 0:
            name = "R";
            break;

            case 1:
            name = "N";
            break;

            case 2:
            name = "B";
            break;

            case 3:
            name = "Q";
            break;

            case 4:
            name = "K";
            break;

            case 5:
            name = "B";
            break;

            case 6:
            name = "N";
            break;

            case 7:
            name = "R";
            break;
        } 
    }

    if (rank == 0 || rank == 1) {
        name = "w" + name;
    }

    else if (rank == 6 || rank == 7) {
        name = "b" + name;
    }
}
