/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 */
#pragma once

#include <list>
#include <memory>
#include <string_view>

#include "Board.hpp"
#include "Move.hpp"

namespace DreamChess {
/**
 * @brief The current game History
 */
class History final {
private:
    /**
     * @brief A single step into the History
     */
    struct Step final {
        /**
         * @brief Last Move which has been made
         */
        std::string m_move;

        explicit Step(const Move &);
    };

    using internal_structure_t = std::list<Step>;

    /**
     * @brief Game History so far
     */
    // FIXME La history è still_reachable secondo valgrind
    internal_structure_t m_game_history{};

public:
    /**
     * @brief Constructs a History object
     */
    History() = default;

    void add_step(const Move &);

    [[nodiscard]] std::string export_all() const;

    [[nodiscard]] internal_structure_t::const_iterator begin() const;
    [[nodiscard]] internal_structure_t::const_iterator end() const;
};
}    // namespace DreamChess
