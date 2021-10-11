/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */
#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace DreamChess {
/**
 * @brief A single Piece in the Board
 */
struct Piece final {
    /**
     * @brief Represents every possible Piece in the Board as Flag Enum
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

    friend Enum operator|(Enum, Enum);
    friend Enum operator&(Enum, Enum);

    static Enum type(Enum);
    static Enum color(Enum);

    static Enum opposite_side_color(Enum);

    static std::string char_representation(Enum);

    static Enum to_enum(char);
};
}    // namespace DreamChess