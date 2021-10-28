/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */

#include "History.hpp"

#include <utility>

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {

History::~History() { m_game_history.clear(); }

void History::add_step(const Move &move) { m_game_history.emplace_back(move); }

[[nodiscard]] std::string History::export_all() const {
    step_list_t output_history = m_game_history;
    std::string move_list;

    for (const auto &step : m_game_history) {
        move_list += std::to_string((&step - &m_game_history.front()) + 1) +
                     ". " + std::string{output_history.front().m_move};
        move_list.push_back('\n');

        output_history.pop_front();
    }

    return move_list;
}

History::Step::Step(const Move &move) : m_move{move.to_alg()} {}
}    // namespace dreamchess
