/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Piece.hpp"

#include <string_view>

namespace DreamChess {
    class Board;

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

        [[nodiscard]] bool is_promotion() const;

        [[nodiscard]] int64_t horizontal_check() const;
        [[nodiscard]] int64_t vertical_check() const;

    private:
        /**
         * @brief "The move's source square"
         */
        uint16_t m_source;
        /**
         * @brief "The move's destination square"
         */
        uint16_t m_destination;

        /**
         * @brief "The piece which is making the move"
         */
        Piece::Enum m_piece;

        /**
         * @brief "The declared promotion present, if promotion"
         */
        Piece::Enum m_promotion_piece = Piece::NONE;
    };
}
