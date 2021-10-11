/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */

#include "History.hpp"

#include <utility>

namespace DreamChess {
/**
 * @brief Clears the History
 */
History::~History() { m_game_history.clear(); }

/**
 * @brief Adds a step to the History list
 * @param move The last move made in the referenced board
 */
void History::add_step(const Move &move) {
    m_game_history.push_back(Step{move});
}

/**
 * @brief Exports the History as a string
 * @details Every Step is exported as <Move number>. <Move in algebraic>
 */
[[nodiscard]] std::string History::export_all() const {
    auto output_history = m_game_history;
    std::string move_list;

    for (uint64_t i = 0; i < m_game_history.size(); i++) {
        move_list += std::to_string(i + 1) + ". " +
                     std::string{output_history.front().m_move};
        move_list.push_back('\n');

        output_history.pop_front();
    }

    return move_list;
}

/**
 * @brief Wraps the std::list::const_iterator begin() method to use it as
 * Board ConstIterator
 * @return The pointer to the first Move of the game
 */
[[nodiscard]] std::list<History::Step>::const_iterator History::begin() const {
    return m_game_history.begin();
}

/**
 * @brief Wraps the std::list::const_iterator end() method to use it as
 * Board ConstIterator
 * @return The pointer to the last Move which has been made
 */
[[nodiscard]] std::list<History::Step>::const_iterator History::end() const {
    return m_game_history.end();
}

/**
 * @brief Constructs the Step
 * @details Each Step is the algebraic notation representation of the Move
 */
History::Step::Step(const Move &move) : m_move{move.to_alg()} {}
}    // namespace DreamChess
