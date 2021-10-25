/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */

#include "Piece.hpp"

namespace dreamchess {
const Piece::char_to_enum_map_t Piece::m_fen_to_piece{
    {'p', BLACK_PAWN}, {'n', BLACK_KNIGHT}, {'b', BLACK_BISHOP},
    {'r', BLACK_ROOK}, {'q', BLACK_QUEEN},  {'k', BLACK_KING},
    {'P', WHITE_PAWN}, {'N', WHITE_KNIGHT}, {'B', WHITE_BISHOP},
    {'R', WHITE_ROOK}, {'Q', WHITE_QUEEN},  {'K', WHITE_KING}};

const Piece::enum_to_char_map_t Piece::m_piece_repr{
    {NONE, " "},         {WHITE_PAWN, "♙"}, {WHITE_KNIGHT, "♘"},
    {WHITE_BISHOP, "♗"}, {WHITE_ROOK, "♖"}, {WHITE_QUEEN, "♕"},
    {WHITE_KING, "♔"},   {BLACK_PAWN, "♟"}, {BLACK_KNIGHT, "♞"},
    {BLACK_BISHOP, "♝"}, {BLACK_ROOK, "♜"}, {BLACK_QUEEN, "♛"},
    {BLACK_KING, "♚"}};

/**
 * @brief Overloads the bitwise OR operator
 * @param lhs The first piece
 * @param rhs The second piece
 * @return The result of the ORed pieces values
 */
Piece::Enum operator|(Piece::Enum lhs, Piece::Enum rhs) {
    return static_cast<Piece::Enum>(static_cast<uint16_t>(lhs) |
                                    static_cast<uint16_t>(rhs));
}

/**
 * @brief Overloads the bitwise AND operator
 * @param lhs The first piece
 * @param rhs The second piece
 * @return The result of the ANDed pieces values
 */
Piece::Enum operator&(Piece::Enum lhs, Piece::Enum rhs) {
    return static_cast<Piece::Enum>(static_cast<uint16_t>(lhs) &
                                    static_cast<uint16_t>(rhs));
}

/**
 * @brief Calculates the given piece's type
 * @param target The piece which I want to know the type
 * @return The piece's type
 */
Piece::Enum Piece::type(Piece::Enum target) {
    return (target & (PAWN | KNIGHT | BISHOP | ROOK | QUEEN | KING));
}

/**
 * @brief Calculates the given piece's color
 * @param target The piece which I want to know the color
 * @return The piece's color
 */
Piece::Enum Piece::color(Piece::Enum target) {
    return (target & (WHITE | BLACK));
}

/**
 * @brief Calculates the target's opposite side color
 * @param target The piece which I want to know the opposite color
 * @return The opposite side's color
 */
Piece::Enum Piece::opposite_side_color(Piece::Enum target) {
    return color(target) == WHITE ? BLACK : WHITE;
}

/**
 * @brief Returns th unicode representation of a given Piece
 * @param piece The Piece which we want to represent
 * @return The unicode representation of the Piece
 */
std::string Piece::unicode_representation(Piece::Enum piece) {
    return m_piece_repr.at(piece);
}

/**
 * @brief Returns the Piece::Enum corresponding to the given Piece
 * @param char_piece The FEN char representation of a Piece
 * @return The FEN char of the Piece
 */
Piece::Enum Piece::to_enum(char char_piece) {
    return m_fen_to_piece.at(char_piece);
}
}    // namespace dreamchess
