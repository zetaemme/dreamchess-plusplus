/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Move.hpp"

#include "Board.hpp"

namespace DreamChess {

    /**
     * @brief "Constructs a move with 'hard' source and destination"
     * @param board The board where to make the move
     * @param source The source square
     * @param destination The destination square
     */
    Move::Move(const Board &board, uint64_t source, uint64_t destination)
        : m_source {static_cast<uint16_t>(source)}
        , m_destination {static_cast<uint16_t>(destination)} {
        if(is_valid()) {
            m_piece = board.get_piece_at(m_source);

            if(board.get_turn() && m_destination >= 0 && m_destination <= 7) {
                m_promotion_piece = Piece::WHITE_QUEEN;
            } else if(!board.get_turn() && m_destination >= 56
                      && m_destination <= 63) {
                m_promotion_piece = Piece::BLACK_QUEEN;
            }
        }
    }

    /**
     * @brief The `Move` constructor
     * @param board The board in which the move has been made
     * @param input Input string in "source-destination" format
     */
    Move::Move(const Board &board, std::string_view input) {
        uint16_t s_file = input.at(0) - 'a';
        uint16_t s_rank = input.at(1) - '1';

        uint16_t d_file = input.at(3) - 'a';
        uint16_t d_rank = input.at(4) - '1';

        m_source = s_rank * 8 + s_file;
        m_destination = d_rank * 8 + d_file;

        if(is_valid()) {
            m_piece = board.get_piece_at(m_source);

            if(board.get_turn() && m_destination >= 0 && m_destination <= 7) {
                m_promotion_piece = Piece::WHITE_QUEEN;
            } else if(!board.get_turn() && m_destination >= 56
                      && m_destination <= 63) {
                m_promotion_piece = Piece::BLACK_QUEEN;
            }
        }
    }

    /**
     * @brief "Source square getter"
     * @return The source square
     */
    [[nodiscard]] uint16_t Move::get_source() const { return m_source; }

    /**
     * @brief "Destination square getter"
     * @return The destination square
     */
    [[nodiscard]] uint16_t Move::get_destination() const {
        return m_destination;
    }

    /**
     * @brief "Gets the piece which is making the move"
     * @return The piece which is making the move
     */
    [[nodiscard]] Piece::Enum Move::get_piece() const { return m_piece; }

    /**
     * @brief "Returns the chosen promotion piece "
     * @return The chosen promotion piece (QUEEN by default)
     */
    [[nodiscard]] Piece::Enum Move::get_promotion_piece() const {
        return m_promotion_piece;
    }

    /**
     * @brief "Checks if the move is valid"
     * @details "A `Move` is valid if it's in the `Board` and actually moves the
     * `Piece`"
     */
    [[nodiscard]] bool Move::is_valid() const {
        return m_source >= 0 && m_source < 64 && m_destination >= 0
            && m_destination < 64 && m_source != m_destination;
    }

    /**
     * @brief "Checks if the move is a promotion move"
     * @details "A `Move` is promotion if it's made by a pawn and the
     * destination it's in the opposite player first file"
     */
    [[nodiscard]] bool Move::is_promotion() const {
        return m_piece == Piece::PAWN
            && (m_destination < 8 || m_destination > 55);
    }

    /**
     * @brief "Checks a Move possible horizontal squares"
     * @return The number of possible horizontal squares
     */
    [[nodiscard]] int64_t Move::horizontal_check() const {
        return std::abs(m_source % 8 - m_destination % 8);
    }

    /**
     * @brief "Checks a Move possible vertical squares"
     * @return The number of possible vertical squares
     */
    [[nodiscard]] int64_t Move::vertical_check() const {
        return std::abs(m_source / 8 - m_destination / 8);
    }
} // namespace DreamChess