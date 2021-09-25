#include <SFML/Graphics.hpp>
#include <algorithm>
#include <stdexcept>
#include "board.h"
#include "moverequest.h"

int main() {
    sf::RenderWindow win(sf::VideoMode(800, 800), "Chess");
    std::vector<std::vector<sf::RectangleShape> > squares;
    sf::Vector2u dims = win.getSize();
    std::vector<sf::RectangleShape> buffer;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape sh(sf::Vector2f(win.getSize().x/8, win.getSize().y/8));
            sh.setPosition((dims.x / 8) * (j % 8), (dims.y / 8) * (7 - i));
            if ((i+j) % 2 == 0) {
                sh.setFillColor(sf::Color::Black);
            }
            else {
                sh.setFillColor(sf::Color::White);
            }
            buffer.push_back(sh);
        }
        squares.push_back(buffer);
    }
    sf::RectangleShape white(sf::Vector2f(win.getSize().x/2, win.getSize().y/2));
    white.setFillColor(sf::Color::White);
    sf::RectangleShape black = white;
    black.setFillColor(sf::Color::Blue);
    win.clear(sf::Color::Black);
    Board board;
    board.setup();
    board.display();
    MoveRequest move;
    while (win.isOpen()) {
        win.clear(sf::Color::Black);
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }

        for (int i = 0; i != squares.size(); i++) {
            for (int j = 0; j != squares[i].size(); j++) {
                win.draw(squares[i][j]);
            }
        }
        win.display();

        // do {
        //     char file_0, file_1;
        //     int rank_0, rank_1;

        //     std::cout << "Origin square? ";
        //     std::cin >> file_0 >> rank_0;
        //     move.origin = Board::to_program_coords(file_0, rank_0);

        //     std::cout << "Destination square? ";
        //     std::cin >> file_1 >> rank_1;
        //     move.destination = Board::to_program_coords(file_1, rank_1);

        //     if (board.request_move(move)) {
        //         board.make_move(move);
        //     }

        //     board.display();
        // } while (true);
    }

    return 0;
}