/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-August, 2021
 */
#pragma once

#include "Piece.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace DreamChess {
    /**
     * @brief "Define Board, Pieces and moves for the game"
     */
    class Board final {
    public:
        explicit Board();

        friend std::ostream &operator<<(std::ostream &, const Board &);

        [[nodiscard]] std::string to_fen() const;

        [[nodiscard]] bool is_in_game() const;

        [[nodiscard]] Piece get_piece_at(uint16_t) const;

        [[nodiscard]] bool get_turn() const;

    private:
        /**
         * @brief "'false' for BLACK's or 'true' for WHITE's turn"
         */
        bool m_turn = true;

        /**
         * @brief "Counts the number of turns since the game started"
         */
        uint64_t m_turn_counter = 1;

        /**
         * @brief "Checks if the game is still going on"
         */
        bool m_in_game = true;

        /**
         * @brief "Array describing the board's state"
         */
        std::array<Piece, 64> m_squares {};

        /**
         * @brief "Keeps track of captured pieces"
         */
        std::map<Piece, uint16_t> m_captured {};

        /**
         * @brief "Vector with all the possible moves for the current board
         * state"
         */
        std::vector<Move> m_move_list;

        void init_board();
        void init_move_list();
        void make_move(const Move &);
    };
} // namespace DreamChess
