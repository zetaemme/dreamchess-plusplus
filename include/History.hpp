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
     * @brief The current game History
     */
    class History final {
    private:
        /**
         * @brief A single step into the History
         */
        struct Step final {
            Step(const Move &);

            /**
             * @brief Last move which has been made
             */
            const std::string_view m_move;
        };

        using internal_structure_t = std::list<Step>;

        /**
         * @brief Game history so far
         */
        internal_structure_t m_game_history {};

        [[nodiscard]] internal_structure_t::const_iterator begin() const;
        [[nodiscard]] internal_structure_t::const_iterator end() const;

    public:
        History();

        void add_step(const Move &);

        static constexpr void export_to_file();
    };
} // namespace DreamChess
