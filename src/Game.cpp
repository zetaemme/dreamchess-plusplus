/**
 * @copyright Dreamchess++
 * @author Mattia Zorzan
 * @version v1.0
 * @date July-October, 2021
 * @file
 */

#include "Game.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <regex>

#include "Board.hpp"
#include "Move.hpp"
#include "Piece.hpp"

/**
 * @namespace dreamchess
 * @brief The only namespace used to contain the DreamChess++ logic
 * @details Used to avoid the std namespace pollution
 */
namespace dreamchess {
/**
 * @brief Overloads the out-stream operator for Game
 * @details Wraps the Board::operator<< to print the Board
 * @param stream The out-stream
 * @param game This game
 * @return The output stream
 */
std::ostream &operator<<(std::ostream &stream, const Game &game) {
    stream << game.m_board;

    return stream;
}

Board Game::board() const { return m_board; }

[[nodiscard]] bool Game::is_in_game() const { return m_board.is_in_game(); }

[[nodiscard]] bool Game::is_move_syntax_correct(const std::string &input_move) {
    std::smatch string_match;

    return std::regex_match(input_move, string_match, Move::move_regex()) ||
           std::regex_match(input_move, string_match, Move::promotion_regex());
}

bool Game::make_move(std::string_view input) {
    const uint16_t s_file = input.at(0) - 'a';
    const uint16_t s_rank = input.at(1) - '1';

    const uint16_t d_file = input.at(3) - 'a';
    const uint16_t d_rank = input.at(4) - '1';

    const uint16_t source = (s_rank * 8) + s_file;
    const uint16_t destination = (d_rank * 8) + d_file;

    Piece::Enum promotion_piece{Piece::NONE};

    if (((destination <= 7) || (destination >= 56 && destination <= 63)) &&
        Piece::type(piece_at(source)) == Piece::PAWN) {
        if (input.find('=') == std::string::npos) {
            promotion_piece = m_board.turn() | Piece::QUEEN;
        } else {
            if (m_board.turn() == Piece::WHITE && std::islower(input.at(6))) {
                return false;
            }

            if (m_board.turn() == Piece::BLACK && std::isupper(input.at(6))) {
                return false;
            }

            promotion_piece = Piece::to_enum(input.at(6));
        }
    }

    Move new_move{source, destination, piece_at(source), promotion_piece};

    if (!m_board.move_is_valid(new_move)) {
        return false;
    }

    m_board.make_move(new_move);
    update_history(new_move);

    return true;
}

void Game::export_to_file() const {
    std::filesystem::create_directory("../history");
    std::ofstream history_file{"../history/game_history.txt"};

    std::filesystem::permissions("../history/game_history.txt",
                                 std::filesystem::perms::owner_write |
                                     std::filesystem::perms::group_write |
                                     std::filesystem::perms::others_write,
                                 std::filesystem::perm_options::add);

    history_file << m_history.export_all();

    history_file.close();
}

void Game::reset() {
    m_board.clear();
    m_board.init_board();
}

Board::piece_t Game::piece_at(uint16_t index) const {
    return m_board.piece_at(index);
}

[[nodiscard]] Board::piece_array_t::const_iterator Game::begin() const {
    return m_board.begin();
}

[[nodiscard]] Board::piece_array_t::const_iterator Game::end() const {
    return m_board.end();
}

void Game::update_history(const Move &move) { m_history.add_step(move); }
}    // namespace dreamchess
