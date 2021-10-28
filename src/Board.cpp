/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */

#include "Board.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>

#include "Move.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {

Board::Board() { init_board(); }

Board::~Board() { m_captured.clear(); }

std::ostream &operator<<(std::ostream &stream, const Board &board) {
    for (uint64_t i = 0; i < 64; i++) {
        stream << Piece::unicode_representation(board.m_squares[i]) << " ";

        if ((i + 1) % 8 == 0) {
            stream << std::endl;
        }
    }

    return stream;
}

void Board::make_move(const Move &move) {
    // En-passant
    if (Piece::type(move.piece()) == Piece::PAWN &&
        (m_squares[move.destination()] == Piece::NONE &&
         move.source() % 8 != move.destination() % 8)) {
        uint16_t en_passant = move.destination() -
                              8 * (move.destination() > move.source() ? 1 : -1);
        m_captured[m_squares[en_passant]]++;
        m_squares[en_passant] = Piece::NONE;
    }

    // Updating captured pieces
    if (m_squares[move.destination()] != Piece::NONE) {
        m_captured[m_squares[move.destination()]]++;
    }

    // kingside castle
    if (Piece::type(move.piece()) == Piece::KING &&
        move.destination() - move.source() == 2) {
        m_squares[move.destination() - 1] = m_squares[move.destination() + 1];
        m_squares[move.destination() + 1] = Piece::NONE;
    }

    // Queenside castle
    if (Piece::type(move.piece()) == Piece::KING &&
        move.source() - move.destination() == 2) {
        m_squares[move.destination() + 1] = m_squares[move.destination() - 2];
        m_squares[move.destination() - 2] = Piece::NONE;
    }

    if (move_is_promotion(move)) {
        // Promotion
        m_squares[move.destination()] = move.promotion_piece();
    } else {
        // The actual "common" move
        m_squares[move.destination()] = m_squares[move.source()];
    }

    m_squares[move.source()] = Piece::NONE;

    m_turn = opponent_turn();
}

[[nodiscard]] bool Board::is_in_game() const { return is_king_dead(); }

[[nodiscard]] bool Board::is_in_check() const {
    for (uint64_t i = 0; i < 64; i++) {
        if (m_squares[i] == (Piece::KING | m_turn)) {
            return square_attacked(i, opponent_turn());
        }
    }

    return true;
}

[[nodiscard]] bool Board::is_king_dead() const {
    return std::any_of(begin(), end(), [this](const Piece::Enum &piece) {
        return Piece::type(piece) == Piece::KING &&
               Piece::color(piece) == m_turn;
    });
}

[[nodiscard]] Board::piece_array_t Board::squares() const { return m_squares; }

[[nodiscard]] Board::piece_t Board::turn() const { return m_turn; }

[[nodiscard]] Board::piece_t Board::opponent_turn() const {
    return m_turn == Piece::WHITE ? Piece::BLACK : Piece::WHITE;
}

[[nodiscard]] Board::piece_t Board::piece_at(uint16_t index) const {
    return m_squares[index];
}

[[nodiscard]] bool Board::square_attacked(uint64_t index,
                                          Board::piece_t turn) const {
    for (uint64_t i = 0; i < 64; i++) {
        if (Piece::color(m_squares[i]) == turn) {
            Move move{static_cast<int64_t>(i), static_cast<int64_t>(index),
                      m_squares[i], Piece::NONE};

            if (move_is_semi_valid(move)) {
                return true;
            }
        }
    }

    return false;
}

[[nodiscard]] bool Board::move_is_valid(const Move &move) const {
    if (!move_is_semi_valid(move)) {
        return false;
    }

    return !is_in_check();
}

[[nodiscard]] bool Board::move_is_semi_valid(const Move &move) const {
    if (move.source() > 63 || move.destination() > 63 ||
        move.source() == move.destination() ||
        m_squares[move.source()] == Piece::NONE ||
        Piece::color(m_squares[move.source()]) != m_turn ||
        Piece::color(m_squares[move.source()]) ==
            Piece::color(m_squares[move.destination()])) {
        return false;
    }

    int64_t hor = horizontal_check(move);
    int64_t ver = vertical_check(move);

    switch (Piece::type(m_squares[move.source()])) {
        case Piece::KNIGHT: {
            if (((hor != 1) && (hor != 2)) || ((hor == 1) && (ver != 2)) ||
                ((hor == 2) && (ver != 1))) {
                return false;
            }

            if (m_squares[move.destination()] == Piece::NONE) {
                break;
            }

            break;
        }

        case Piece::BISHOP: {
            if (hor != ver) {
                return false;
            }

            break;
        }

        case Piece::ROOK: {
            if ((hor != 0) && (ver != 0)) {
                return false;
            }

            break;
        }

        case Piece::QUEEN: {
            if ((hor != 0) && (ver != 0) && (hor != ver)) {
                return false;
            }

            break;
        }

        case Piece::PAWN: {
            if ((move.destination() > move.source()) &&
                (Piece::color(m_squares[move.source()]) == Piece::BLACK)) {
                return false;
            }

            if ((move.destination() < move.source()) &&
                (Piece::color(m_squares[move.source()]) == Piece::WHITE)) {
                return false;
            }

            if (hor > 1) {
                return false;
            }

            if (hor == 0) {
                if (ver > 2) {
                    return false;
                }
                if ((ver == 2) && !(static_cast<unsigned>(move.source() - 8) <=
                                        static_cast<unsigned>(15 - 8) ||
                                    static_cast<unsigned>(move.source() - 48) <=
                                        static_cast<unsigned>(55 - 48))) {
                    return false;
                }

                if (m_squares[move.destination()] != Piece::NONE) {
                    return false;
                }
            } else {
                if (ver != 1) {
                    return false;
                }

                if (m_squares[move.destination()] == Piece::NONE) {
                    if ((Piece::color(m_squares[move.source()]) ==
                         Piece::WHITE) &&
                        static_cast<unsigned>(move.source() - 32) >
                            static_cast<unsigned>(40 - 32)) {
                        return false;
                    }

                    if ((Piece::color(m_squares[move.source()]) ==
                         Piece::BLACK) &&
                        static_cast<unsigned>(move.source() - 24) >
                            static_cast<unsigned>(32 - 24)) {
                        return false;
                    }

                    const int16_t offset =
                        Piece::color(m_squares[move.source()]) == Piece::WHITE
                            ? -8
                            : 8;

                    if (m_squares[move.destination() + offset] !=
                        (Piece::PAWN | Piece::opposite_side_color(
                                           m_squares[move.source()]))) {
                        return false;
                    }
                }
            }

            break;
        }

        case Piece::KING: {
            if (hor > 2) {
                return false;
            } else if (hor == 2) {
                bool white =
                    Piece::color(m_squares[move.source()]) == Piece::WHITE;

                const int16_t step = move.destination() > move.source() ? 1
                                                                        : -1;

                uint16_t rook;

                if (step == 1) {
                    rook = white ? 7 : 63;
                } else {
                    rook = white ? 0 : 56;
                }

                if (ver != 0) {
                    return false;
                }

                if (move.source() != (white ? 4 : 60)) {
                    return false;
                }

                if (m_squares[rook] != (Piece::ROOK | m_turn)) {
                    return false;
                }

                int32_t i = move.source() + step;

                while (i != rook) {
                    if (m_squares[i] != Piece::NONE) {
                        return false;
                    }

                    i += step;
                }

                if (square_attacked(move.source(), opponent_turn())) {
                    return false;
                }

                if (square_attacked(move.source() + step, opponent_turn())) {
                    return false;
                }
            } else {
                if (ver > 1) {
                    return false;
                }
            }

            break;
        }

        default:
            return false;
    }

    return true;
}

[[nodiscard]] bool Board::move_is_promotion(const Move &move) const {
    return move.promotion_piece() != Piece::NONE;
}

[[nodiscard]] Board::piece_array_t::const_iterator Board::begin() const {
    return m_squares.begin();
}

[[nodiscard]] Board::piece_array_t::const_iterator Board::end() const {
    return m_squares.end();
}

void Board::init_board() {
    uint16_t file = 0;
    uint16_t rank = 7;

    std::array<std::string, 6> splitted_fen;
    std::stringstream stream{
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

    std::string tmp;

    for (uint64_t i = 0; i < 6; i++) {
        std::getline(stream, tmp, ' ');
        splitted_fen[i] = tmp;
    }

    for (const auto &sym : splitted_fen[0]) {
        if (sym == '/') {
            file = 0;
            rank--;
        } else {
            if (isdigit(sym)) {
                file += sym - '0';
            } else {
                m_squares[rank * 8 + file] = Piece::to_enum(sym);
                file++;
            }
        }
    }
}

void Board::clear() { m_squares.fill(Piece::NONE); }

[[nodiscard]] int64_t Board::horizontal_check(const Move &move) const {
    return std::abs(move.source() % 8 - move.destination() % 8);
}

[[nodiscard]] int64_t Board::vertical_check(const Move &move) const {
    return std::abs(move.source() / 8 - move.destination() / 8);
}
}    // namespace dreamchess
