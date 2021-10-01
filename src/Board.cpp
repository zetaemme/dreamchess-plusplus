/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Board.hpp"

#include "Move.hpp"

#include <array>
#include <iostream>
#include <sstream>

namespace DreamChess {
    using piece_t = Piece::Enum;
    using internal_structure_t = std::array<piece_t, 64>;

    /**
     * @brief Constructs a Board
     * @details Starts with the neutral FEN string, using init_board()
     */
    Board::Board() { init_board(); }

    /**
     * @brief Overloads the out-stream operator for the Board
     * @details Print each piece and ends line every 8 files
     * @param stream The new output stream
     * @param board The printed board
     * @return The output stream
     */
    std::ostream &operator<<(std::ostream &stream, const Board &board) {
        uint16_t i = 0;

        for(auto &square : board) {
            stream << Piece::g_piece_repr.at(square);

            if((i + 1) % 8 == 0) { stream << std::endl; }

            i++;
        }

        return stream;
    }

    /**
     * @brief Makes a move in the current Board
     * @details Checks if the `Move` is a "special move", makes a "normal move
     * otherwise
     * @param move The Move to make
     */
    void Board::make_move(const Move &move) {
        // En-passant
        if(Piece::type(move.piece()) == Piece::PAWN
           && (m_squares[move.destination()] == Piece::NONE
               && move.source() % 8 != move.destination() % 8)) {
            uint16_t en_passant
                = move.destination()
                - 8 * (move.destination() > move.source() ? 1 : -1);
            m_captured[m_squares[en_passant]]++;
            m_squares[en_passant] = Piece::NONE;
        }

        // Updating captured pieces
        if(m_squares[move.destination()] != Piece::NONE) {
            m_captured[m_squares[move.destination()]]++;
        }

        // kingside castle
        if(Piece::type(move.piece()) == Piece::KING
           && move.destination() - move.source() == 2) {
            m_squares[move.destination() - 1]
                = m_squares[move.destination() + 1];
            m_squares[move.destination() + 1] = Piece::NONE;
        }

        // Queenside castle
        if(Piece::type(move.piece()) == Piece::KING
           && move.source() - move.destination() == 2) {
            m_squares[move.destination() + 1]
                = m_squares[move.destination() - 2];
            m_squares[move.destination() - 2] = Piece::NONE;
        }

        if(move_is_promotion(move)) {
            // Promotion
            m_squares[move.destination()] = move.promotion_piece();
        } else {
            // The actual "common" move
            m_squares[move.destination()] = m_squares[move.source()];
        }

        m_squares[move.source()] = Piece::NONE;

        m_turn = opponent_turn();
    }

    /**
     * @brief Checks if the Game is still in progress
     * @details A Game is in progress if neither one of the players is in check
     * and mated
     * @return true if the Game is in progress, false otherwise
     */
    [[nodiscard]] bool Board::is_in_game() const {
        if(is_in_check() && is_mated()) {
            return false;
        }

        return true; 
    }

    /**
     * @brief Checks if one of the two sides is under check
     * @return The side who's in check
     */
    [[nodiscard]] bool Board::is_in_check() const {
        for(auto &square : *this) {
            if(square == (Piece::KING | m_turn)) {
                return square_attacked(&square - &m_squares[0],
                                       opponent_turn());
            }
        }

        return true;
    }

    /**
     * @brief Checks if a Piece is mated in this Board
     * @return true if a Piece is mated, false otherwise
     */
    [[nodiscard]] bool Board::is_mated() const {
        for(auto &square1 : m_squares) {
            if(Piece::color(square1) == m_turn) {
                for(auto &square2 : m_squares) {
                    Move move {static_cast<uint64_t>(&square1 - &m_squares[0]),
                               static_cast<uint64_t>(&square2 - &m_squares[0]),
                               square1};

                    if(move_is_valid(move)) { return true; }
                }
            }
        }

        return false;
    }

    /**
     * @brief Returns the squares array of Board
     * @return The m_squares array
     */
    [[nodiscard]] internal_structure_t Board::squares() const {
        return m_squares;
    }

    /**
     * @brief Returns who plays in current turn
     * @return True if it's WHITE, false otherwise
     */
    [[nodiscard]] piece_t Board::turn() const { return m_turn; }

    /**
     * @brief Gets the next turn moving color
     * @return The opposite of m_turn
     */
    [[nodiscard]] piece_t Board::opponent_turn() const {
        return m_turn == Piece::WHITE ? Piece::BLACK : Piece::WHITE;
    }

    /**
     * @brief Returns the piece corresponding to index
     * @param index The index of the returned piece
     * @return The corresponding piece
     */
    [[nodiscard]] piece_t Board::piece_at(uint16_t index) const {
        return m_squares[index];
    }

    /**
     * @brief Checks if a given square is attached by another piece
     * @param index The index of the square
     * @param turn The playing turn
     * @return The color of the piece which is attacked
     */
    [[nodiscard]] bool Board::square_attacked(uint64_t index,
                                              piece_t turn) const {
        for(auto &square : m_squares) {
            if(Piece::color(square) == turn) {
                Move move {static_cast<uint64_t>(&square - &m_squares[0]),
                           index, square};

                if(move_is_semi_valid(move)) { return true; }
            }
        }

        return false;
    }

    /**
     * @brief Checks if the move is valid
     * @details "A Move is valid if it's in the Board and actually moves the
     * Piece
     */
    [[nodiscard]] bool Board::move_is_valid(const Move &move) const {
        if(!move_is_semi_valid(move)) { return false; }

        return !is_in_check();
    }

    /**
     * @brief Checks if a move is semi_valid
     * @param move The move to check
     * @return True if the move is semi_valid, False otherwise
     */
    [[nodiscard]] bool Board::move_is_semi_valid(const Move &move) const {
        if(move.source() > 63 || move.destination() > 63
           || move.source() == move.destination()
           || m_squares[move.source()] == Piece::NONE
           || Piece::color(m_squares[move.source()]) != m_turn) {
            return false;
        }

        int64_t hor = horizontal_check(move);
        int64_t ver = vertical_check(move);
        bool diag = diagonal_check(ver, move);

        switch(Piece::type(m_squares[move.source()])) {
            case Piece::KNIGHT: {
                if(((hor != 1) && (hor != 2)) || ((hor == 1) && (ver != 2))
                   || ((hor == 2) && (ver != 1))) {
                    return false;
                }

                if(m_squares[move.destination()] == Piece::NONE) { break; }

                if(Piece::color(m_squares[move.destination()])
                   == Piece::color(m_squares[move.source()])) {
                    return false;
                }

                break;
            }

            case Piece::BISHOP: {
                if((hor != ver) || !diag) { return false; }

                break;
            }

            case Piece::ROOK: {
                if(((hor != 0) && (ver != 0)) || !diag) { return false; }

                break;
            }

            case Piece::QUEEN: {
                if(((hor != 0) && (ver != 0) && (hor != ver)) || !diag) {
                    return false;
                }

                break;
            }

            case Piece::PAWN: {
                if((move.destination() > move.source())
                   && (Piece::color(m_squares[move.source()])
                       == Piece::BLACK)) {
                    return false;
                }

                if((move.destination() < move.source())
                   && (Piece::color(m_squares[move.source()])
                       == Piece::WHITE)) {
                    return false;
                }

                if(hor > 1) { return false; }

                if(hor == 0) {
                    if(ver > 2) { return false; }

                    if(ver == 2) {
                        if(!(((move.source() >= 8) && (move.source() <= 15))
                             || ((move.source() >= 48)
                                 && (move.source() <= 55)))) {
                            return false;
                        }
                    }

                    if(m_squares[move.destination()] != Piece::NONE) {
                        return false;
                    }
                } else {
                    if((ver != 1) || !diag) { return false; }

                    if(m_squares[move.destination()] == Piece::NONE) {
                        if((Piece::color(m_squares[move.source()])
                            == Piece::WHITE)
                           && !((move.source() >= 32)
                                && (move.source() < 40))) {
                            return false;
                        }

                        if((Piece::color(m_squares[move.source()])
                            == Piece::BLACK)
                           && !((move.source() >= 24)
                                && (move.source() < 32))) {
                            return false;
                        }

                        uint16_t offset = Piece::color(m_squares[move.source()])
                                               == Piece::WHITE
                                            ? -8
                                            : 8;

                        if(m_squares[move.destination() + offset]
                           != (Piece::PAWN
                               | Piece::opposite_side_color(
                                   m_squares[move.source()]))) {
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
                    bool white = Piece::color(m_squares[move.source()])
                              == Piece::WHITE;

                    uint16_t step = move.destination() > move.source() ? 1 : -1;

                    uint16_t rook
                        = step == 1 ? (white ? 7 : 63) : (white ? 0 : 56);

                    if(ver != 0) { return false; }

                    if(move.source() != (white ? 4 : 60)) { return false; }

                    if(m_squares[rook] != (Piece::ROOK | m_turn)) {
                        return false;
                    }

                    uint16_t i = move.source() + step;

                    while(i != rook) {
                        if(m_squares[i] != Piece::NONE) { return false; }

                        i += step;
                    }

                    if(square_attacked(move.source(), opponent_turn())) {
                        return false;
                    }

                    if(square_attacked(move.source() + step, opponent_turn())) {
                        return false;
                    }
                } else {
                    if((ver > 1) || !diag) { return false; }
                }

                break;
            }

            default:
                return false;
        }

        return true;
    }

    /**
     * @brief Checks if the given Move is a promotion move
     * @details A Move is promotion if it's made by a pawn and the
     * destination it's in the opposite player first file
     */
    [[nodiscard]] bool Board::move_is_promotion(const Move &move) const {
        return move.piece() == Piece::PAWN
            && (move.destination() < 8 || move.destination() >= 56);
    }

    /**
     * @brief Wraps the std::array::iterator begin() method to use it as Board
     * ConstIterator
     * @return The pointer to the first square's address
     */
    [[nodiscard]] internal_structure_t::const_iterator Board::begin() const {
        return m_squares.begin();
    }

    /**
     * @brief Wraps the std::array::iterator end() method to use it as Board
     * ConstIterator
     * @return The pointer to the last square's address
     */
    [[nodiscard]] internal_structure_t::const_iterator Board::end() const {
        return m_squares.end();
    }

    /**
     * @brief Used to init the board with the neutral FEN configuration
     * @details Parses the FEN string and inits the Board
     */
    void Board::init_board() {
        uint16_t file = 0;
        uint16_t rank = 7;

        std::array<std::string, 6> splitted_fen;
        std::stringstream stream {
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

        std::string tmp;

        for(uint64_t i = 0; i < 6; i++) {
            std::getline(stream, tmp, ' ');
            splitted_fen[i] = tmp;
        }

        for(auto &sym : splitted_fen[0]) {
            if(sym == '/') {
                file = 0;
                rank--;
            } else {
                if(isdigit(sym)) {
                    file += sym - '0';
                } else {
                    m_squares[rank * 8 + file] = Piece::g_fen_to_piece.at(sym);
                    file++;
                }
            }
        }
    }

    /**
     * @brief Clears all Board's squares
     */
    void Board::clear() {
        for(auto &square : m_squares) {
            square = Piece::NONE;
        }
    }

    /**
     * @brief Checks the number of horizontal squares a Move is making
     * @return The number of horizontal squares
     */
    [[nodiscard]] int64_t Board::horizontal_check(const Move &move) const {
        return std::abs(move.source() % 8 - move.destination() % 8);
    }

    /**
     * @brief Checks the number of vertical squares a Move is making
     * @return The number of vertical squares
     */
    [[nodiscard]] int64_t Board::vertical_check(const Move &move) const {
        return std::abs(move.source() / 8 - move.destination() / 8);
    }

    /**
     * @brief Checks if a Move is diagonal
     * @param ver The possible vertical values from the move source square
     * @return true if is moving diagonally, false otherwise
     */
    [[nodiscard]] bool Board::diagonal_check(int64_t ver,
                                             const Move &move) const {
        uint16_t step;

        if(ver != 0) {
            step = (move.destination() - move.source()) / ver;
        } else {
            step = move.destination() > move.source() ? 1 : -1;
        }

        uint16_t i = move.source() + step;

        while(i != move.destination()) {
            if(m_squares[i] != Piece::NONE) { return false; }

            i += step;
        }

        if(m_squares[i] != Piece::NONE) { return false; }

        if(Piece::color(m_squares[i])
           == Piece::color(m_squares[move.source()])) {
            return false;
        }

        return true;
    }

} // namespace DreamChess
