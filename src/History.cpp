/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "History.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

namespace DreamChess {
    /**
     * @brief Constructs the History
     * @details History can be seen as a list of Steps
     */
    History::History() {}

    /**
     * @brief Wraps the std::vector::const_iterator begin() method to use it as 
     * Board ConstIterator
     * @return The pointer to the first Move of the game
     */
    [[nodiscard]] std::list<History::Step>::const_iterator History::begin() const {
        return m_game_history.begin();
    }

    /**
     * @brief Wraps the std::vector::const_iterator end() method to use it as 
     * Board ConstIterator
     * @return The pointer to the last Move which has been made
     */
    [[nodiscard]] std::list<History::Step>::const_iterator History::end() const {
        return m_game_history.end();
    }

    /**
     * @brief Adds a step to the History list
     * @param move The last move made in the referenced board
     */
    void History::add_step(const Move &move) {
        m_game_history.push_back(Step {move});
    }

    /**
     * @brief Exports History to a file 
     */
    constexpr void History::export_to_file(std::string_view game_id) {
        std::filesystem::current_path(std::filesystem::temp_directory_path());

        if(!std::filesystem::create_directory("../history")) {
            std::cerr << "Failed to create the \'history\' dir!";
        }

        std::ofstream history_file {"../history/game_history.txt"};
    }

    /**
     * @brief Constructs the Step
     * @details Each Step is the algebraic notation representation of the Move
     */
    History::Step::Step(const Move &move)
        : m_move {move.to_alg()} {}
} // namespace DreamChess
