#include "Board.hpp"

#include <gtest/gtest.h>

#include "Move.hpp"

class BoardTest : public ::testing::Test {
protected:
    DreamChess::Board board{};

    [[nodiscard]] bool pawns_check() const {
        for (uint64_t i = 8; i < 16; i++) {
            if (board.squares()[i] != DreamChess::Piece::WHITE_PAWN) {
                return false;
            }
        }

        for (uint64_t i = 48; i < 56; i++) {
            if (board.squares()[i] != DreamChess::Piece::BLACK_PAWN) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool rooks_check() const {
        if (board.squares()[0] != DreamChess::Piece::WHITE_ROOK ||
            board.squares()[7] != DreamChess::Piece::WHITE_ROOK) {
            return false;
        }

        if (board.squares()[63] != DreamChess::Piece::BLACK_ROOK ||
            board.squares()[56] != DreamChess::Piece::BLACK_ROOK) {
            return false;
        }

        return true;
    }

    [[nodiscard]] bool knights_check() const {
        if (board.squares()[1] != DreamChess::Piece::WHITE_KNIGHT ||
            board.squares()[6] != DreamChess::Piece::WHITE_KNIGHT) {
            return false;
        }

        if (board.squares()[62] != DreamChess::Piece::BLACK_KNIGHT ||
            board.squares()[57] != DreamChess::Piece::BLACK_KNIGHT) {
            return false;
        }

        return true;
    }

    [[nodiscard]] bool bishop_check() const {
        if (board.squares()[2] != DreamChess::Piece::WHITE_BISHOP ||
            board.squares()[5] != DreamChess::Piece::WHITE_BISHOP) {
            return false;
        }

        if (board.squares()[61] != DreamChess::Piece::BLACK_BISHOP ||
            board.squares()[58] != DreamChess::Piece::BLACK_BISHOP) {
            return false;
        }

        return true;
    }

    [[nodiscard]] bool royals_check() const {
        if (board.squares()[3] != DreamChess::Piece::WHITE_QUEEN ||
            board.squares()[4] != DreamChess::Piece::WHITE_KING) {
            return false;
        }

        if (board.squares()[59] != DreamChess::Piece::BLACK_QUEEN ||
            board.squares()[60] != DreamChess::Piece::BLACK_KING) {
            return false;
        }

        return true;
    }
};

TEST_F(BoardTest, BoardCorrectCreation) {
    ASSERT_EQ(pawns_check(), true);
    ASSERT_EQ(rooks_check(), true);
    ASSERT_EQ(knights_check(), true);
    ASSERT_EQ(bishop_check(), true);
    ASSERT_EQ(royals_check(), true);
}
