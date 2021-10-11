/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */
#pragma once

#include <array>
#include <cstdint>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "Piece.hpp"

namespace DreamChess {
// Move forward declaration
struct Move;

/**
 * @brief Defines a chess Game board
 */
class Board final {
    using piece_t = Piece::Enum;
    using internal_structure_t = std::array<piece_t, 64>;

public:
    Board();
    ~Board();

    friend std::ostream &operator<<(std::ostream &, const Board &);

    void make_move(const Move &);

    [[nodiscard]] bool is_in_game() const;
    [[nodiscard]] bool is_in_check() const;
    [[nodiscard]] bool is_mated() const;

    [[nodiscard]] internal_structure_t squares() const;
    [[nodiscard]] piece_t turn() const;
    [[nodiscard]] piece_t opponent_turn() const;

    [[nodiscard]] piece_t piece_at(uint16_t) const;
    [[nodiscard]] bool square_attacked(uint64_t, piece_t) const;

    [[nodiscard]] bool move_is_valid(const Move &) const;
    [[nodiscard]] bool move_is_semi_valid(const Move &) const;
    [[nodiscard]] bool move_is_promotion(const Move &) const;

    [[nodiscard]] internal_structure_t::const_iterator begin() const;
    [[nodiscard]] internal_structure_t::const_iterator end() const;

private:
    /**
     * @brief false for BLACK's or true for WHITE's turn
     */
    piece_t m_turn{Piece::WHITE};

    /**
     * @brief Array describing the board's state
     */
    internal_structure_t m_squares{};

    /**
     * @brief Keeps track of captured pieces
     */
    std::map<piece_t, uint16_t> m_captured{};

    void init_board();
    void clear();

    [[nodiscard]] int64_t horizontal_check(const Move &) const;
    [[nodiscard]] int64_t vertical_check(const Move &) const;
    [[nodiscard]] bool diagonal_check(int64_t, const Move &) const;

    friend class Game;
};
}    // namespace DreamChess
