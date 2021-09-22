/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Board.hpp"
#include "Piece.hpp"

#include <string_view>

namespace DreamChess {
    /**
     * @brief A single move in the Game
     */
    class Move final {
        using piece_t = Piece::Enum;

    public:
        Move(const Board &, uint64_t, uint64_t);
        Move(const Board &, std::string_view);

        [[nodiscard]] uint16_t source() const;
        [[nodiscard]] uint16_t destination() const;
        [[nodiscard]] piece_t piece() const;
        [[nodiscard]] piece_t promotion_piece() const;

        [[nodiscard]] bool is_valid() const;
        [[nodiscard]] bool is_semi_valid() const;
        [[nodiscard]] bool is_promotion() const;

        [[nodiscard]] int64_t horizontal_check() const;
        [[nodiscard]] int64_t vertical_check() const;
        [[nodiscard]] bool diagonal_check(int64_t) const;

        [[nodiscard]] std::string to_alg() const;

    private:
        /**
         * @brief The Board where the Move has been made
         */
        Board m_board;

        /**
         * @brief The Move's source square
         */
        uint16_t m_source;

        /**
         * @brief The Move's destination square
         */
        uint16_t m_destination;

        /**
         * @brief The Piece which is making the move
         */
        piece_t m_piece;

        /**
         * @brief The declared promotion present, if promotion
         */
        piece_t m_promotion_piece {Piece::NONE};
    };
} // namespace DreamChess
