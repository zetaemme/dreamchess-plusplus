#include "Piece.hpp"

#include <gtest/gtest.h>

TEST(PieceTest, PiecesAreConvertedCorrectly) {
    ASSERT_EQ(
        DreamChess::Piece::unicode_representation(DreamChess::Piece::NONE),
        " ");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::WHITE_PAWN),
              "♙");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::WHITE_KNIGHT),
              "♘");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::WHITE_BISHOP),
              "♗");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::WHITE_ROOK),
              "♖");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::WHITE_QUEEN),
              "♕");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::WHITE_KING),
              "♔");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::BLACK_PAWN),
              "♟");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::BLACK_KNIGHT),
              "♞");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::BLACK_BISHOP),
              "♝");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::BLACK_ROOK),
              "♜");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::BLACK_QUEEN),
              "♛");
    ASSERT_EQ(DreamChess::Piece::unicode_representation(
                  DreamChess::Piece::BLACK_KING),
              "♚");
}