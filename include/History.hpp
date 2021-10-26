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

namespace dreamchess {
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

    using step_list_t = std::list<Step>;

    /**
     * @brief Game History so far
     */
    step_list_t m_game_history{};

public:
    /**
     * @brief Constructs a History object
     */
    History() = default;
    ~History();

    void add_step(const Move &);

    [[nodiscard]] std::string export_all() const;
};
}    // namespace dreamchess
