/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */

#include "Move.hpp"

#include "Board.hpp"

namespace DreamChess {
    /**
     * @brief Constructs a move with 'hard' source and destination
     * @param board The board where to make the move
     * @param source The source square
     * @param destination The destination square
     */
    Move::Move(uint64_t source, uint64_t destination, Piece::Enum piece)
        : m_source {static_cast<uint16_t>(source)}
        , m_destination {static_cast<uint16_t>(destination)} 
        , m_piece {piece} {}

    /**
     * @brief Source square getter
     * @return The source square
     */
    [[nodiscard]] uint16_t Move::source() const { return m_source; }

    /**
     * @brief Destination square getter
     * @return The destination square
     */
    [[nodiscard]] uint16_t Move::destination() const { return m_destination; }

    /**
     * @brief Gets the piece which is making the move
     * @return The piece which is making the move
     */
    [[nodiscard]] Piece::Enum Move::piece() const { return m_piece; }

    /**
     * @brief Returns the chosen promotion piece
     * @return The chosen promotion piece (QUEEN by default)
     */
    [[nodiscard]] Piece::Enum Move::promotion_piece() const {
        return m_promotion_piece;
    }

    /**
     * @brief Converts a Move to his its algebraic notation
     * @return The Move in algebraic notation
     */
    [[nodiscard]] std::string Move::to_alg() const {
        uint16_t rem = m_destination % 8;
        uint16_t quot = m_destination / 8;

        std::string res {};

        if(Piece::type(m_piece) != Piece::PAWN) {
            res.push_back(Piece::g_piece_repr.at(m_piece));
        }

        res.push_back(static_cast<char>('a' + rem));
        res.push_back(static_cast<char>('1' + quot));

        return res;
    }
} // namespace DreamChess