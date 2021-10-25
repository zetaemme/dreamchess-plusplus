#include "Piece.hpp"

#include <gtest/gtest.h>

TEST(PieceTest, PiecesAreConvertedCorrectly) {
    ASSERT_EQ(
        dreamchess::Piece::unicode_representation(dreamchess::Piece::NONE),
        " ");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::WHITE_PAWN),
              "♙");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::WHITE_KNIGHT),
              "♘");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::WHITE_BISHOP),
              "♗");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::WHITE_ROOK),
              "♖");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::WHITE_QUEEN),
              "♕");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::WHITE_KING),
              "♔");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::BLACK_PAWN),
              "♟");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::BLACK_KNIGHT),
              "♞");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::BLACK_BISHOP),
              "♝");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::BLACK_ROOK),
              "♜");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::BLACK_QUEEN),
              "♛");
    ASSERT_EQ(dreamchess::Piece::unicode_representation(
                  dreamchess::Piece::BLACK_KING),
              "♚");
}