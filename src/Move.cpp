/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */

#include "Move.hpp"

#include "Board.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {

const std::shared_ptr<std::regex> Move::m_move_regex{
    std::make_shared<std::regex>("[a-h][1-8]-[a-h][1-8]")};

const std::shared_ptr<std::regex> Move::m_promotion_regex{
    std::make_shared<std::regex>("[a-h][1-8]-[a-h][1-8]=[r|R|n|N|b|B|q|Q]")};

Move::Move(int64_t source, int64_t destination, Board::piece_t piece,
           Board::piece_t promotion_piece)
    : m_source{static_cast<int16_t>(source)},
      m_destination{static_cast<int16_t>(destination)},
      m_piece{piece},
      m_promotion_piece{promotion_piece} {}

[[nodiscard]] int16_t Move::source() const { return m_source; }

[[nodiscard]] int16_t Move::destination() const { return m_destination; }

[[nodiscard]] Board::piece_t Move::piece() const { return m_piece; }

[[nodiscard]] Board::piece_t Move::promotion_piece() const {
    return m_promotion_piece;
}

[[nodiscard]] std::regex Move::move_regex() { return *m_move_regex; }

[[nodiscard]] std::regex Move::promotion_regex() { return *m_promotion_regex; }

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
}    // namespace dreamchess