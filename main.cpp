/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */
#include <iostream>
#include <regex>
#include <string>

#include "Game.hpp"

int main() {
    DreamChess::Game game{};

    std::string input_move;

    std::regex move_regex{"[a-h][1-8]-[a-h][1-8]"};
    std::regex promotion_regex{"[a-h][1-8]-[a-h][1-8]=[r|R|n|N|b|B|q|Q]"};

    while (game.is_in_game()) {
        std::cout << "---------------------" << std::endl;
        std::cout << game;
        std::cout << "---------------------" << std::endl;

        bool valid;

        do {
            std::cout << "Input move: ";
            std::cin >> input_move;

            std::smatch match;

            if (input_move == "export_history") {
                game.export_to_file();
                valid = true;
            } else {
                // Checks if the input_move is properly formatted
                if (std::regex_match(input_move, match, move_regex) ||
                    std::regex_match(input_move, match, promotion_regex)) {
                    valid = game.make_move(input_move);
                } else {
                    valid = false;
                }
            }
        } while (!valid && (std::cout << "Invalid move! Retry!" << std::endl));
    }

    std::cout << "Game is over!" << std::endl;

    return 0;
}
