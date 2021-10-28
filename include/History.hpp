/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */
#pragma once

#include <list>
#include <memory>
#include <string_view>

#include "Board.hpp"
#include "Move.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {
/**
 * @class History
 * @brief The current game History
 */
class History final {
private:
    /**
     * @struct Step
     * @brief A single step into the History
     * @details Each Step is represented as the ALG notation representation of
     * the move which brought the game in this state
     */
    struct Step final {
        /**
         * @brief Last Move which has been made
         */
        std::string m_move;

        /**
         * @brief Constructs the Step
         * @details Each Step is the algebraic notation representation of the
         * Move
         * @see Move::to_alg()
         */
        explicit Step(const Move &);
    };

    /**
     * @typedef Defines the step_list_t type to improve readability
     */
    using step_list_t = std::list<Step>;

    /**
     * @brief Game History so far
     */
    step_list_t m_game_history{};

public:
    /**
     * @fn History()
     * @brief Constructs a History object
     */
    History() = default;

    /**
     * @fn ~History()
     * @brief The History class destructor
     * @details Clears the History
     */
    ~History();

    /**
     * @fn void add_step(const Move &)
     * @brief Adds a step to the History list
     * @param move The last move made in the referenced board
     * @see std::list::emplace_back()
     */
    void add_step(const Move &);

    /**
     * @fn std::string export_all()
     * @brief Exports the History as a string
     * @details Every Step is exported as "<Move number>. <Move in algebraic>"
     * @return The whole Game's History as a string
     * @see std::to_string()
     * @see std::list::front()
     * @see std::list::push_back()
     * @see std::list::pop_front()
     */
    [[nodiscard]] std::string export_all() const;
};
}    // namespace dreamchess
