/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#include "../include/Game.hpp"

#include <iostream>

int main() {
    DreamChess::Game game {};

    std::string input_move;

    while(game.is_in_game()) {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << game;
        std::cout << "---------------------------------------" << std::endl;

        std::cout << "Input move:";
        std::cin >> input_move;
    }

    return 0;
}
