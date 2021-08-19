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
     * @brief "Describes every piece in the board"
     * @details "Each piece is ORed with the color to code its value"
     */
    enum Piece : uint16_t {
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
    const std::map<Piece, uint8_t> g_piece_repr {
        {NONE, ' '},         {WHITE_PAWN, 'P'}, {WHITE_KNIGHT, 'N'},
        {WHITE_BISHOP, 'B'}, {WHITE_ROOK, 'R'}, {WHITE_QUEEN, 'Q'},
        {WHITE_KING, 'K'},   {BLACK_PAWN, 'p'}, {BLACK_KNIGHT, 'n'},
        {BLACK_BISHOP, 'b'}, {BLACK_ROOK, 'r'}, {BLACK_QUEEN, 'q'},
        {BLACK_KING, 'k'}};

    /**
     * @brief "Convention for the FEN to DreamChess::Piece mapping"
     */
    const std::map<uint8_t, Piece> g_fen_to_piece {
        {'p', BLACK_PAWN}, {'n', BLACK_KNIGHT}, {'b', BLACK_BISHOP},
        {'r', BLACK_ROOK}, {'q', BLACK_QUEEN},  {'k', BLACK_KING},
        {'P', WHITE_PAWN}, {'N', WHITE_KNIGHT}, {'B', WHITE_BISHOP},
        {'R', WHITE_ROOK}, {'Q', WHITE_QUEEN},  {'K', WHITE_KING},
    };
} // namespace DreamChess