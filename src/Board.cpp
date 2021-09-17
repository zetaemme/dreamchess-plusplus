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
     * @brief Checks if the game is in progress
     * @return true if the game is in progress, false otherwise
     */
    [[nodiscard]] bool Board::is_in_game() const { return m_in_game; }

    /**
     * @brief Returns the piece corresponding to index
     * @param index The index of the returned piece
     * @return The corresponding piece
     */
    [[nodiscard]] Piece::Enum Board::piece_at(uint16_t index) const {
        return m_squares[index];
    }

    /**
     * @brief Returns who plays in current turn
     * @return True if it's WHITE, false otherwise
     */
    [[nodiscard]] Piece::Enum Board::turn() const { return m_turn; }

    /**
     * @brief Gets the next turn moving color
     * @return The opposite of m_turn
     */
    [[nodiscard]] Piece::Enum Board::opponent_turn() const {
        return m_turn == Piece::WHITE ? Piece::BLACK : Piece::WHITE;
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
     * @brief Returns the squares array of Board
     * @return The m_squares array
     */
    [[nodiscard]] std::array<Piece::Enum, 64> Board::squares() const {
        return m_squares;
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
     * @brief Checks if a given square is attached by another piece
     * @param index The index of the square
     * @param turn The playing turn
     * @return The color of the piece which is attacked
     */
    [[nodiscard]] bool Board::square_attacked(uint64_t index,
                                              Piece::Enum turn) const {
        for(auto &square : *this) {
            if(Piece::color(square) == turn) {
                Move move {*this,
                           static_cast<uint64_t>(&square - &m_squares[0]),
                           index};

                if(move.is_semi_valid()) { return true; }
            }
        }

        return false;
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

        if(move.is_promotion()) {
            // Promotion
            m_squares[move.destination()] = move.promotion_piece();
        } else {
            // The actual "common" move
            m_squares[move.destination()] = m_squares[move.source()];
        }

        m_squares[move.source()] = Piece::NONE;

        m_turn = m_turn == Piece::WHITE ? Piece::BLACK : Piece::WHITE;
    }

    /**
     * @brief Wraps the std::array::iterator begin() method to use it as Board
     * ConstIterator
     * @return The pointer to the first square's address
     */
    std::array<Piece::Enum, 64>::const_iterator Board::begin() const {
        return m_squares.begin();
    }

    /**
     * @brief Wraps the std::array::iterator end() method to use it as Board
     * ConstIterator
     * @return The pointer to the last square's address
     */
    std::array<Piece::Enum, 64>::const_iterator Board::end() const {
        return m_squares.end();
    }
} // namespace DreamChess
