/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */
#pragma once

#include <regex>
#include <string_view>

#include "Board.hpp"
#include "Piece.hpp"

namespace DreamChess {
/**
 * @brief A single move in the Game
 */
struct Move final {
    using piece_t = Piece::Enum;

public:
    Move(int64_t, int64_t, piece_t, piece_t);

    [[nodiscard]] int16_t source() const;
    [[nodiscard]] int16_t destination() const;
    [[nodiscard]] piece_t piece() const;
    [[nodiscard]] piece_t promotion_piece() const;
    [[nodiscard]] static std::regex move_regex();
    [[nodiscard]] static std::regex promotion_regex();

    [[nodiscard]] std::string to_alg() const;

private:
    /**
     * @brief The Move's source square
     */
    int16_t m_source;

    /**
     * @brief The Move's destination square
     */
    int16_t m_destination;

    /**
     * @brief The Piece which is making the move
     */
    piece_t m_piece;

    /**
     * @brief The declared promotion present, if promotion
     */
    piece_t m_promotion_piece;

    /**
     * @brief Pointer to the standard move regex pattern
     */
    static const std::shared_ptr<std::regex> m_move_regex;

    /**
     * @brief Pointer to the promotion move regex pattern
     */
    static const std::shared_ptr<std::regex> m_promotion_regex;
};
}    // namespace DreamChess
