/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */
#include <iostream>
#include <string>

#include "Game.hpp"

int main() {
    dreamchess::Game game{};

    std::string input_move;

    while (game.is_in_game()) {
        std::cout << "---------------------" << std::endl;
        std::cout << game;
        std::cout << "---------------------" << std::endl;

        bool valid{false};

        do {
            std::cout << "Input move: ";
            std::cin >> input_move;

            if (input_move == "export_history") {
                game.export_to_file();
                valid = true;
            } else {
                if (dreamchess::Game::is_move_syntax_correct(input_move)) {
                    valid = game.make_move(input_move);
                }
            }
        } while (!valid && (std::cout << "Invalid move! Retry!" << std::endl));
    }

    std::cout << "Game is over!" << std::endl;

    return 0;
}
