/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */

#include "Piece.hpp"

#include <map>

namespace DreamChess {
/**
 * @brief Overloads the bitwise OR operator
 * @param lhs The first piece
 * @param rhs The second piece
 * @return The result of the ORed pieces values
 */
Piece::Enum operator|(const Piece::Enum &lhs, const Piece::Enum &rhs) {
    return static_cast<Piece::Enum>(static_cast<uint16_t>(lhs) |
                                    static_cast<uint16_t>(rhs));
}

/**
 * @brief Overloads the bitwise AND operator
 * @param lhs The first piece
 * @param rhs The second piece
 * @return The result of the ANDed pieces values
 */
Piece::Enum operator&(const Piece::Enum &lhs, const Piece::Enum &rhs) {
    return static_cast<Piece::Enum>(static_cast<uint16_t>(lhs) &
                                    static_cast<uint16_t>(rhs));
}

/**
 * @brief Calculates the given piece's type
 * @param target The piece which I want to know the type
 * @return The piece's type
 */
Piece::Enum Piece::type(Piece::Enum target) {
    return static_cast<Enum>(target &
                             (PAWN | KNIGHT | BISHOP | ROOK | QUEEN | KING));
}

/**
 * @brief Calculates the given piece's color
 * @param target The piece which I want to know the color
 * @return The piece's color
 */
Piece::Enum Piece::color(Piece::Enum target) {
    return static_cast<Enum>(target & (WHITE | BLACK));
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
char Piece::unicode_representation(Piece::Enum piece) {
    const std::map<Enum, char> piece_repr{
        {NONE, ' '},         {WHITE_PAWN, 'P'}, {WHITE_KNIGHT, 'N'},
        {WHITE_BISHOP, 'B'}, {WHITE_ROOK, 'R'}, {WHITE_QUEEN, 'Q'},
        {WHITE_KING, 'K'},   {BLACK_PAWN, 'p'}, {BLACK_KNIGHT, 'n'},
        {BLACK_BISHOP, 'b'}, {BLACK_ROOK, 'r'}, {BLACK_QUEEN, 'q'},
        {BLACK_KING, 'k'}};

    return piece_repr.at(piece);
}

/**
 * @brief Returns the Piece::Enum representation of a given unicode Piece
 * @param unicode_piece The unicode represented Piece
 * @return The corresponding Piece::Enum
 */
Piece::Enum Piece::to_enum(char unicode_piece) {
    const std::map<char, Enum> fen_to_piece{
        {'p', BLACK_PAWN}, {'n', BLACK_KNIGHT}, {'b', BLACK_BISHOP},
        {'r', BLACK_ROOK}, {'q', BLACK_QUEEN},  {'k', BLACK_KING},
        {'P', WHITE_PAWN}, {'N', WHITE_KNIGHT}, {'B', WHITE_BISHOP},
        {'R', WHITE_ROOK}, {'Q', WHITE_QUEEN},  {'K', WHITE_KING},
    };

    return fen_to_piece.at(unicode_piece);
}
}    // namespace DreamChess
