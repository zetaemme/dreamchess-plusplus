/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#include "Game.hpp"

#include <iostream>

int
main() {
    // DreamChess::Game game {};

    // std::string input_move;

    /*while(game.is_in_game()) {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << game;
        std::cout << "---------------------------------------" << std::endl;

        bool valid_move;

        do {
            std::cout << "Input move: ";
            std::cin >> input_move;

            valid_move = game.make_move(input_move);
        } while(!valid_move
                && (std::cout << "Invalid move! Retry!" << std::endl));
    }*/

    DreamChess::Board board {};
    DreamChess::It board_it {board};

    for(auto it = board_it.begin(); it != board_it.end(); ++it) {
        std::cout << std::distance(board_it.begin(), it) << ":"
                  << DreamChess::Piece::g_piece_repr.at(*it) << std::endl;
    }

    return 0;
}
