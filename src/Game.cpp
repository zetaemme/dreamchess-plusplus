/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Game.hpp"
#include "Move.hpp"

namespace DreamChess {
    /**
     * @brief Creates a Game object
     */
    Game::Game()
        : m_board(Board {})
        , m_history(History {}) {}

    /**
     * @brief Checks if the game is still going on
     * @return true if a game is being played, false otherwise
     */
    bool Game::is_in_game() const { return m_board.is_in_game(); }

    /**
     * @breif Wraps Board::make_move and updates m_history
     * @param input The user input containing the move "source-destination"
     * @return True if the move is valid, False otherwise
     */
    bool Game::make_move(std::string_view input) {
        Move new_move {m_board, input};

        if(m_board.make_move(new_move)) {
            update_history(new_move);
        } else {
            return false;
        }

        return true;
    }

    /**
     * @brief Overloads the out-stream operator for Game
     * @param stream The out-stream
     * @param game This game
     * @return The output stream
     */
    std::ostream &operator<<(std::ostream &stream, const Game &game) {
        stream << game.m_board;

        return stream;
    }

    /**
     * @brief Updates the Game's history
     */
    void Game::update_history(const Move &move) {
        m_history.add_step(m_board.to_fen(), move);
    }
} // namespace DreamChess
