/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */

#include "Piece.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
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

Piece::Enum operator|(Piece::Enum lhs, Piece::Enum rhs) {
    return static_cast<Piece::Enum>(static_cast<uint16_t>(lhs) |
                                    static_cast<uint16_t>(rhs));
}

Piece::Enum operator&(Piece::Enum lhs, Piece::Enum rhs) {
    return static_cast<Piece::Enum>(static_cast<uint16_t>(lhs) &
                                    static_cast<uint16_t>(rhs));
}

Piece::Enum Piece::type(Piece::Enum target) {
    return (target & (PAWN | KNIGHT | BISHOP | ROOK | QUEEN | KING));
}

Piece::Enum Piece::color(Piece::Enum target) {
    return (target & (WHITE | BLACK));
}

Piece::Enum Piece::opposite_side_color(Piece::Enum target) {
    return color(target) == WHITE ? BLACK : WHITE;
}

std::string Piece::unicode_representation(Piece::Enum piece) {
    return m_piece_repr.at(piece);
}

Piece::Enum Piece::to_enum(char char_piece) {
    return m_fen_to_piece.at(char_piece);
}
}    // namespace dreamchess
