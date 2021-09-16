/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "History.hpp"

#include <utility>

namespace DreamChess {
    /**
     * @brief Constructs the History
     * @details History can be seen as a list of Steps
     */
    History::History()
        : m_game_history {std::make_unique<std::list<Step>>()} {}

    /**
     * @brief Adds a step to the History list
     * @param board_fen The Step's view of the board
     * @param move The last move made in the referenced board
     */
    void History::add_step(std::string_view board_fen,
                                        const Move &move) {
        m_game_history->push_back(Step {board_fen, move});
    }

    /**
     * @brief Constructs the Step
     * @details Each Step is a view of the board and the move which brought
     * us here
     */
    History::Step::Step(const std::string_view board_fen, Move move)
        : m_board_fen {board_fen}
        , m_move {std::move(move)} {}
} // namespace DreamChess
