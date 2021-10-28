/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */
#pragma once

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#include "Board.hpp"
#include "History.hpp"
#include "Piece.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {
// Move forward declaration
struct Move;

/**
 * @class Game
 * @brief Describes a chess Game, with a Board and a History
 */
class Game final {
public:
    /**
     * @fn Game()
     * @brief Creates a Game object
     */
    Game() = default;

    friend std::ostream &operator<<(std::ostream &, const Game &);

    /**
     * @fn Board board()
     * @breif The Board getter
     * @return The Board member of Game
     */
    [[nodiscard]] Board board() const;

    /**
     * @fn bool is_in_game()
     * @brief Checks if the game is still going on
     * @return true if a game is being played, false otherwise
     * @see Board::is_in_game()
     */
    [[nodiscard]] bool is_in_game() const;

    /**
     * @fn bool is_move_syntax_correct(const std::string &)
     * @brief Checks the input move syntactic correctness via regex
     * @param input_move The std::string to be checked
     * @return true if input_move respects the syntax, false otherwise
     * @see std::regex_match()
     */
    [[nodiscard]] static bool is_move_syntax_correct(const std::string &);

    /**
     * @fn bool make_move(std::string_view)
     * @brief Wraps Board::make_move and updates m_history
     * @param input The user input containing the move "source-destination"
     * @return True if the move is valid, False otherwise
     * @see Piece::type()
     * @see Piece::to_enum()
     * @see Board::move_is_valid()
     * @see Board::make_move()
     * @see update_history()
     */
    bool make_move(std::string_view);

    /**
     * @fn void export_to_file()
     * @brief Exports the Game's History to a file
     * @details Wraps History::export_to_file() method
     * @see std::filesystem::create_directory()
     * @see std::filesystem::permissions()
     * @see History::export_all()
     * @see std::ofstream::close()
     */
    void export_to_file() const;

    /**
     * @fn void reset()
     * @brief Resets the whole Board
     * @details First it whipe out every Piece in the Board, then it calls to
     * Board::init_board() to set each Piece in the original position
     * @see Board::clear()
     * @see Board::init_board()
     */
    void reset();

    /**
     * @fn piece_t piece_at(uint16_t)
     * @brief Wraps Board's piece_at method
     * @param index The square which you want to know the value
     * @return The Piece in the index square
     * @see Board::piece_at()
     */
    [[nodiscard]] Board::piece_t piece_at(uint16_t) const;

    /**
     * @brief Wraps Board's begin() method
     * @return A pointer to the first element of the Board
     * @see Board::begin()
     */
    [[nodiscard]] Board::piece_array_t::const_iterator begin() const;

    /**
     * @brief Wraps Board's end() method
     * @return A pointer to the last element of the Board
     * @see Board::end()
     */
    [[nodiscard]] Board::piece_array_t::const_iterator end() const;

private:
    /**
     * @brief The current game's Board
     */
    Board m_board = Board{};

    /**
     * @brief The current game's History
     */
    History m_history = History{};

    /**
     * @fn void update_history(const Move &)
     * @brief Updates the Game's history
     * @see History::add_step()
     */
    void update_history(const Move &);
};
}    // namespace dreamchess