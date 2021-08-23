/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Board.hpp"
#include "History.hpp"

namespace DreamChess {
    class Move;

    class Game final {
    public:
        Game();

        [[nodiscard]] bool is_in_game() const;
        [[nodiscard]] bool make_move(std::string_view);

        friend std::ostream &operator<<(std::ostream &, const Game &);

    private:
        /**
         * @brief "The current game's board"
         */
        Board m_board;

        /**
         * @brief "The current game's history"
         */
        History m_history;

        void update_history(const Move &);
    };
} // namespace DreamChess