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
    public:
        Move(const Board &, uint64_t, uint64_t);
        Move(const Board &, std::string_view);

        [[nodiscard]] uint16_t get_source() const;
        [[nodiscard]] uint16_t get_destination() const;
        [[nodiscard]] Piece::Enum get_piece() const;
        [[nodiscard]] Piece::Enum get_promotion_piece() const;

        [[nodiscard]] bool is_valid() const;
        [[nodiscard]] bool is_semi_valid() const;
        [[nodiscard]] bool is_promotion() const;
        [[nodiscard]] bool is_capture() const;

        [[nodiscard]] int64_t horizontal_check() const;
        [[nodiscard]] int64_t vertical_check() const;
        [[nodiscard]] bool diagonal_check(int64_t) const;

    private:
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
        Piece::Enum m_piece;

        /**
         * @brief The declared promotion present, if promotion
         */
        Piece::Enum m_promotion_piece = Piece::NONE;

        /**
         * @brief True if the move is a capture, false otherwise
         */
        bool m_is_capture = false;
    };
} // namespace DreamChess
