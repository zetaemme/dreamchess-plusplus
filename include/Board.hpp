/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Piece.hpp"

#include <array>
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>

namespace DreamChess {
    // Move forward declaration
    class Move;

    /**
     * @brief Defines a chess Game board
     */
    class Board final {
        using piece_t = Piece::Enum;
        using internal_structure_t = std::array<piece_t, 64>;

    public:
        Board();

        friend std::ostream &operator<<(std::ostream &, const Board &);

        void make_move(const Move &);

        [[nodiscard]] bool is_in_game() const;
        [[nodiscard]] bool is_in_check() const;

        [[nodiscard]] internal_structure_t squares() const;
        [[nodiscard]] piece_t turn() const;
        [[nodiscard]] piece_t opponent_turn() const;

        [[nodiscard]] piece_t piece_at(uint16_t) const;
        [[nodiscard]] bool square_attacked(uint64_t, piece_t) const;

        [[nodiscard]] internal_structure_t::const_iterator begin() const;
        [[nodiscard]] internal_structure_t::const_iterator end() const;

    private:

        /**
         * @brief false for BLACK's or true for WHITE's turn
         */
        piece_t m_turn {Piece::WHITE};

        /**
         * @brief Checks if the game is still going on
         */
        bool m_in_game {true};

        /**
         * @brief Array describing the board's state
         */
        internal_structure_t m_squares {};

        /**
         * @brief Keeps track of captured pieces
         */
        std::map<piece_t, uint16_t> m_captured {};

        void init_board();
    };
} // namespace DreamChess
