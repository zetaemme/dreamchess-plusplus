/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July, 2021
 */
#pragma once

#include "Board.hpp"
#include "History.hpp"

namespace DreamChess {
    class Game final {
    public:
        explicit Game();
        ~Game() = default;

        bool is_in_game() const;

    private:
        /**
         * @brief "The current game's board"
         */
        Board m_board;

        /**
         * @brief "The current game's history"
         */
        History m_history;

        void update_history(const Board &, const Board::Move &);
    };
} // namespace DreamChess