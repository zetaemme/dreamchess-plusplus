/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */

#include "Board.hpp"

#include "Move.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <sstream>

namespace DreamChess {
    /**
     * @brief "Constructs a `Board`"
     * @details "Starts with the neutral FEN string, using `init_board()`"
     */
    Board::Board() { init_board(); }

    /**
     * @brief "`out-stream` operator overloading"
     * @details "Print each piece and ends line every 8 files"
     * @param stream The new output stream
     * @param board The printed board
     * @return The output stream
     */
    std::ostream &operator<<(std::ostream &stream, const Board &board) {
        for(uint64_t i = 0; i < 64; i++) {
            stream << Piece::g_piece_repr.at(board.m_squares[i]);

            if((i + 1) % 8 == 0) { stream << std::endl; }
        }

        return stream;
    }

    /**
     * @brief "Converts the board to FEN notation"
     * @details "First the method constructs the actual state of the Board, then
     *          replaces consecutive whitespaces with the number of ' ' chars.
     *          Finally it adds Move, Castle, En Passant, Semi-moves end Number
     *          of Moves since the beginning"
     * @return The FEN representation of the Board
     */
    [[nodiscard]] std::string Board::to_fen() const {
        std::string fen;

        // Board representation
        for(uint64_t i = 0; i < 64; i++) {
            fen.push_back(
                static_cast<char>(Piece::g_piece_repr.at(m_squares[i])));

            if((i + 1) % 8 == 0 && i != 63) { fen.push_back('/'); }
        }

        // Removing whitespaces
        uint16_t counter = 0;
        for(uint64_t i = 0; i < fen.length(); i++) {
            if(fen.at(i) == ' ') {
                counter++;

                for(uint64_t j = i; j < i + 7; j++) {
                    if(!isblank(fen.at(j))) { break; }

                    counter++;
                }

                fen.replace(i, counter, std::to_string(counter));
                i++;
                counter = 0;
            }
        }

        std::string turn = m_turn == Piece::WHITE ? "w" : "b";
        fen.append(" " + turn + " ");

        std::string castle;

        // TODO: Manca controllo se re è sotto scacco
        // White can castle
        if(m_squares[4] == Piece::WHITE_KING) {
            // Kingside
            if(m_squares[7] == Piece::WHITE_ROOK) { castle.append("K"); }

            // Queenside
            if(m_squares[0] == Piece::WHITE_ROOK) { castle.append("Q"); }
        }

        // Black can castle
        if(m_squares[60] == Piece::BLACK_KING) {
            // Kingside
            if(m_squares[63] == Piece::BLACK_ROOK) { castle.append("k"); }

            // Queenside
            if(m_squares[56] == Piece::BLACK_ROOK) { castle.append("q"); }
        }

        if(!castle.empty()) {
            fen.append(castle + " ");
        } else {
            // No castle is possible
            fen.append("- ");
        }

        std::string en_passant;

        // TODO Manca controllo mossa precedente
        for(uint64_t i = 24; i < 32; i++) {
            if(m_turn == Piece::BLACK) {
                if(m_squares[i] == Piece::BLACK_PAWN) {
                    if(m_squares[i + 1] == Piece::WHITE_PAWN
                       || m_squares[i - 1] == Piece::WHITE_PAWN) {
                        switch(i) {
                            case 24:
                                en_passant.append("a6");
                                break;
                            case 25:
                                en_passant.append("b6");
                                break;
                            case 26:
                                en_passant.append("c6");
                                break;
                            case 27:
                                en_passant.append("d6");
                                break;
                            case 28:
                                en_passant.append("e6");
                                break;
                            case 29:
                                en_passant.append("f6");
                                break;
                            case 30:
                                en_passant.append("g6");
                                break;
                            default:
                                en_passant.append("h6");
                                break;
                        }
                    }
                }
            } else {
                if(m_squares[i] == Piece::WHITE_PAWN) {
                    if(m_squares[i + 1] == Piece::BLACK_PAWN
                       || m_squares[i - 1] == Piece::BLACK_PAWN) {
                        switch(i) {
                            case 24:
                                en_passant.append("a3");
                                break;
                            case 25:
                                en_passant.append("b3");
                                break;
                            case 26:
                                en_passant.append("c3");
                                break;
                            case 27:
                                en_passant.append("d3");
                                break;
                            case 28:
                                en_passant.append("e3");
                                break;
                            case 29:
                                en_passant.append("f3");
                                break;
                            case 30:
                                en_passant.append("g3");
                                break;
                            default:
                                en_passant.append("h3");
                                break;
                        }
                    }
                }
            }

            if(!en_passant.empty()) { break; }
        }

        if(!en_passant.empty()) {
            fen.append(en_passant + " ");
        } else {
            fen.append("- ");
        }

        // Half-moves
        // TODO Implementare
        fen.append("0 ");

        // Turn number
        fen.append(std::to_string(m_turn_counter));

        return fen;
    }

    /**
     * @brief "Checks if the game is in progress"
     * @return true if the game is in progress, false otherwise
     */
    [[nodiscard]] bool Board::is_in_game() const { return m_in_game; }

    /**
     * @brief "Returns the piece corresponding to index"
     * @param index The index of the returned piece
     * @return The corresponding piece
     */
    [[nodiscard]] Piece::Enum Board::get_piece_at(uint16_t index) const {
        return m_squares[index];
    }

    /**
     * @brief "Returns who plays in current turn"
     * @return True if it's WHITE, false otherwise
     */
    [[nodiscard]] Piece::Enum Board::get_turn() const { return m_turn; }

    /**
     * @brief "Checks if one of the two sides is under check"
     * @return The side who's in check
     */
    [[nodiscard]] Piece::Enum Board::is_in_check() const {
        auto playing_side
            = m_turn == Piece::WHITE ? Piece::BLACK : Piece::WHITE;
        auto opponent_king = (Piece::KING | playing_side);

        for(uint64_t i = 0; i < 64; i++) {
            if(m_squares[i] == opponent_king) { return square_attacked(i); }
        }

        return Piece::NONE;
    }

    /**
     * @brief "Used to init the board with the neutral FEN configuration"
     * @details "Parses the FEN string and inits the `Board`"
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
     * @brief Inits the std::vector containing all the available moves
     */
    void Board::init_move_list() {
        // TODO Generate all legal moves
    }

    /**
     * @breif "Checks if a given square is attached by another piece"
     * @param index The index of the square
     * @return The color of the piece which is attacked
     */
    [[nodiscard]] Piece::Enum Board::square_attacked(uint64_t index) const {
        for(uint64_t i = 0; i < 64; i++) {
            if(Piece::get_color(m_squares[i]) == m_turn) {
                Move move {*this, i, index};

                if(is_semi_valid_move(move)) { return Piece::WHITE; }
            }
        }

        return Piece::BLACK;
    }

    /**
     * @brief "Checks if the diagonals of the given move are free"
     * @param move The move to check
     * @param ver The possible vertical values from the move source square
     * @return True if the diagonals are free, False otherwise
     */
    [[nodiscard]] bool Board::is_diagonals_ok(const Move &move,
                                              int64_t ver) const {
        uint16_t step;
        if(ver != 0) {
            step = (move.get_destination() - move.get_source()) / ver;
        } else {
            step = move.get_destination() > move.get_source() ? 1 : -1;
        }

        uint16_t i = move.get_source() + step;

        while(i != move.get_destination()) {
            if(m_squares[i] != Piece::NONE) { return false; }

            i += step;
        }

        if(m_squares[i] != Piece::NONE) { return false; }

        if(Piece::get_color(m_squares[i])
           != Piece::get_color(m_squares[move.get_source()])) {
            return false;
        }

        return true;
    }

    /**
     * @brief "Checks if a move is semi_valid"
     * @param move The move to check
     * @return True if the move is semi_valid, False otherwise
     */
    [[nodiscard]] bool Board::is_semi_valid_move(const Move &move) const {
        if(!move.is_valid()
           || Piece::get_color(m_squares[move.get_source()]) != m_turn) {
            return false;
        }

        int64_t hor = move.horizontal_check();
        int64_t ver = move.vertical_check();

        bool diag = is_diagonals_ok(move, ver);

        switch(Piece::get_type(move.get_piece())) {
            case Piece::KNIGHT:
                if(hor != 1 && hor != 2) { return false; }

                if(hor == 1 && ver != 2) { return false; }

                if(hor == 2 && ver != 1) { return false; }

                if(m_squares[move.get_destination()] == Piece::NONE) { break; }

                if(Piece::get_color(m_squares[move.get_destination()])
                   == Piece::get_color(m_squares[move.get_source()])) {
                    return false;
                }
                break;

            case Piece::BISHOP:
                if(hor != ver) { return false; }

                if(!diag) { return false; }

                break;

            case Piece::ROOK:
                if(hor != 0 && ver != 0) { return false; }

                if(!diag) { return false; }

                break;

            case Piece::QUEEN:
                if(hor != 0 && ver != 0 && hor != ver) { return false; }

                if(!diag) { return false; }

                break;

            // TODO Finire cases 279 board.c dreamchess/dreamchess
            case Piece::PAWN:
                break;
            case Piece::KING:
                break;
            default:
                return false;
        }

        return true;
    }

    /**
     * @brief "Makes a move in the current `Board`"
     * @details "Checks if the `Move` is a "special move", makes a "normal move"
     * otherwise"
     * @param move The `Move` to make
     */
    bool Board::make_move(const Move &move) {
        if(move.is_valid()) {
            // En-passant
            if(Piece::get_type(move.get_piece()) == Piece::PAWN
               && m_squares[move.get_destination()] == 0) {
                uint16_t en_passant
                    = move.get_destination()
                    - 8 * (move.get_destination() > move.get_source() ? 1 : -1);
                m_captured[m_squares[en_passant]]++;
                m_squares[en_passant] = Piece::NONE;
            }

            // Updating captured pieces
            if(move.get_destination() != 0) {
                m_captured[m_squares[move.get_destination()]]++;
            }

            // kingside castle
            if(Piece::get_type(move.get_piece()) == Piece::KING
               && move.get_destination() - move.get_source() == 2) {
                m_squares[move.get_destination() - 1]
                    = m_squares[move.get_destination() + 1];
                m_squares[move.get_destination() + 1] = Piece::NONE;
            }

            // Queenside castle
            if(Piece::get_type(move.get_piece()) == Piece::KING
               && move.get_source() - move.get_destination() == 2) {
                m_squares[move.get_destination() + 1]
                    = m_squares[move.get_destination() - 2];
                m_squares[move.get_destination() - 2] = Piece::NONE;
            }

            if(move.is_promotion()) {
                // Promotion
                m_squares[move.get_destination()] = move.get_promotion_piece();
            } else {
                // The actual "common" move
                m_squares[move.get_destination()]
                    = m_squares[move.get_source()];
            }
        } else {
            return false;
        }

        return true;
    }
} // namespace DreamChess