/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "../include/Game.hpp"

namespace DreamChess {
    /**
     * @brief "Creates a `Game` object"
     */
    Game::Game()
        : m_board(Board {})
        , m_history(History {}) {}

    /**
     * @brief "Checks if the game is still going on"
     * @return true if a game is being played, false otherwise
     */
    bool Game::is_in_game() const {
        return m_board.is_in_game();
    }

    std::ostream &operator<<(std::ostream &stream, const Game &game) {
        stream << game.m_board;

        return stream;
    }

    /**
     * @brief "Updates the `Game`'s history"
     */
    void Game::update_history(const Board &board, const Board::Move &move) {
        m_history.add_step(board.to_fen(), move);
    }
} // namespace DreamChess
