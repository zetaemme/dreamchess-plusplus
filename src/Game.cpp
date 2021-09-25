/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Game.hpp"

#include "Move.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace DreamChess {
    /**
     * @brief Creates a Game object
     */
    Game::Game()
        : m_board(Board {})
        , m_history(History {}) {}

    /**
     * @brief Overloads the out-stream operator for Game
     * @details Wraps the Board::operator<< to print the Board
     * @param stream The out-stream
     * @param game This game
     * @return The output stream
     */
    std::ostream &operator<<(std::ostream &stream, const Game &game) {
        stream << game.m_board;

        return stream;
    }

    /**
     * @brief Checks if the game is still going on
     * @return true if a game is being played, false otherwise
     */
    bool Game::is_in_game() const { return m_board.is_in_game(); }

    /**
     * @brief Wraps Board::make_move and updates m_history
     * @param input The user input containing the move "source-destination"
     * @return True if the move is valid, False otherwise
     */
    bool Game::make_move(std::string_view input) {
        Move new_move {m_board, input};

        if(!new_move.is_valid()) { return false; }

        m_board.make_move(new_move);
        update_history(new_move);

        return true;
    }

    /**
     * @brief Exports the Game's Hisotry to a file
     * @details Wraps History::export_to_file() method
     */
    void Game::export_to_file() const {
        if(!std::filesystem::create_directory("../history")) {
            std::cerr << "Failed to create the \'history\' dir!";
        }

        std::ofstream history_file {"../history/game_history.txt"};

        std::filesystem::permissions("../history/game_history.txt",
                                     std::filesystem::perms::owner_write
                                         | std::filesystem::perms::group_write
                                         | std::filesystem::perms::others_write,
                                     std::filesystem::perm_options::add);

        history_file << m_history.export_all();

        history_file.close();
    }

    // TODO Usare hash nel modo corretto
    /**
     * @brief Checks if the 'game_licence.txt' file is a valid licence
     * @return true if the licence is valid, false otherwise
     */
    bool Game::is_licence_valid() {
        std::ifstream licence_file;

        licence_file.open("../game_licence.txt");

        if(licence_file.is_open()) {
            std::string game_licence;

            licence_file >> game_licence;

            return licence_hash(31, game_licence) == generate_licence();
        }

        return false;
    }

    /**
     * @brief Updates the Game's history
     */
    void Game::update_history(const Move &move) { m_history.add_step(move); }

    /**
     * @brief Generates the "licence" value
     * @details This shouldn't exist, added in order to introduce a compile
     * time feature to the project
     * @return The hashed Game licence
     */
    constexpr uint64_t Game::generate_licence() {
        return licence_hash(31, "dreamchess");
    }

    /**
     * @brief A compile time hash function
     * @param prime A prime number
     * @param str A cheracter from the string str
     * @param len The remaining chars to be hashed
     */
    template<size_t N>
    static constexpr size_t licence_hash(size_t prime, 
                                         const char (&str)[N], 
                                         size_t len = N - 1) {
        return len <= 1 
            ? str[0] 
            : (prime * licence_hash(prime, str, len - 1) + str[len - 1]);
    }
} // namespace DreamChess
