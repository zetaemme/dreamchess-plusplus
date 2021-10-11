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
public:
    Game();

    friend std::ostream &operator<<(std::ostream &, const Game &);

    [[nodiscard]] bool is_in_game() const;

    bool make_move(std::string_view);
    void export_to_file() const;

    void reset();

    Piece::Enum piece_at(uint16_t index) const;

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