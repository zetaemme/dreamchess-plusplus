/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */

#include "Move.hpp"

#include "Board.hpp"

namespace DreamChess {
using piece_t = Piece::Enum;

const std::shared_ptr<std::regex> Move::m_move_regex{
    std::make_shared<std::regex>("[a-h][1-8]-[a-h][1-8]")};

const std::shared_ptr<std::regex> Move::m_promotion_regex{
    std::make_shared<std::regex>("[a-h][1-8]-[a-h][1-8]=[r|R|n|N|b|B|q|Q]")};

/**
 * @brief Constructs a move with 'hard' source and destination
 * @param board The board where to make the move
 * @param source The source square
 * @param destination The destination square
 */
Move::Move(int64_t source, int64_t destination, Board::piece_t piece,
           Board::piece_t promotion_piece)
    : m_source{static_cast<int16_t>(source)},
      m_destination{static_cast<int16_t>(destination)},
      m_piece{piece},
      m_promotion_piece{promotion_piece} {}

/**
 * @brief Source square getter
 * @return The source square
 */
[[nodiscard]] int16_t Move::source() const { return m_source; }

/**
 * @brief Destination square getter
 * @return The destination square
 */
[[nodiscard]] int16_t Move::destination() const { return m_destination; }

/**
 * @brief Gets the piece which is making the move
 * @return The piece which is making the move
 */
[[nodiscard]] piece_t Move::piece() const { return m_piece; }

/**
 * @brief Returns the chosen promotion piece
 * @return The chosen promotion piece (QUEEN by default)
 */
[[nodiscard]] piece_t Move::promotion_piece() const {
    return m_promotion_piece;
}

/**
 * @brief Getter for the move regex
 * @return The object pointed by the m_move_regex shared pointer
 */
[[nodiscard]] std::regex Move::move_regex() { return *m_move_regex; }

/**
 * @brief Getter for the promotion regex
 * @return The object pointed by the m_promotion_regex shared pointer
 */
[[nodiscard]] std::regex Move::promotion_regex() { return *m_promotion_regex; }

/**
 * @brief Converts a Move to his its algebraic notation
 * @return The Move in algebraic notation
 */
[[nodiscard]] std::string Move::to_alg() const {
    uint16_t rem = m_destination % 8;
    uint16_t quot = m_destination / 8;

    std::string res{};

    if (Piece::type(m_piece) != Piece::PAWN) {
        res.append(Piece::unicode_representation(m_piece));
    }

    res.push_back(static_cast<char>('a' + rem));
    res.push_back(static_cast<char>('1' + quot));

    return res;
}
}    // namespace DreamChess