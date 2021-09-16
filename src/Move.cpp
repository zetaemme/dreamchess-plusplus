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
     * @brief Constructs a move with 'hard' source and destination
     * @param board The board where to make the move
     * @param source The source square
     * @param destination The destination square
     */
    Move::Move(const Board &board, uint64_t source, uint64_t destination)
        : m_board {board}
        , m_source {static_cast<uint16_t>(source)}
        , m_destination {static_cast<uint16_t>(destination)} {
        if(is_valid()) {
            m_piece = board.piece_at(m_source);

            if(board.turn() && m_destination >= 0 && m_destination <= 7) {
                m_promotion_piece = Piece::WHITE_QUEEN;
            } else if(!board.turn() && m_destination >= 56
                      && m_destination <= 63) {
                m_promotion_piece = Piece::BLACK_QUEEN;
            }
        }
    }

    /**
     * @brief The Move constructor
     * @param board The board in which the move has been made
     * @param input Input string in "source-destination" format
     */
    Move::Move(const Board &board, std::string_view input)
        : m_board {board} {
        uint16_t s_file = input.at(0) - 'a';
        uint16_t s_rank = input.at(1) - '1';

        uint16_t d_file = input.at(3) - 'a';
        uint16_t d_rank = input.at(4) - '1';

        m_source = s_rank * 8 + s_file;
        m_destination = d_rank * 8 + d_file;

        if(is_valid()) {
            m_piece = board.piece_at(m_source);

            if(board.turn() && m_destination >= 0 && m_destination <= 7) {
                m_promotion_piece = Piece::WHITE_QUEEN;
            } else if(!board.turn() && m_destination >= 56
                      && m_destination <= 63) {
                m_promotion_piece = Piece::BLACK_QUEEN;
            }
        }
    }

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
     * @brief Checks if the move is valid
     * @details "A Move is valid if it's in the Board and actually moves the
     * Piece
     */
    [[nodiscard]] bool Move::is_valid() const {
        if(!is_semi_valid()) { return false; }

        return !m_board.is_in_check();
    }

    // FIXME Non permette doppio avanzamento del pedone in prima mossa, fixare
    /**
     * @brief Checks if a move is semi_valid
     * @param move The move to check
     * @return True if the move is semi_valid, False otherwise
     */
    [[nodiscard]] bool Move::is_semi_valid() const {
        const auto &squares = m_board.squares();

        if(m_source > 63 || m_source < 0 || m_destination > 63
           || m_destination < 0 || m_source == m_destination
           || squares[m_source] == Piece::NONE
           || Piece::color(squares[m_source]) != m_board.turn()) {
            return false;
        }

        int64_t hor = horizontal_check();
        int64_t ver = vertical_check();
        bool diag = diagonal_check(ver);

        switch(Piece::type(squares[m_source])) {
            case Piece::KNIGHT: {
                if((hor != 1 && hor != 2) || (hor == 1 && ver != 2)
                   || (hor == 2 && ver != 1)) {
                    return false;
                }

                if(squares[m_destination] == Piece::NONE) { break; }

                if(Piece::color(squares[m_destination])
                   == Piece::color(squares[m_source])) {
                    return false;
                }

                break;
            }

            case Piece::BISHOP: {
                if(hor != ver || !diag) { return false; }

                break;
            }

            case Piece::ROOK: {
                if((hor != 0 && ver != 0) || !diag) { return false; }

                break;
            }

            case Piece::QUEEN: {
                if((hor != 0 && ver != 0 && hor != ver) || !diag) {
                    return false;
                }

                break;
            }

            case Piece::PAWN: {
                if(m_destination > m_source
                   && Piece::color(squares[m_source]) == Piece::BLACK) {
                    return false;
                }

                if(m_destination < m_source
                   && Piece::color(squares[m_source]) == Piece::WHITE) {
                    return false;
                }

                if(hor > 1) { return false; }

                if(hor == 0) {
                    if(ver > 2) { return false; }

                    if(ver == 2) {
                        if(!(((m_source >= 8) && (m_source <= 15))
                             || ((m_source >= 48) && (m_source <= 55)))) {
                            return false;
                        }

                        if(!diag || squares[m_destination] != Piece::NONE) {
                            return false;
                        }
                    }
                } else {
                    if(ver != 1 || !diag) { return false; }

                    if(squares[m_destination] == Piece::NONE) {
                        if(Piece::color(squares[m_source]) == Piece::WHITE
                           && !(m_source >= 32 && m_source < 40)) {
                            return false;
                        }

                        if(Piece::color(squares[m_source]) == Piece::BLACK
                           && !(m_source >= 24 && m_source < 32)) {
                            return false;
                        }

                        uint16_t offset
                            = Piece::color(squares[m_source]) == Piece::WHITE
                                ? -8
                                : 8;

                        if(squares[m_destination + offset]
                           != (Piece::PAWN
                               | Piece::opposite_side_color(
                                   squares[m_source]))) {
                            return false;
                        }
                    }
                }

                break;
            }

            case Piece::KING: {
                if(hor > 2) {
                    return false;
                } else if(hor == 2) {
                    bool white
                        = Piece::color(squares[m_source]) == Piece::WHITE;

                    uint16_t step = m_destination > m_source ? 1 : -1;

                    uint16_t rook
                        = step == 1 ? (white ? 7 : 63) : (white ? 0 : 63);

                    if(ver != 0) { return false; }

                    if(m_source != (white ? 4 : 60)) { return false; }

                    if(squares[rook] != (Piece::ROOK | m_board.turn())) {
                        return false;
                    }

                    uint16_t i = m_source + step;

                    while(i != rook) {
                        if(squares[i] != Piece::NONE) { return false; }

                        i += step;
                    }

                    if(m_board.square_attacked(m_source,
                                               m_board.opponent_turn())) {
                        return false;
                    }

                    if(m_board.square_attacked(m_source + step,
                                               m_board.opponent_turn())) {
                        return false;
                    }
                } else {
                    if(ver > 1 || !diag) { return false; }
                }

                break;
            }

            default:
                return false;
        }

        return true;
    }

    /**
     * @brief Checks if the move is a promotion move
     * @details A Move is promotion if it's made by a pawn and the
     * destination it's in the opposite player first file
     */
    [[nodiscard]] bool Move::is_promotion() const {
        return m_piece == Piece::PAWN
            && (m_destination < 8 || m_destination >= 56);
    }

    /**
     * @brief Checks a Move possible horizontal squares
     * @return The number of possible horizontal squares
     */
    [[nodiscard]] int64_t Move::horizontal_check() const {
        return std::abs(m_source % 8 - m_destination % 8);
    }

    /**
     * @brief Checks a Move possible vertical squares
     * @return The number of possible vertical squares
     */
    [[nodiscard]] int64_t Move::vertical_check() const {
        return std::abs(m_source / 8 - m_destination / 8);
    }

    /**
     * @brief Checks if the diagonals of the given move are free
     * @param move The move to check
     * @param ver The possible vertical values from the move source square
     * @return True if the diagonals are free, False otherwise
     */
    [[nodiscard]] bool Move::diagonal_check(int64_t ver) const {
        uint16_t step;
        const auto &squares = m_board.squares();

        if(ver != 0) {
            step = (m_destination - m_source) / ver;
        } else {
            step = m_destination > m_source ? 1 : -1;
        }

        uint16_t i = m_source + step;

        while(i != m_destination) {
            if(squares[i] != Piece::NONE) { return false; }

            i += step;
        }

        if(squares[i] != Piece::NONE) { return false; }

        if(Piece::color(squares[i]) != Piece::color(squares[m_source])) {
            return false;
        }

        return true;
    }
} // namespace DreamChess