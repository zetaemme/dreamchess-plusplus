/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */
#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <utility>

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {
/**
 * @struct Piece
 * @brief A single Piece in the Board
 */
struct Piece final {
    /**
     * @enum Enum
     * @brief Represents every possible Piece in the Board as Flag Enum
     * @details Each type is a value in [0,32], each color is a value in
     * [64,128]. Each type of Piece is obtained bu ORing color and type
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
     * @typedef Defines the enum_to_char_map_t type to improve readability
     */
    using enum_to_char_map_t = std::map<Enum, std::string>;

    /**
     * @typedef Defines the char_to_enum_map_t type to improve readability
     */
    using char_to_enum_map_t = std::map<char, Enum>;

    /**
     * @brief Maps a Piece::Enum representation of a Piece into the
     * corresponding unicode character
     */
    static const enum_to_char_map_t m_piece_repr;

    /**
     * @brief Maps a FEN notation Piece char representation into the
     * corresponding Piece::Enum value
     */
    static const char_to_enum_map_t m_fen_to_piece;

    /**
     * @brief Overloads the bitwise OR operator
     * @param lhs The first piece
     * @param rhs The second piece
     * @return The result of the ORed pieces values
     */
    friend Enum operator|(Enum, Enum);

    /**
     * @brief Overloads the bitwise AND operator
     * @param lhs The first piece
     * @param rhs The second piece
     * @return The result of the ANDed pieces values
     */
    friend Enum operator&(Enum, Enum);

    /**
     * @brief Calculates the given piece's type
     * @param target The piece which I want to know the type
     * @return The piece's type
     */
    static Enum type(Enum);

    /**
     * @brief Calculates the given piece's color
     * @param target The piece which I want to know the color
     * @return The piece's color
     */
    static Enum color(Enum);

    /**
     * @brief Calculates the target's opposite side color
     * @param target The piece which I want to know the opposite color
     * @return The opposite side's color
     * @see color()
     */
    static Enum opposite_side_color(Enum);

    /**
     * @brief Returns th unicode representation of a given Piece
     * @param piece The Piece which we want to represent
     * @return The unicode representation of the Piece
     */
    static std::string unicode_representation(Enum);

    /**
     * @brief Returns the Piece::Enum corresponding to the given Piece
     * @param char_piece The FEN char representation of a Piece
     * @return The FEN char of the Piece
     */
    static Enum to_enum(char);
};
}    // namespace dreamchess