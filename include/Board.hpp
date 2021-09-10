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
        using internal_structure_type = std::array<Piece::Enum, 64>;

    public:
        Board();

        friend std::ostream &operator<<(std::ostream &, const Board &);

        bool make_move(const Move &);

        [[nodiscard]] bool is_in_game() const;
        [[nodiscard]] Piece::Enum is_in_check() const;

        [[nodiscard]] internal_structure_type get_squares() const;
        [[nodiscard]] Piece::Enum get_turn() const;

        [[nodiscard]] Piece::Enum get_piece_at(uint16_t) const;
        [[nodiscard]] std::string to_fen() const;
        [[nodiscard]] Piece::Enum square_attacked(uint64_t) const;

        [[nodiscard]] internal_structure_type::const_iterator begin() const;
        [[nodiscard]] internal_structure_type::const_iterator end() const;
    private:

        /**
         * @brief false for BLACK's or true for WHITE's turn
         */
        Piece::Enum m_turn {Piece::WHITE};

        /**
         * @brief Counts the number of turns since the game started
         */
        uint64_t m_turn_counter = 1;

        /**
         * @brief Checks if the game is still going on
         */
        bool m_in_game = true;

        /**
         * @brief Array describing the board's state
         */
        internal_structure_type m_squares {};

        /**
         * @brief Keeps track of captured pieces
         */
        std::map<Piece::Enum, uint16_t> m_captured {};

        void init_board();
    };
} // namespace DreamChess
