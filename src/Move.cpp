/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Board.hpp"
#include "Move.hpp"
#include "Piece.hpp"

#include <string_view>

namespace DreamChess {
    /**
     * @brief The `Move` constructor
     * @param board The board in which the move has been made
     * @param input Input string in "source-destination" format
     */
    Move::Move(const Board &board, std::string_view input) {
        uint16_t s_rank = input.at(0) - 'a';
        uint16_t s_file = input.at(1) - '1';

        uint16_t d_rank = input.at(3) - 'a';
        uint16_t d_file = input.at(4) - '1';

        m_source = s_rank * 8 + s_file;
        m_destination = d_rank * 8 + d_file;

        m_piece = board.get_piece_at(m_source);

        if(board.get_turn() && m_destination >= 0 && m_destination <= 7) {
            m_promotion_piece = WHITE_QUEEN;
        } else if(!board.get_turn() && m_destination >= 56 && m_destination <= 63) {
            m_promotion_piece = BLACK_QUEEN;
        }
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
        return m_piece == PAWN && (m_destination < 8 || m_destination > 55);
    }
}