#include "Game.hpp"

#include <gtest/gtest.h>

#include "Piece.hpp"

class GameTest : public ::testing::Test {
protected:
    DreamChess::Game game{};

    bool test_reset() {
        game.make_move("a2-a4");
        game.make_move("g8-f6");
        game.make_move("a1-a3");
        game.make_move("d7-d5");

        game.reset();

        if (game.piece_at(8) != DreamChess::Piece::WHITE_PAWN ||
            game.piece_at(62) != DreamChess::Piece::BLACK_KNIGHT ||
            game.piece_at(0) != DreamChess::Piece::WHITE_ROOK ||
            game.piece_at(55) != DreamChess::Piece::BLACK_PAWN) {
            return false;
        }

        return true;
    }
};

TEST_F(GameTest, GameStartsCorrectly) { ASSERT_EQ(game.is_in_game(), true); }

TEST_F(GameTest, GameResetsCorrectly) { ASSERT_EQ(test_reset(), true); }
