/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */
#pragma once

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#include "Board.hpp"
#include "History.hpp"
#include "Piece.hpp"

namespace DreamChess {
// Move forward declaration
struct Move;

/**
 * @brief Describes a chess Game, with a Board and a History
 */
class Game final {
    using piece_t = Piece::Enum;
    using board_internal_structure_t = std::array<piece_t, 64>;

public:
    Game();

    friend std::ostream &operator<<(std::ostream &, const Game &);

    Board board() const;

    [[nodiscard]] bool is_in_game() const;

    bool make_move(std::string_view);
    void export_to_file() const;

    void reset();

    piece_t piece_at(uint16_t index) const;

    [[nodiscard]] board_internal_structure_t::const_iterator begin() const;
    [[nodiscard]] board_internal_structure_t::const_iterator end() const;

private:
    /**
     * @brief The current game's Board
     */
    Board m_board;

    /**
     * @brief The current game's History
     */
    History m_history;

    void update_history(const Move &);
};
}    // namespace DreamChess