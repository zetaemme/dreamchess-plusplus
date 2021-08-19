/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include <cstdint>
#include <map>
#include <utility>
#include <vector>

namespace DreamChess {
    /**
     * @brief "A single piece in the Board"
     */
    struct Piece final {
        /**
         * @brief "Represents every possible piece in the Board"
         */
        enum Enum : uint16_t {
            NONE = 0,
            PAWN = 1 << 0,
            KNIGHT = 1 << 1,
            BISHOP = 1 << 2,
            ROOK = 1 << 3,
            QUEEN = 1 << 4,
            KING = 1 << 5,
            WHITE = 1 << 6,
            BLACK = 1 << 7,

            WHITE_PAWN = PAWN | WHITE,
            BLACK_PAWN = PAWN | BLACK,
            WHITE_KNIGHT = KNIGHT | WHITE,
            BLACK_KNIGHT = KNIGHT | BLACK,
            WHITE_BISHOP = BISHOP | WHITE,
            BLACK_BISHOP = BISHOP | BLACK,
            WHITE_ROOK = ROOK | WHITE,
            BLACK_ROOK = ROOK | BLACK,
            WHITE_QUEEN = QUEEN | WHITE,
            BLACK_QUEEN = QUEEN | BLACK,
            WHITE_KING = KING | WHITE,
            BLACK_KING = KING | BLACK
        };

        /**
         * @brief "Used in Piece to char conversion, while printing the board"
         */
        static const std::map<Enum, uint8_t> g_piece_repr;

        /**
         * @brief "Convention for the FEN to Piece mapping"
         */
        static const std::map<uint8_t, Enum> g_fen_to_piece;

        /**
         * @brief "Logic NOT operator overloading"
         * @param piece The piece value to negate
         * @return The negated piece value
         */
        friend Enum operator~(Enum piece) {
            return static_cast<Enum>(~static_cast<uint16_t>(piece));
        }

        /**
         * @brief "OR operator overloading"
         * @param lhs The first piece
         * @param rhs The second piece
         * @return The result of the ORed pieces values
         */
        friend Enum operator|(Enum lhs, Enum rhs) {
            return static_cast<Enum>(static_cast<uint16_t>(lhs)
                                      | static_cast<uint16_t>(rhs));
        }

        /**
         * @brief "AND operator overloading"
         * @param lhs The first piece
         * @param rhs The second piece
         * @return The result of the ANDed pieces values
         */
        friend Enum operator&(Enum lhs, Enum rhs) {
            return static_cast<Enum>(static_cast<uint16_t>(lhs)
                                      & static_cast<uint16_t>(rhs));
        }

        /**
         * @brief "XOR operator overloading"
         * @param lhs The first piece
         * @param rhs The second piece
         * @return The result of the XORed pieces values
         */
        friend Enum operator^(Enum lhs, Enum rhs) {
            return static_cast<Enum>(static_cast<uint16_t>(lhs)
                                      ^ static_cast<uint16_t>(rhs));
        }

        static Enum get_type(Enum);
        static Enum get_color(Enum);
    };
} // namespace DreamChess