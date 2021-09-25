/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Board.hpp"
#include "History.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

namespace DreamChess {
    // Move forward declaration
    class Move;

    /**
     * @brief Describes a chess Game, with a Board and a History
     */
    class Game final {
    public:
        Game();

        friend std::ostream &operator<<(std::ostream &, const Game &);

        [[nodiscard]] bool is_in_game() const;

        [[nodiscard]] bool make_move(std::string_view);
        void export_to_file() const;

        bool is_licence_valid();

    private:
        /**
         * @brief The current game's Board
         */
        Board m_board;

        /**
         * @brief The current game's History
         */
        History m_history;

        void update_history(const Move &);

        constexpr size_t generate_licence();

        template<size_t N>
        static constexpr size_t licence_hash(size_t prime, 
                                             const char (&str)[N], 
                                             size_t len = N - 1);
    };
} // namespace DreamChess