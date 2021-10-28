/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */
#pragma once

#include <regex>
#include <string_view>

#include "Board.hpp"
#include "Piece.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {
/**
 * @struct Move
 * @brief A single move in the Game
 */
struct Move final {
public:
    /**
     * @fn Move(int64_t, int64_t, Board::piece_t, Board::piece_t)
     * @brief Constructs a move with 'hard' source and destination
     * @param source The source square
     * @param destination The destination square
     * @param piece The Piece which is making the Move
     * @param promotion_piece The chosen promotion Piece (if promotion move)
     */
    Move(int64_t, int64_t, Board::piece_t, Board::piece_t);

    /**
     * @fn int16_t source()
     * @brief Source square getter
     * @return The source square
     */
    [[nodiscard]] int16_t source() const;

    /**
     * @fn uint16_t destination()
     * @brief Destination square getter
     * @return The destination square
     */
    [[nodiscard]] int16_t destination() const;

    /**
     * @fn piece_t piece()
     * @brief Gets the piece which is making the move
     * @return The piece which is making the move
     */
    [[nodiscard]] Board::piece_t piece() const;

    /**
     * @fn piece_t promotion_piece()
     * @brief Returns the chosen promotion piece
     * @return The chosen promotion piece (A Queen by default)
     */
    [[nodiscard]] Board::piece_t promotion_piece() const;

    /**
     * @fn std::regex move_regex()
     * @brief Getter for the move regex
     * @return The object pointed by the m_move_regex shared pointer
     */
    [[nodiscard]] static std::regex move_regex();

    /**
     * @fn std::regex promotion_regex()
     * @brief Getter for the promotion regex
     * @return The object pointed by the m_promotion_regex shared pointer
     */
    [[nodiscard]] static std::regex promotion_regex();

    /**
     * @fn std::string to_alg()
     * @brief Converts a Move to his its algebraic notation
     * @return The Move in algebraic notation
     * @see Piece::unicode_representation()
     * @see std::string::push_back()
     */
    [[nodiscard]] std::string to_alg() const;

private:
    /**
     * @brief The Move's source square
     */
    int16_t m_source;

    /**
     * @brief The Move's destination square
     */
    int16_t m_destination;

    /**
     * @brief The Piece which is making the move
     */
    Board::piece_t m_piece;

    /**
     * @brief The declared promotion present, if promotion
     */
    Board::piece_t m_promotion_piece;

    /**
     * @brief Pointer to the standard move regex pattern
     */
    static const std::shared_ptr<std::regex> m_move_regex;

    /**
     * @brief Pointer to the promotion move regex pattern
     */
    static const std::shared_ptr<std::regex> m_promotion_regex;
};
}    // namespace dreamchess
