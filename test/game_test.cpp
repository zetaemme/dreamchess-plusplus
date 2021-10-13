#include "Game.hpp"

#include <gtest/gtest.h>

#include <filesystem>

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

    bool is_history_exported() {
        game.make_move("a2-a4");
        game.make_move("c8-d6");

        game.export_to_file();

        game.reset();

        return std::filesystem::exists("../history/game_history.txt") &&
               std::filesystem::remove_all("../history");
        ;
    }
};

TEST_F(GameTest, GameStartsCorrectly) { ASSERT_TRUE(game.is_in_game()); }

TEST_F(GameTest, GameResetsCorrectly) { ASSERT_TRUE(test_reset()); }

TEST_F(GameTest, HisotryIsExported) { ASSERT_TRUE(is_history_exported()); }
