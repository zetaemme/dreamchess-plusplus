/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */
#pragma once

#include <array>
#include <cstdint>
#include <iterator>
#include <map>
#include <string>
#include <vector>

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
 * @class Board
 * @brief Defines a chess Game board
 */
class Board final {
public:
    /**
     * @typedef Defines the piece_t type to improve readability
     */
    using piece_t = Piece::Enum;

    /**
     * @typedef Defines the piece_array_t type to improve readability
     */
    using piece_array_t = std::array<piece_t, 64>;

    /**
     * @fn Board()
     * @brief Constructs a Board
     * @details Starts with the neutral FEN string, using init_board()
     * @see init_board()
     */
    Board();

    /**
     * @fn ~Board()
     * @breif Board's class destructor
     * @details Clears the captures std::map
     * @see std::map::clear()
     */
    ~Board();

    /**
     * @brief Overloads the out-stream operator for the Board
     * @details Print each piece and ends line every 8 files
     * @param stream The new output stream
     * @param board The printed board
     * @return The output stream
     */
    friend std::ostream &operator<<(std::ostream &, const Board &);

    /**
     * @fn void make_move(const Move &)
     * @brief Makes a move in the current Board
     * @details Checks if the `Move` is a "special move", makes a "normal move
     * otherwise
     * @param move The Move to make
     * @see Piece::type
     */
    void make_move(const Move &);

    /**
     * @fn bool is_in_game()
     * @brief Checks if the Game is still in progress
     * @details A Game is in progress if neither one of the players is in check
     * and mated
     * @return true if the Game is in progress, false otherwise
     * @see king_is_dead()
     */
    [[nodiscard]] bool is_in_game() const;

    /**
     * @fn bool is_in_check()
     * @brief Checks if one of the two sides is under check
     * @return The side who's in check
     * @see square_attacked()
     */
    [[nodiscard]] bool is_in_check() const;

    /**
     * @fn bool is_king_dead()
     * @brief Checks if the current's turn KING is still alive
     * @return true if the KING is alive, false otherwise
     * @see std::any_of()
     * @see Piece::color
     * @see Piece::type
     */
    [[nodiscard]] bool is_king_dead() const;

    /**
     * @fn piece_array_t squares()
     * @brief Returns the squares array of Board
     * @return The m_squares array
     */
    [[nodiscard]] piece_array_t squares() const;

    /**
     * @fn piece_t turn()
     * @brief Returns who plays in current turn
     * @return True if it's WHITE, false otherwise
     */
    [[nodiscard]] piece_t turn() const;

    /**
     * @fn piece_t opponent_turn()
     * @brief Gets the next turn moving color
     * @return The opposite of m_turn
     */
    [[nodiscard]] piece_t opponent_turn() const;

    /**
     * @fn piece_t piece_at(uint16_t)
     * @brief Returns the piece corresponding to index
     * @param index The index of the returned piece
     * @return The corresponding piece
     */
    [[nodiscard]] piece_t piece_at(uint16_t) const;

    /**
     * @fn bool square_attacked(uint64_t, piece_t)
     * @brief Checks if a given square is attached by another piece
     * @param index The index number of the square
     * @param turn The playing turn
     * @return The color of the piece which is attacked
     * @see Piece::color()
     * @see move_is_semi_valid()
     */
    [[nodiscard]] bool square_attacked(uint64_t, piece_t) const;

    /**
     * @fn bool move_is_valid(const Move &)
     * @brief Checks if the move is valid
     * @details "A Move is valid if it's in the Board and actually moves the
     * Piece
     * @param move The Move to check
     * @return True if there's no check on the board, false otherwise
     * @see move_is_semi_valid()
     * @see is_in_check()
     */
    [[nodiscard]] bool move_is_valid(const Move &) const;

    /**
     * @fn bool move_is_semi_valid(const Move &)
     * @brief Checks if a move is semi_valid
     * @param move The move to check
     * @return True if the move is semi-valid, False otherwise
     * @see Piece::color()
     * @see Piece::type
     * @see horizontal_check()
     * @see vertical_check()
     * @see Piece::type()
     */
    [[nodiscard]] bool move_is_semi_valid(const Move &) const;

    /**
     * @fn bool move_is_promotion(const Move &)
     * @brief Checks if the given Move is a promotion move
     * @details A Move is promotion if it's made by a pawn and the
     * destination it's in the opposite player first file
     * @param move The Move to check
     * @return True if the Move is a promotion move, false otherwise
     */
    [[nodiscard]] bool move_is_promotion(const Move &) const;

    /**
     * @fn piece_array_t::const_iterator begin()
     * @brief Wraps the std::array::iterator begin() method to use it as Board
     * ConstIterator
     * @return The pointer to the first square's address
     */
    [[nodiscard]] piece_array_t::const_iterator begin() const;

    /**
     * @fn piece_array_t::const_iterator end()
     * @brief Wraps the std::array::iterator end() method to use it as Board
     * ConstIterator
     * @return The pointer to the last square's address
     */
    [[nodiscard]] piece_array_t::const_iterator end() const;

private:
    /**
     * @brief false for BLACK's or true for WHITE's turn
     */
    piece_t m_turn{Piece::WHITE};

    /**
     * @brief Array describing the board's state
     */
    piece_array_t m_squares{};

    /**
     * @brief Keeps track of captured pieces
     */
    std::map<piece_t, uint16_t> m_captured{};

    /**
     * @fn void init_board()
     * @brief Used to init the board with the neutral FEN configuration
     * @details Parses the FEN string and inits the Board
     * @see Piece::to_enum()
     */
    void init_board();

    /**
     * @fn void clear()
     * @brief Clears all Board's squares
     * @see std::array::fill()
     */
    void clear();

    /**
     * @fn int64_t horizontal_check(const Move &)
     * @brief Checks the number of horizontal squares a Move is making
     * @param move The Move to check
     * @return The number of horizontal squares
     * @see std::abs()
     */
    [[nodiscard]] int64_t horizontal_check(const Move &) const;

    /**
     * @fn int64_t vertical_check(const Move &)
     * @brief Checks the number of vertical squares a Move is making
     * @param move The Move to check
     * @return The number of vertical squares
     * @see std::abs()
     */
    [[nodiscard]] int64_t vertical_check(const Move &) const;

    friend class Game;
};
}    // namespace dreamchess
