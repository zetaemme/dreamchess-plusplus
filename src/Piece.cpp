/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Piece.hpp"

namespace DreamChess {
    const std::map<Piece::Enum, uint8_t> Piece::g_piece_repr
        = {{Piece::NONE, ' '},         {Piece::WHITE_PAWN, 'P'},
           {Piece::WHITE_KNIGHT, 'N'}, {Piece::WHITE_BISHOP, 'B'},
           {Piece::WHITE_ROOK, 'R'},   {Piece::WHITE_QUEEN, 'Q'},
           {Piece::WHITE_KING, 'K'},   {Piece::BLACK_PAWN, 'p'},
           {Piece::BLACK_KNIGHT, 'n'}, {Piece::BLACK_BISHOP, 'b'},
           {Piece::BLACK_ROOK, 'r'},   {Piece::BLACK_QUEEN, 'q'},
           {Piece::BLACK_KING, 'k'}};

    const std::map<uint8_t, Piece::Enum> Piece::g_fen_to_piece = {
        {'p', Piece::BLACK_PAWN},   {'n', Piece::BLACK_KNIGHT},
        {'b', Piece::BLACK_BISHOP}, {'r', Piece::BLACK_ROOK},
        {'q', Piece::BLACK_QUEEN},  {'k', Piece::BLACK_KING},
        {'P', Piece::WHITE_PAWN},   {'N', Piece::WHITE_KNIGHT},
        {'B', Piece::WHITE_BISHOP}, {'R', Piece::WHITE_ROOK},
        {'Q', Piece::WHITE_QUEEN},  {'K', Piece::WHITE_KING},
    };

    /**
     * @brief Calculates the given piece's type
     * @param target The piece which I want to know the type
     * @return The piece's type
     */
    Piece::Enum Piece::get_type(Enum target) {
        return static_cast<Enum>(target & (~BLACK | ~WHITE));
    };

    /**
     * @brief Calculates the given piece's color
     * @param target The piece which I want to know the color
     * @return The piece's color
     */
    Piece::Enum Piece::get_color(Enum target) {
        return static_cast<Enum>(
            target & (~PAWN | ~KNIGHT | ~BISHOP | ~ROOK | ~QUEEN | ~KING));
    }

    /**
     * @brief Calculates the target's opposite side color
     * @param target The piece which I want to know the opposite color
     * @return The opposite side's color
     */
    Piece::Enum Piece::opposite_side_color(Enum target) {
        return get_color(target) == WHITE ? BLACK : WHITE;
    }
} // namespace DreamChess
