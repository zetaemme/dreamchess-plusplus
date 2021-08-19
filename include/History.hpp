/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Board.hpp"
#include "Move.hpp"

#include <list>
#include <memory>
#include <string_view>


namespace DreamChess {
    /**
     * @brief "The current game History"
     */
    class History final {
    private:
        /**
         * @brief "A single step into the History"
         */
        struct Step final {
            Step(std::string_view, const Move &);

            /**
             * @brief "The board as it can be seen at this step"
             */
            std::string_view m_board_fen;

            /**
             * @brief "Last move which has been made"
             */
            const Move m_move;
        };

        /**
         * @brief "Game history so far"
         */
        std::unique_ptr<std::list<Step>> m_game_history;

    public:
        History();

        Step first();
        Step last();

        void add_step(std::string_view, const Move &);
    };
} // namespace DreamChess
