/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

namespace DreamChess {
    class Move final {
        Move(const Board &, std::string_view);

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
        Piece m_piece;
        /**
         * @brief "The declared promotion present, if promotion"
         */
        Piece m_promotion_piece = NONE;

        [[nodiscard]] bool is_valid() const;

        [[nodiscard]] bool is_promotion() const;
    };
}
