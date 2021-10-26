#include "Game.hpp"

#include <gtest/gtest.h>

#include <filesystem>

#include "Piece.hpp"

class GameTest : public ::testing::Test {
protected:
    dreamchess::Game game{};

    [[nodiscard]] bool test_reset() {
        game.make_move("a2-a4");
        game.make_move("g8-f6");
        game.make_move("a1-a3");
        game.make_move("d7-d5");

        game.reset();

        if (game.piece_at(8) != dreamchess::Piece::WHITE_PAWN ||
            game.piece_at(62) != dreamchess::Piece::BLACK_KNIGHT ||
            game.piece_at(0) != dreamchess::Piece::WHITE_ROOK ||
            game.piece_at(55) != dreamchess::Piece::BLACK_PAWN) {
            return false;
        }

        return true;
    }
    [[nodiscard]] bool test_games_end() {
        game.make_move("e2-a4");
        game.make_move("b7-b6");
        game.make_move("e1-e2");
        game.make_move("c8-a6");
        game.make_move("a6-e2");

        return game.board().is_king_dead();
    }
    [[nodiscard]] bool is_history_exported() {
        game.make_move("a2-a4");
        game.make_move("c8-d6");

        game.export_to_file();

        game.reset();

        return std::filesystem::exists("../history/game_history.txt") &&
               std::filesystem::remove_all("../history");
    }

    [[nodiscard]] bool only_correct_knight_moves() {
        game.make_move("b1-c3");
        game.make_move("a7-a6");
        game.make_move("b2-b4");
        game.make_move("b7-b6");
        game.make_move("b4-b5");
        game.make_move("c7-c6");

        return game.make_move("c3-b5");
    }

    [[nodiscard]] bool en_passant_check() {
        game.make_move("a2-a4");
        game.make_move("h7-h6");
        game.make_move("b2-b4");
        game.make_move("g7-g6");
        game.make_move("b4-b5");
        game.make_move("a7-a5");
        game.make_move("b5-a6");

        return game.piece_at(32) == dreamchess::Piece::NONE;
    }
    [[nodiscard]] bool queen_promotion_check() {
        game.make_move("d2-d4");
        game.make_move("c7-c5");
        game.make_move("a2-a3");
        game.make_move("c5-d4");
        game.make_move("d2-d4");
        game.make_move("d1-d3");
        game.make_move("h7-h6");
        game.make_move("d3-h3");
        game.make_move("d4-d3");
        game.make_move("a3-a4");
        game.make_move("d3-d2");
        game.make_move("a4-a5");
        game.make_move("d2-d4");
        game.make_move("d2-d1");

        return game.piece_at(3) == dreamchess::Piece::BLACK_QUEEN;
    }
    [[nodiscard]] bool rook_promotion_check() {
        game.make_move("d2-d4");
        game.make_move("c7-c5");
        game.make_move("a2-a3");
        game.make_move("c5-d4");
        game.make_move("d2-d4");
        game.make_move("d1-d3");
        game.make_move("h7-h6");
        game.make_move("d3-h3");
        game.make_move("d4-d3");
        game.make_move("a3-a4");
        game.make_move("d3-d2");
        game.make_move("a4-a5");
        game.make_move("d2-d4");
        game.make_move("d2-d1=r");

        return game.piece_at(3) == dreamchess::Piece::BLACK_ROOK;
    }
    [[nodiscard]] bool knight_promotion_check() {
        game.make_move("d2-d4");
        game.make_move("c7-c5");
        game.make_move("a2-a3");
        game.make_move("c5-d4");
        game.make_move("d2-d4");
        game.make_move("d1-d3");
        game.make_move("h7-h6");
        game.make_move("d3-h3");
        game.make_move("d4-d3");
        game.make_move("a3-a4");
        game.make_move("d3-d2");
        game.make_move("a4-a5");
        game.make_move("d2-d4");
        game.make_move("d2-d1=n");

        return game.piece_at(3) == dreamchess::Piece::BLACK_KNIGHT;
    }
    [[nodiscard]] bool bishop_promotion_check() {
        game.make_move("d2-d4");
        game.make_move("c7-c5");
        game.make_move("a2-a3");
        game.make_move("c5-d4");
        game.make_move("d2-d4");
        game.make_move("d1-d3");
        game.make_move("h7-h6");
        game.make_move("d3-h3");
        game.make_move("d4-d3");
        game.make_move("a3-a4");
        game.make_move("d3-d2");
        game.make_move("a4-a5");
        game.make_move("d2-d4");
        game.make_move("d2-d1=b");

        return game.piece_at(3) == dreamchess::Piece::BLACK_BISHOP;
    }
    [[nodiscard]] bool queen_side_castle_check() {
        game.make_move("b1-a3");
        game.make_move("a7-a6");
        game.make_move("d2-d4");
        game.make_move("b7-b6");
        game.make_move("c1-e3");
        game.make_move("c7-c6");
        game.make_move("d1-d3");
        game.make_move("d7-d6");
        game.make_move("e1-c1");

        return game.piece_at(2) == dreamchess::Piece::WHITE_KING;
    }
    [[nodiscard]] bool king_side_castle_check() {
        game.make_move("g1-h3");
        game.make_move("a7-a6");
        game.make_move("e2-e4");
        game.make_move("b7-b6");
        game.make_move("f1-d3");
        game.make_move("c7-c6");
        game.make_move("e1-g1");

        return game.piece_at(6) == dreamchess::Piece::WHITE_KING;
    }

    [[nodiscard]] bool terminal_output_check() const {
        std::stringstream out;

        out << game;

        std::string game_str;

        for (uint64_t i = 0; i < 64; i++) {
            game_str.append(
                dreamchess::Piece::unicode_representation(game.piece_at(i)));
            game_str.append(" ");

            if ((i + 1) % 8 == 0) {
                game_str.push_back('\n');
            }
        }

        return out.str() == game_str;
    }
};

TEST_F(GameTest, GameStartsCorrectly) { ASSERT_TRUE(game.is_in_game()); }

TEST_F(GameTest, GameEndsCorrectly) {
    ASSERT_TRUE(test_games_end());
    game.reset();
}

TEST_F(GameTest, GameResetsCorrectly) { ASSERT_TRUE(test_reset()); }

TEST_F(GameTest, HistoryIsExported) { ASSERT_TRUE(is_history_exported()); }

TEST_F(GameTest, OnlyCorrectPawnMovesAreMade) {
    ASSERT_FALSE(game.make_move("a2-a1"));
    ASSERT_FALSE(game.make_move("a2-a2"));
    ASSERT_FALSE(game.make_move("a2-a6"));
    ASSERT_FALSE(game.make_move("a2-b3"));
    ASSERT_FALSE(game.make_move("a2-a4") && game.make_move("b7-b6") &&
                 game.make_move("a4-a3"));
    game.reset();
}

TEST_F(GameTest, OnlyCorrectRookMovesAreMade) {
    ASSERT_FALSE(game.make_move("a1-a2"));
    ASSERT_FALSE(game.make_move("b2-b4") && game.make_move("b7-b6") &&
                 game.make_move("a1-c3"));
    game.reset();
}

TEST_F(GameTest, OnlyCorrectKnightMovesAreMade) {
    ASSERT_FALSE(only_correct_knight_moves());
    game.reset();
}

TEST_F(GameTest, OnlyCorrectBishopMovesAreMade) {
    ASSERT_FALSE(game.make_move("c1-d2"));
    ASSERT_FALSE(game.make_move("b2-b4") && game.make_move("h7-h6") &&
                 game.make_move("c1-a3") && game.make_move("g7-g6") &&
                 game.make_move("a3-a4"));
    game.reset();
}

TEST_F(GameTest, OnlyCorrectQueenMovesAreMade) {
    ASSERT_FALSE(game.make_move("d1-d2"));
    ASSERT_FALSE(game.make_move("d2-d4") && game.make_move("h7-h6") &&
                 game.make_move("d1-d3") && game.make_move("g7-g6") &&
                 game.make_move("d2-b3"));
    game.reset();
}

TEST_F(GameTest, OnlyCorrectKingMovesAreMade) {
    ASSERT_FALSE(game.make_move("e1-e2"));
    ASSERT_FALSE(game.make_move("e2-e4") && game.make_move("h7-h6") &&
                 game.make_move("e1-e3"));
    game.reset();
}

TEST_F(GameTest, EnPassantMoveIsCorrect) {
    ASSERT_TRUE(en_passant_check());
    game.reset();
}

TEST_F(GameTest, QueenPromotionIsMade) {
    ASSERT_TRUE(queen_promotion_check());
    game.reset();
}

TEST_F(GameTest, RookPromotionIsMade) {
    ASSERT_TRUE(rook_promotion_check());
    game.reset();
}

TEST_F(GameTest, KnightPromotionIsMade) {
    ASSERT_TRUE(knight_promotion_check());
    game.reset();
}

TEST_F(GameTest, BishopPromotionIsMade) {
    ASSERT_TRUE(bishop_promotion_check());
    game.reset();
}

TEST_F(GameTest, QueensideCastleIsCorrect) {
    ASSERT_TRUE(queen_side_castle_check());
    game.reset();
}

TEST_F(GameTest, KingsideCastleIsCorrect) {
    ASSERT_TRUE(king_side_castle_check());
    game.reset();
}

TEST_F(GameTest, BoardIsPrintedCorrectly) {
    ASSERT_TRUE(terminal_output_check());
}