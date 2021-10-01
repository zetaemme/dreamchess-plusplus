#include <gtest/gtest.h>

#include "Game.hpp"

#include <filesystem>
#include <fstream>

class GameTest : public ::testing::Test {
protected:
    DreamChess::Game game {};

    bool test_game(std::string_view filename) {
        std::ofstream game_file {std::data(filename)};

        return true;
    }
};

TEST_F(GameTest, GameStartsCorrectly) {
    ASSERT_EQ(game.is_in_game(), true);
}

TEST_F(GameTest, GameRunsCorrectly) {
    ASSERT_EQ(test_game(""), true);
}
