#include <gtest/gtest.h>

#include "Board.hpp"

TEST(BoardTest, BoardCreation) {
    DreamChess:Board board {};

    // Pawns check
    for(uint64_t i = 8; i < 16; i++) {
        ASSERT_EQ(board.squares()[i], Piece::WHITE_PAWN);
    }

    for(uint64_t i = 48; i < 56; i++) {
        ASSERT_EQ(board.squares()[i], Piece::BLACK_PAWN);
    }

    // Rooks check
    ASSERT_EQ(board.squares()[0], Piece::WHITE_ROOK);
    ASSERT_EQ(board.squares()[7], Piece::WHITE_ROOK);

    ASSERT_EQ(board.squares()[63], Piece::BLACK_ROOK);
    ASSERT_EQ(board.squares()[56], Piece::BLACK_ROOK);

    // Knights check
    ASSERT_EQ(board.squares()[1], Piece::WHITE_KNIGHT);
    ASSERT_EQ(board.squares()[6], Piece::WHITE_KNIGHT);

    ASSERT_EQ(board.squares()[62], Piece::BLACK_KNIGHT);
    ASSERT_EQ(board.squares()[57], Piece::BLACK_KNIGHT);

    // Bishops check
    ASSERT_EQ(board.squares()[2], Piece::WHITE_BISHOP);
    ASSERT_EQ(board.squares()[5], Piece::WHITE_BISHOP);

    ASSERT_EQ(board.squares()[61], Piece::BLACK_BISHOP);
    ASSERT_EQ(board.squares()[58], Piece::BLACK_BISHOP);

    // Royals checks
    ASSERT_EQ(board.squares()[3], Piece::WHITE_QUEEN);
    ASSERT_EQ(board.squares()[4], Piece::WHITE_KING);

    ASSERT_EQ(board.squares()[59], Piece::WHITE_QUEEN);
    ASSERT_EQ(board.squares()[60], Piece::WHITE_KING);
}