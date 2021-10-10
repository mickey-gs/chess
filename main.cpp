#include <SFML/Graphics.hpp>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "board.h"
#include "moverequest.h"

int main() {
    sf::RenderWindow win(sf::VideoMode(800, 800), "Chess");
    std::vector<std::vector<sf::RectangleShape> > squares;
    sf::Vector2u dims = win.getSize();
    std::vector<sf::RectangleShape> buffer;
    sf::Texture text;
    text.loadFromFile("./assets/wood_grain.jpg");
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

        sf::Texture piece_texture;
        sf::RectangleShape piece;
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                sf::RectangleShape sh(sf::Vector2f(win.getSize().x/8, win.getSize().y/8));
                sh.setPosition((dims.x / 8) * (file % 8), dims.y - (dims.y / 8 * (rank + 1)));
                if ((rank+file) % 2 == 0) {
                    sh.setFillColor(sf::Color(140, 100, 100));
                }
                else {
                    sh.setFillColor(sf::Color::White);
                }
                sh.setTexture(&text);
                win.draw(sh);
                std::string name = board.get_name(sf::Vector2u(file, rank));
                if (name != "  ") {
                    piece_texture.loadFromFile("./assets/" + name + ".png");
                    piece.setTexture(&piece_texture);
                    piece.setSize(sf::Vector2f(dims.x / 8, dims.y / 8));
                    piece.setPosition(sf::Vector2f(
                        (dims.x / 8) * (file % 8), dims.y - (dims.y / 8 * (rank + 1))));
                    win.draw(piece);
                }
            }
        }
        win.display();

        sf::Vector2u origin(10, 10);
        do {
            sf::Event e;
            while (win.pollEvent(e)) {
                if (e.type == sf::Event::MouseButtonPressed) {
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f pos(float(e.mouseButton.x), 
                            float(e.mouseButton.y)); 
                        pos.x = pos.x / dims.x * 8;
                        pos.y = pos.y / dims.y * 8;
                        if (0 <= pos.x && pos.x < 8 && 0 <= pos.y && pos.y < 8) {
                            origin.x = pos.x;
                            origin.y = pos.y;
                            origin.y = 7 - origin.y;
                        }
                    }
                }
            }
        } while (origin.x == 10 || board.piece_colour(origin) != std::string(1, board.get_turn()));

        sf::Vector2u dest(10, 10);
        do {
            sf::Event e;
            while (win.pollEvent(e)) {
                if (e.type == sf::Event::MouseButtonPressed) {
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f pos(float(e.mouseButton.x), 
                            float(e.mouseButton.y)); 
                        pos.x = pos.x / dims.x * 8;
                        pos.y = pos.y / dims.y * 8;
                        if (0 <= pos.x && pos.x < 8 && 0 <= pos.y && pos.y < 8) {
                            dest.x = pos.x;
                            dest.y = pos.y;
                            dest.y = 7 - dest.y;
                        }
                    }
                }
            }
        } while (dest.x == 10 || board.piece_colour(dest) == std::string(1, board.get_turn()));

        move.origin = origin;
        move.destination = dest;
        if (board.request_move(move)) {
            board.make_move(move);
        }

        system(("ruby analyse.rb " + board.gen_fen()).c_str());

        std::string line;
        std::ifstream analysis("bestmove.txt");
        analysis >> line;
        if (line == "checkmate") {
            std::cout << "Checkmate!" << std::endl;
            break;
        }
        else if (line == "stalemate") {
            std::cout << "Stalemate." << std::endl;
            break;
        }
        else {
            std::cout << "Best move: " << line << std::endl;
        }
    }

    return 0;
}