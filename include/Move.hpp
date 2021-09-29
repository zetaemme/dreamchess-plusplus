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
    struct Move final {
        using piece_t = Piece::Enum;

    public:
        Move(uint64_t, uint64_t, piece_t);

        [[nodiscard]] uint16_t source() const;
        [[nodiscard]] uint16_t destination() const;
        [[nodiscard]] piece_t piece() const;
        [[nodiscard]] piece_t promotion_piece() const;

        [[nodiscard]] std::string to_alg() const;

    private:
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
