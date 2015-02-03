/**
 * libptce
 * Copyright (C) 2015 David Jolly
 * ----------------------
 *
 * libptce is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libptce is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/ptce.h"
#include "../include/ptce_board_type.h"

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		#define BLACK_RANK_FIRST BOARD_POS_MAX
		#define BLACK_RANK_SECOND (BOARD_POS_MAX - 1)
		#define KING_POS_CASTLING_LEFT 2
		#define KING_POS_CASTLING_RIGHT 6
		#define KING_POS_INIT 4
		#define ROOK_POS_CASTLING_LEFT 3
		#define ROOK_POS_CASTLING_RIGHT 5
		#define ROOK_POS_LEFT_INIT 0
		#define ROOK_POS_RIGHT_INIT BOARD_POS_MAX
		#define WHITE_RANK_FIRST 0
		#define WHITE_RANK_SECOND 1

		#define BOARD_COORD(_POS_) \
			(((BOARD_WID * BOARD_WID) - (BOARD_WID * (((_POS_).second) + 1))) + ((_POS_).first))

		static const ptce_piece_t PIECE_ODR[] = {
			PIECE_ROOK, PIECE_KNIGHT, PIECE_BISHOP, PIECE_QUEEN, 
			PIECE_KING, PIECE_BISHOP, PIECE_KNIGHT, PIECE_ROOK,
			};

		#define PIECE_ORDER(_POS_) \
			((_POS_) > BOARD_POS_MAX ? PIECE_EMPTY : PIECE_ODR[_POS_])

		_ptce_board::_ptce_board(
			__in_opt bool blank
			) :
				m_piece_captured(false),
				m_state(BOARD_INACTIVE)
		{
			TRACE_ENTRY();

			generate_initial_board(blank);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board::_ptce_board(
			__in const std::string &serial,
			__out ptce_board_mv_t &type
			) :
				m_piece_captured(false),
				m_state(BOARD_INACTIVE)
		{
			TRACE_ENTRY();

			type = unserialize(serial);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board::_ptce_board(
			__in const _ptce_board &other
			) :
				ptce_uid_base(other),
				m_piece_captured(other.m_piece_captured),
				m_piece_list(other.m_piece_list),
				m_piece_moved(other.m_piece_moved),
				m_state(other.m_state)
		{
			std::vector<ptce_piece>::iterator piece_iter;

			TRACE_ENTRY();

			for(piece_iter = m_piece_list.begin(); piece_iter != m_piece_list.end();
					++piece_iter) {
				increment_piece_reference(*piece_iter);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board::~_ptce_board(void)
		{
			std::vector<ptce_piece>::iterator piece_iter;

			TRACE_ENTRY();

			for(piece_iter = m_piece_list.begin(); piece_iter != m_piece_list.end();
					++piece_iter) {
				decrement_piece_reference(*piece_iter);
			}

			decrement_reference();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board &
		_ptce_board::operator=(
			__in const _ptce_board &other
			)
		{
			std::vector<ptce_piece>::iterator piece_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {

				for(piece_iter = m_piece_list.begin(); piece_iter != m_piece_list.end();
						++piece_iter) {
					decrement_piece_reference(*piece_iter);
				}

				ptce_uid_base::operator=(other);
				m_piece_captured = other.m_piece_captured;
				m_piece_list = other.m_piece_list;
				m_piece_moved = other.m_piece_moved;
				m_state = other.m_state;

				for(piece_iter = m_piece_list.begin(); piece_iter != m_piece_list.end();
						++piece_iter) {
					increment_piece_reference(*piece_iter);
				}
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		bool 
		_ptce_board::operator==(
			__in const _ptce_board &other
			)
		{
			size_t iter = 0;
			bool result = true;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				result = ((m_piece_captured == other.m_piece_captured)
						&& (m_piece_list.size() == other.m_piece_list.size())
						&& (m_piece_moved.first == other.m_piece_moved.first)
						&& (m_piece_moved.second == other.m_piece_moved.second)
						&& (m_state == other.m_state));

				if(result) {
					
					for(iter = 0; iter < m_piece_list.size(); ++iter) {

						if(m_piece_list.at(iter) != other.m_piece_list.at(iter)) {
							result = false;
							break;
						}
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_board::operator!=(
			__in const _ptce_board &other
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = !(*this == other);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		std::string 
		_ptce_board::board_as_string(
			__in const _ptce_board &board,
			__in_opt bool verbose
			)
		{
			int x, y;
			std::stringstream result;			
			std::vector<ptce_piece>::const_iterator piece_iter;
			size_t black = 0, count = 0, white = 0;

			TRACE_ENTRY();

			result << ptce_uid::id_as_string(board.m_uid) << ", State=" << BOARD_STATE_STRING(board.m_state)
					<< " (0x" << VALUE_AS_HEX(ptce_board_st_t, board.m_state) << ")";

			if(verbose) {

				for(piece_iter = board.m_piece_list.begin(); 
						piece_iter != board.m_piece_list.end(); ++piece_iter) {

					if(piece_iter->m_type != PIECE_EMPTY) {

						if(piece_iter->m_color == PIECE_WHITE) {
							++white;
						} else {
							++black;
						}

						++count;
					}
				}

				result << ", Last={" << (uint32_t) board.m_piece_moved.first << ", " 
						<< (uint32_t) board.m_piece_moved.second 
						<< "}, Captured=" << board.m_piece_captured << ", Count=" << count 
						<< " (white=" << white << ", black=" << black << ")" << std::endl;

				for(x = 0; x < BOARD_WID; ++x) {

					if(!x) {
						result << " ___";
					} else {
						result << "____";
					}
				}

				result << std::endl;

				for(y = BOARD_POS_MAX; y >= 0; --y) {

					for(x = 0; x < BOARD_WID; ++x) {
						result << "| " << ptce_piece::piece_as_symbol(
								board.m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y)))) 
								<< " ";
					}

					result << "|" << std::endl;

					if(y) {

						for(x = 0; x < BOARD_WID; ++x) {

							if(!x) {
								result << " ---";
							} else {
								result << "----";
							}
						}

						result << std::endl;
					}
				}

				for(x = 0; x < BOARD_WID; ++x) {

					if(!x) {
						result << " ‾‾‾";
					} else {
						result << "‾‾‾‾";
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		ptce_mv_t 
		_ptce_board::check_piece_move(
			__out std::set<ptce_mv_ent_t> &move_list,
			__in const ptce_pos_t &old_position,
			__in const ptce_pos_t &new_position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			size_t iter_x, iter_y = 0;
			ptce_mv_t result = MOVE_INVALID;
			bool allow = true, check = false;
			std::set<ptce_mv_ent_t> enemy_moves;
			ptce_piece check_piece, curr_piece, enemy_piece;
			std::set<ptce_mv_ent_t>::iterator enemy_move_iter;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>> pos_list;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>>::iterator enemy_pos_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if((old_position.first < BOARD_WID) 
					&& (old_position.second < BOARD_WID)
					&& (new_position.first < BOARD_WID) 
					&& (new_position.second < BOARD_WID)) {

				curr_piece = piece(old_position);
				if(curr_piece.type() == PIECE_KING) {

					for(; iter_y < BOARD_WID; ++iter_y) {

						for(iter_x = 0; iter_x < BOARD_WID; ++iter_x) {

							enemy_piece = piece(ptce_pos_t(iter_x, iter_y));
							if((enemy_piece.type() != PIECE_EMPTY)
									&& (enemy_piece.color() == enemy_color)) {

								enemy_moves = generate_move_set(ptce_pos_t(iter_x, iter_y), 
										(enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK);

								for(enemy_move_iter = enemy_moves.begin(); enemy_move_iter != enemy_moves.end();
										++enemy_move_iter) {

									if((enemy_piece.type() == PIECE_PAWN)
											&& ((enemy_move_iter->first == MOVE_NORMAL)
											|| (enemy_move_iter->first == MOVE_PROMOTE))) {
										continue;
									}

									for(enemy_pos_iter = enemy_move_iter->second.begin();
											enemy_pos_iter != enemy_move_iter->second.end();
											++enemy_pos_iter) {

										if((enemy_pos_iter->second.first == new_position.first)
												&& (enemy_pos_iter->second.second == new_position.second)) {
											allow = false;
											break;
										}
									}

									if(!allow) {
										break;
									}
								}
							}
						}

						if(!allow) {
							break;
						}
					}
				}

				if(allow) {

					check_piece = piece(new_position);
					if(check_piece.type() != PIECE_EMPTY) {

						if(check_piece.color() == enemy_color) {
							result = (check_piece.type() == PIECE_KING) ? MOVE_CHECK : MOVE_CAPTURE;
							pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position, new_position));
							check = true;
						} else {
							result = MOVE_PROTECT;
							pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position, new_position));
						}

						move_list.insert(ptce_mv_ent_t(result, pos_list));
					} else {
						result = MOVE_NORMAL;
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position, new_position));
						move_list.insert(ptce_mv_ent_t(result, pos_list));
					}

					if(!check 
							&& (curr_piece.type() == PIECE_PAWN)
							&& (((enemy_color == PIECE_BLACK) 
							&& (new_position.second == BOARD_POS_MAX))
							|| ((enemy_color == PIECE_WHITE) 
							&& !new_position.second))) {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position, new_position));
						move_list.insert(ptce_mv_ent_t(MOVE_PROMOTE, pos_list));					
					}
				}
			}

			TRACE_EXIT("Return Value: %s (0x%x)", MOVE_TYPE_STRING(result), result);
			return result;
		}

		void 
		_ptce_board::check_piece_moves_cross(
			__out std::set<ptce_mv_ent_t> &move_list,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			int x, y;
			ptce_mv_t piece_type;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(x = position.first + 1; x < BOARD_WID; ++x) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(x, position.second), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID)
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			for(x = position.first - 1; x >= 0; --x) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(x, position.second), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID)
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			for(y = position.second + 1; y < BOARD_WID; ++y) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(position.first, y), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID)
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			for(y = position.second - 1; y >= 0; --y) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(position.first, y), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID)
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			TRACE_EXIT("Return Value: Moves=%lu", move_list.size());
		}

		void 
		_ptce_board::check_piece_moves_diagonal(
			__out std::set<ptce_mv_ent_t> &move_list,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			int x, y;
			ptce_mv_t piece_type;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(x = position.first + 1, y = position.second + 1; x < BOARD_WID; ++x, ++y) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(x, y), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID) 
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			for(x = position.first - 1, y = position.second + 1; x >= 0; --x, ++y) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(x, y), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID) 
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			for(x = position.first + 1, y = position.second - 1; x < BOARD_WID; ++x, --y) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(x, y), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID) 
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			for(x = position.first - 1, y = position.second - 1; x >= 0; --x, --y) {

				piece_type = check_piece_move(move_list, position, ptce_pos_t(x, y), enemy_color);
				if((piece_type == MOVE_CAPTURE) 
						|| (piece_type == MOVE_INVALID) 
						|| (piece_type == MOVE_PROTECT)) {
					break;
				}
			}

			TRACE_EXIT("Return Value: Moves=%lu", move_list.size());
		}

		void 
		_ptce_board::clear(void)
		{
			size_t x, y = 0;
			ptce_piece board_piece;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(; y < BOARD_WID; ++y) {

				for(x = 0; x < BOARD_WID; ++x) {

					board_piece = piece(ptce_pos_t(x, y));
					if(board_piece.type() != PIECE_EMPTY) {
						remove(ptce_pos_t(x, y));
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_board::contains(
			__in const ptce_pos_t &position
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if((position.first > BOARD_POS_MAX)
					|| (position.second > BOARD_POS_MAX)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_POSITION,
					"{%i, %i} (must be at most {%i, %i})", position.first,
					position.second, BOARD_POS_MAX, BOARD_POS_MAX);
			}

			result = (m_piece_list.at(BOARD_COORD(position)).type() != PIECE_EMPTY);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		size_t 
		_ptce_board::decrement_piece_reference(
			__in const ptce_piece &piece
			)
		{
			size_t result = 0;
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(inst && inst->is_initialized()) {

				fact_inst = inst->acquire_piece_factory();
				if(fact_inst && fact_inst->contains(piece.m_uid)) {
					result = fact_inst->decrement_reference(piece.m_uid);
				}
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		void 
		_ptce_board::generate_initial_board(
			__in_opt bool blank
			)
		{
			size_t x, y = 0;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_piece_list.resize(BOARD_LEN);

			for(; y < BOARD_WID; ++y) {

				for(x = 0; x < BOARD_WID; ++x) {

					if(!blank) {

						switch(y) {
							case BLACK_RANK_SECOND:
								m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
									= generate_piece(PIECE_PAWN, PIECE_BLACK);
								break;
							case BLACK_RANK_FIRST:
							case WHITE_RANK_FIRST:
								m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) = generate_piece(PIECE_ORDER(x), 
									y == BLACK_RANK_FIRST ? PIECE_BLACK : PIECE_WHITE);
								break;
							case WHITE_RANK_SECOND:
								m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
									= generate_piece(PIECE_PAWN, PIECE_WHITE);
								break;
							default:
								m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
									= generate_piece(PIECE_EMPTY, PIECE_WHITE);
								break;
						}
					} else {
						m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
							= generate_piece(PIECE_EMPTY, PIECE_WHITE);
					}
				}
			}

			m_piece_captured = false;
			m_piece_moved = ptce_pos_t(0, 0);
			m_state = BOARD_INACTIVE;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_move_set(
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			ptce_piece board_piece;
			std::set<ptce_mv_ent_t> result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			board_piece = piece(position);
			switch(board_piece.type()) {
				case PIECE_BISHOP:
					result = generate_moves_bishop(board_piece, position, enemy_color);
					break;
				case PIECE_KING:
					result = generate_moves_king(board_piece, position, enemy_color);
					break;
				case PIECE_KNIGHT:
					result = generate_moves_knight(board_piece, position, enemy_color);
					break;
				case PIECE_PAWN:
					result = generate_moves_pawn(board_piece, position, enemy_color);
					break;
				case PIECE_QUEEN:
					result = generate_moves_queen(board_piece, position, enemy_color);
					break;
				case PIECE_ROOK:
					result = generate_moves_rook(board_piece, position, enemy_color);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_UNKNOWN_PIECE_TYPE,
						"%s", board_piece.to_string().c_str());
			}

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_moves_bishop(
			__in const ptce_piece &board_piece,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			std::set<ptce_mv_ent_t> result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(board_piece.m_type != PIECE_BISHOP) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s (expecting %s)", ptce_piece::piece_as_string(board_piece).c_str(),
					PIECE_TYPE_STRING(PIECE_BISHOP));
			}

			if(board_piece.m_color == enemy_color) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
					"%s", ptce_piece::piece_as_string(board_piece).c_str());
			}

			check_piece_moves_diagonal(result, position, enemy_color);

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_moves_king(
			__in const ptce_piece &board_piece,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			int x, y, y_off;
			size_t iter_x, iter_y;
			bool castling_allowed;
			ptce_piece enemy_piece;
			std::set<ptce_mv_ent_t> enemy_pos_list, result;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>> pos_list;
			std::set<ptce_mv_ent_t>::iterator enemy_pos_list_iter;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>>::iterator enemy_pos_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(board_piece.m_type != PIECE_KING) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s (expecting %s)", ptce_piece::piece_as_string(board_piece).c_str(),
					PIECE_TYPE_STRING(PIECE_KING));
			}

			if(board_piece.m_color == enemy_color) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
					"%s", ptce_piece::piece_as_string(board_piece).c_str());
			}

			for(y = (position.second ? (position.second - 1) : 0); 
					y <= (position.second < BOARD_POS_MAX ? (position.second + 1) : BOARD_POS_MAX); 
					++y) {

				for(x = (position.first ? (position.first - 1) : 0); 
						x <= (position.first < BOARD_POS_MAX ? (position.first + 1) : BOARD_POS_MAX); 
						++x) {

					if((x != position.first) || (y != position.second)) {
						check_piece_move(result, position, ptce_pos_t(x, y), enemy_color);
					}
				}
			}

			y_off = (enemy_color == PIECE_WHITE) ? BOARD_POS_MAX : 0;

			if(contains(ptce_pos_t(KING_POS_INIT, y_off))
					&& (piece(ptce_pos_t(KING_POS_INIT, y_off)).type() == PIECE_KING)
					&& (piece(ptce_pos_t(KING_POS_INIT, y_off)).color() 
							== ((enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK))
					&& !piece(ptce_pos_t(KING_POS_INIT, y_off)).moved()) {

				if(contains(ptce_pos_t(ROOK_POS_LEFT_INIT, y_off))
						&& (piece(ptce_pos_t(ROOK_POS_LEFT_INIT, y_off)).type() == PIECE_ROOK)
						&& (piece(ptce_pos_t(ROOK_POS_LEFT_INIT, y_off)).color() 
								== ((enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK))
						&& !piece(ptce_pos_t(ROOK_POS_LEFT_INIT, y_off)).moved()
						&& !contains(ptce_pos_t(ROOK_POS_LEFT_INIT + 1, y_off))
						&& !contains(ptce_pos_t(ROOK_POS_LEFT_INIT + 2, y_off))
						&& !contains(ptce_pos_t(ROOK_POS_LEFT_INIT + 3, y_off))) {

					castling_allowed = true;

					for(iter_y = 0; iter_y < BOARD_WID; ++iter_y) {

						for(iter_x = 0; iter_x < BOARD_WID; ++iter_x) {

							enemy_piece = piece(ptce_pos_t(iter_x, iter_y));
							if((enemy_piece.type() != PIECE_EMPTY)
									&& (enemy_piece.color() == enemy_color)) {
								enemy_pos_list = generate_move_set(ptce_pos_t(iter_x, iter_y), 
										(enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK);

								for(enemy_pos_list_iter = enemy_pos_list.begin(); 
										enemy_pos_list_iter != enemy_pos_list.end();
										++enemy_pos_list_iter) {

									for(enemy_pos_iter = enemy_pos_list_iter->second.begin();
											enemy_pos_iter != enemy_pos_list_iter->second.end();
											++enemy_pos_iter) {

										if(((enemy_pos_iter->second.first == (ROOK_POS_LEFT_INIT + 1)) 
												&& (enemy_pos_iter->second.second == y_off))
												|| ((enemy_pos_iter->second.first == (ROOK_POS_LEFT_INIT + 2)) 
												&& (enemy_pos_iter->second.second == y_off))
												|| ((enemy_pos_iter->second.first == (ROOK_POS_LEFT_INIT + 3)) 
												&& (enemy_pos_iter->second.second == y_off))) {
											castling_allowed = false;
											break;
										}
									}

									if(!castling_allowed) {
										break;
									}
								}
							}

							if(!castling_allowed) {
								break;
							}
						}

						if(!castling_allowed) {
							break;
						}
					}

					if(castling_allowed) {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(ptce_pos_t(ROOK_POS_LEFT_INIT, y_off), 
								ptce_pos_t(ROOK_POS_CASTLING_LEFT, y_off)));
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(ptce_pos_t(KING_POS_INIT, y_off), 
								ptce_pos_t(KING_POS_CASTLING_LEFT, y_off)));
						result.insert(ptce_mv_ent_t(MOVE_CASTLE, pos_list));
					}
				}

				if(contains(ptce_pos_t(ROOK_POS_RIGHT_INIT, y_off))
						&& (piece(ptce_pos_t(ROOK_POS_RIGHT_INIT, y_off)).type() == PIECE_ROOK)
						&& (piece(ptce_pos_t(ROOK_POS_RIGHT_INIT, y_off)).color() 
								== ((enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK))
						&& !piece(ptce_pos_t(ROOK_POS_RIGHT_INIT, y_off)).moved()
						&& !contains(ptce_pos_t(ROOK_POS_RIGHT_INIT - 1, y_off))
						&& !contains(ptce_pos_t(ROOK_POS_RIGHT_INIT - 2, y_off))) {

					castling_allowed = true;

					for(iter_y = 0; iter_y < BOARD_WID; ++iter_y) {

						for(iter_x = 0; iter_x < BOARD_WID; ++iter_x) {

							enemy_piece = piece(ptce_pos_t(iter_x, iter_y));
							if((enemy_piece.type() != PIECE_EMPTY)
									&& (enemy_piece.color() == enemy_color)) {
								enemy_pos_list = generate_move_set(ptce_pos_t(iter_x, iter_y), 
										(enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK);

								for(enemy_pos_list_iter = enemy_pos_list.begin(); 
										enemy_pos_list_iter != enemy_pos_list.end();
										++enemy_pos_list_iter) {

									for(enemy_pos_iter = enemy_pos_list_iter->second.begin();
											enemy_pos_iter != enemy_pos_list_iter->second.end();
											++enemy_pos_iter) {

										if(((enemy_pos_iter->second.first == (ROOK_POS_RIGHT_INIT - 1)) 
												&& (enemy_pos_iter->second.second == y_off))
												|| ((enemy_pos_iter->second.first == (ROOK_POS_RIGHT_INIT - 2)) 
												&& (enemy_pos_iter->second.second == y_off))) {
											castling_allowed = false;
											break;
										}
									}

									if(!castling_allowed) {
										break;
									}
								}
							}

							if(!castling_allowed) {
								break;
							}
						}

						if(!castling_allowed) {
							break;
						}
					}

					if(castling_allowed) {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(ptce_pos_t(ROOK_POS_RIGHT_INIT, y_off), 
								ptce_pos_t(ROOK_POS_CASTLING_RIGHT, y_off)));
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(ptce_pos_t(KING_POS_INIT, y_off), 
								ptce_pos_t(KING_POS_CASTLING_RIGHT, y_off)));
						result.insert(ptce_mv_ent_t(MOVE_CASTLE, pos_list));
					}
				}
			}

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_moves_knight(
			__in const ptce_piece &board_piece,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			std::set<ptce_mv_ent_t> result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(board_piece.m_type != PIECE_KNIGHT) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s (expecting %s)", ptce_piece::piece_as_string(board_piece).c_str(),
					PIECE_TYPE_STRING(PIECE_KNIGHT));
			}

			if(board_piece.m_color == enemy_color) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
					"%s", ptce_piece::piece_as_string(board_piece).c_str());
			}

			check_piece_move(result, position, ptce_pos_t(position.first + 2, position.second + 1), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first + 1, position.second + 2), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first - 2, position.second + 1), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first - 1, position.second + 2), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first + 2, position.second - 1), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first + 1, position.second - 2), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first - 2, position.second - 1), enemy_color);
			check_piece_move(result, position, ptce_pos_t(position.first - 1, position.second - 2), enemy_color);

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_moves_pawn(
			__in const ptce_piece &board_piece,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			ptce_piece enemy_piece;
			std::set<ptce_mv_ent_t> result;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>> pos_list;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(board_piece.m_type != PIECE_PAWN) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s (expecting %s)", ptce_piece::piece_as_string(board_piece).c_str(),
					PIECE_TYPE_STRING(PIECE_PAWN));
			}

			if(board_piece.m_color == enemy_color) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
					"%s", ptce_piece::piece_as_string(board_piece).c_str());
			}

			if(enemy_color == PIECE_BLACK) {

				if((position.first < BOARD_POS_MAX)
						&& (position.second < BOARD_POS_MAX)) {

					enemy_piece = piece(ptce_pos_t(position.first + 1, position.second + 1));
					if((enemy_piece.type() != PIECE_EMPTY)
							&& (enemy_piece.color() == enemy_color)) {
						check_piece_move(result, position, ptce_pos_t(position.first + 1, position.second + 1), 
								enemy_color);
					} else {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(position, 
								ptce_pos_t(position.first + 1, position.second + 1)));
						result.insert(ptce_mv_ent_t(MOVE_PROTECT, pos_list));
					}
				}
			
				if(position.first
						&& (position.second < BOARD_POS_MAX)) {

					enemy_piece = piece(ptce_pos_t(position.first - 1, position.second + 1));
					if((enemy_piece.type() != PIECE_EMPTY)
							&& (enemy_piece.color() == enemy_color)) {
						check_piece_move(result, position, ptce_pos_t(position.first - 1, position.second + 1), 
								enemy_color);
					} else {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(position, 
								ptce_pos_t(position.first - 1, position.second + 1)));
						result.insert(ptce_mv_ent_t(MOVE_PROTECT, pos_list));
					}
				}

				if((position.second < BOARD_POS_MAX)
						&& !contains(ptce_pos_t(position.first, position.second + 1))) {
					check_piece_move(result, position, ptce_pos_t(position.first, position.second + 1), 
							enemy_color);

					if(!board_piece.m_moved 
							&& (position.second < (BOARD_WID - 2))
							&& !contains(ptce_pos_t(position.first, position.second + 2))) {
						check_piece_move(result, position, ptce_pos_t(position.first, position.second + 2), 
								enemy_color);
					}
				}
			} else {

				if((position.first < BOARD_POS_MAX)
						&& position.second) {

					enemy_piece = piece(ptce_pos_t(position.first + 1, position.second - 1));
					if((enemy_piece.type() != PIECE_EMPTY)
							&& (enemy_piece.color() == enemy_color)) {
						check_piece_move(result, position, ptce_pos_t(position.first + 1, position.second - 1), 
								enemy_color);
					} else {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(position, 
								ptce_pos_t(position.first + 1, position.second - 1)));
						result.insert(ptce_mv_ent_t(MOVE_PROTECT, pos_list));
					}
				}
			
				if(position.first
						&& position.second) {

					enemy_piece = piece(ptce_pos_t(position.first - 1, position.second - 1));
					if((enemy_piece.type() != PIECE_EMPTY)
							&& (enemy_piece.color() == enemy_color)) {
						check_piece_move(result, position, ptce_pos_t(position.first - 1, position.second - 1), 
								enemy_color);
					} else {
						pos_list.clear();
						pos_list.insert(std::pair<ptce_pos_t, ptce_pos_t>(position, 
								ptce_pos_t(position.first - 1, position.second - 1)));
						result.insert(ptce_mv_ent_t(MOVE_PROTECT, pos_list));
					}
				}

				if(position.second
						&& !contains(ptce_pos_t(position.first, position.second - 1))) {
					check_piece_move(result, position, ptce_pos_t(position.first, position.second - 1), 
							enemy_color);

					if(!board_piece.m_moved 
							&& (position.second >= 2)
							&& !contains(ptce_pos_t(position.first, position.second - 2))) {
						check_piece_move(result, position, ptce_pos_t(position.first, position.second - 2), 
								enemy_color);
					}
				}
			}

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_moves_queen(
			__in const ptce_piece &board_piece,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			std::set<ptce_mv_ent_t> result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(board_piece.m_type != PIECE_QUEEN) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s (expecting %s)", ptce_piece::piece_as_string(board_piece).c_str(),
					PIECE_TYPE_STRING(PIECE_QUEEN));
			}

			if(board_piece.m_color == enemy_color) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
					"%s", ptce_piece::piece_as_string(board_piece).c_str());
			}

			check_piece_moves_cross(result, position, enemy_color);
			check_piece_moves_diagonal(result, position, enemy_color);

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		std::set<ptce_mv_ent_t> 
		_ptce_board::generate_moves_rook(
			__in const ptce_piece &board_piece,
			__in const ptce_pos_t &position,
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			std::set<ptce_mv_ent_t> result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(board_piece.m_type != PIECE_ROOK) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s (expecting %s)", ptce_piece::piece_as_string(board_piece).c_str(),
					PIECE_TYPE_STRING(PIECE_ROOK));
			}

			if(board_piece.m_color == enemy_color) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
					"%s", ptce_piece::piece_as_string(board_piece).c_str());
			}

			check_piece_moves_cross(result, position, enemy_color);

			TRACE_EXIT("Return Value: Moves=%lu", result.size());
			return result;
		}

		void 
		_ptce_board::generate_piece(
			__in const ptce_pos_t &position,
			__in ptce_piece_t type,
			__in ptce_piece_col_t color,
			__in_opt bool moved
			)
		{
			ptce_piece old_piece;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(contains(position)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_PIECE_ALREADY_EXISTS,
					"{%i, %i}", position.first, position.second);
			}

			old_piece = piece(position);
			m_piece_list.at(BOARD_COORD(position)) = generate_piece(type, color, moved);
			decrement_piece_reference(old_piece);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_piece &
		_ptce_board::generate_piece(
			__in ptce_piece_t type,
			__in ptce_piece_col_t color,
			__in_opt bool moved
			)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(!inst && inst->is_initialized()) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_ACQUIRE_PIECE_FACTORY_FAILED);
			}

			fact_inst = inst->acquire_piece_factory();
			if(!fact_inst) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_ACQUIRE_PIECE_FACTORY_FAILED);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return fact_inst->generate(type, color, moved);
		}

		size_t 
		_ptce_board::increment_piece_reference(
			__in const ptce_piece &piece
			)
		{
			size_t result = 0;
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(inst && inst->is_initialized()) {

				fact_inst = inst->acquire_piece_factory();
				if(fact_inst && fact_inst->contains(piece.m_uid)) {
					result = fact_inst->increment_reference(piece.m_uid);
				}
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		bool 
		_ptce_board::is_checkmated(
			__in_opt const ptce_piece_col_t &enemy_color
			)
		{
			size_t x, y;			
			ptce_pos_t pos = INVALID_POS;
			ptce_piece curr_piece, enemy_piece;
			bool attacked = false, result = true;
			std::set<ptce_mv_ent_t> enemy_pos_set, pos_set;
			std::set<ptce_mv_ent_t>::iterator enemy_pos_set_iter, pos_iter;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>>::iterator enemy_pos_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(y = 0; y < BOARD_WID; ++y) {

				for(x = 0; x < BOARD_WID; ++x) {

					curr_piece = piece(ptce_pos_t(x, y));
					if((curr_piece.type() == PIECE_KING)
							&& (curr_piece.color() == enemy_color)) {
						pos = ptce_pos_t(x, y);
						break;
					}
				}

				if(pos != INVALID_POS) {
					break;
				}
			}

			if(pos == INVALID_POS) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_KING_NOT_FOUND);
			}

			for(y = 0; y < BOARD_WID; ++y) {

				for(x = 0; x < BOARD_WID; ++x) {

					enemy_piece = piece(ptce_pos_t(x, y));
					if((enemy_piece.type() != PIECE_EMPTY)
							&& (enemy_piece.color() == ((enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK))) {

						enemy_pos_set = generate_move_set(ptce_pos_t(x, y), enemy_color);
						for(enemy_pos_set_iter = enemy_pos_set.begin(); 
								enemy_pos_set_iter != enemy_pos_set.end();
								++enemy_pos_set_iter) {

							for(enemy_pos_iter = enemy_pos_set_iter->second.begin();
									enemy_pos_iter != enemy_pos_set_iter->second.end();
									++enemy_pos_iter) {

								if((enemy_pos_iter->second.first == pos.first) 
										&& (enemy_pos_iter->second.second == pos.second)) {
									attacked = true;
									break;
								}
							}

							if(attacked) {
								break;
							}
						}
					}

					if(attacked) {
						break;
					}
				}

				if(attacked) {
					break;
				}
			}

			if(attacked) {

				pos_set = generate_move_set(pos, ((enemy_color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK));
				for(pos_iter = pos_set.begin(); pos_iter != pos_set.end(); ++pos_iter) {

					if(pos_iter->first != MOVE_PROTECT) {
						result = false;
						break;
					}
				}
			} else {
				result = false;
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		void 
		_ptce_board::move(
			__in const ptce_pos_t &old_position,
			__in const ptce_pos_t &new_position
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if((old_position.first > BOARD_POS_MAX)
					|| (old_position.second > BOARD_POS_MAX)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_POSITION,
					"{%i, %i} (must be at most {%i, %i})", old_position.first,
					old_position.second, BOARD_POS_MAX, BOARD_POS_MAX);
			}

			if((new_position.first > BOARD_POS_MAX)
					|| (new_position.second > BOARD_POS_MAX)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_POSITION,
					"{%i, %i} (must be at most {%i, %i})", new_position.first,
					new_position.second, BOARD_POS_MAX, BOARD_POS_MAX);
			}

			m_piece_captured = contains(new_position);
			decrement_piece_reference(m_piece_list.at(BOARD_COORD(new_position)));
			m_piece_list.at(BOARD_COORD(new_position)) = m_piece_list.at(BOARD_COORD(old_position));
			m_piece_list.at(BOARD_COORD(new_position)).moved() = true;
			m_piece_list.at(BOARD_COORD(old_position)) = generate_piece(PIECE_EMPTY, PIECE_WHITE);
			m_piece_moved = new_position;

			if(m_state == BOARD_INACTIVE) {
				m_state = BOARD_ACTIVE;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_piece &
		_ptce_board::piece(
			__in const ptce_pos_t &position
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if((position.first > BOARD_POS_MAX)
					|| (position.second > BOARD_POS_MAX)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_POSITION,
					"{%i, %i} (must be at most {%i, %i})", position.first,
					position.second, BOARD_POS_MAX, BOARD_POS_MAX);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_piece_list.at(BOARD_COORD(position));
		}

		bool 
		_ptce_board::piece_captured(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_piece_captured);
			return m_piece_captured;
		}

		size_t 
		_ptce_board::piece_count(
			__out size_t &white,
			__out size_t &black
			)
		{
			size_t result = 0;
			std::vector<ptce_piece>::iterator piece_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			white = 0;
			black = 0;

			for(piece_iter = m_piece_list.begin(); piece_iter != m_piece_list.end(); ++piece_iter) {

				if(piece_iter->type() != PIECE_EMPTY) {

					if(piece_iter->color() == PIECE_WHITE) {
						++white;
					} else {
						++black;
					}

					++result;
				}
			}

			TRACE_EXIT("Return Value: %lu (white=%lu, black=%lu)", result, white, black);
			return result;
		}

		std::vector<ptce_piece> &
		_ptce_board::piece_list(void) 
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_piece_list;
		}

		ptce_piece &
		_ptce_board::piece_moved(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_state == BOARD_INACTIVE) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_STATE,
					"%s (0x%x) (must not be in state %s (0x%x))", BOARD_STATE_STRING(m_state),
					m_state, BOARD_STATE_STRING(BOARD_INACTIVE), BOARD_INACTIVE);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return piece(m_piece_moved);
		}

		ptce_pos_t &
		_ptce_board::piece_moved_coordinate(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_piece_moved;
		}

		void 
		_ptce_board::remove(
			__in const ptce_pos_t &position
			)
		{
			ptce_piece old_piece;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if((position.first > BOARD_POS_MAX)
					|| (position.second > BOARD_POS_MAX)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_POSITION,
					"{%i, %i} (must be at most {%i, %i})", position.first, position.second, 
					BOARD_POS_MAX, BOARD_POS_MAX);
			}

			old_piece = piece(position);
			if(old_piece.type() == PIECE_EMPTY) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%s, {%i, %i}", PIECE_TYPE_STRING(old_piece.type()), position.first,
					position.second);
			}

			m_piece_list.at(BOARD_COORD(position)) = generate_piece(PIECE_EMPTY, PIECE_WHITE);
			decrement_piece_reference(old_piece);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		size_t 
		_ptce_board::score_move_bishop(
			__in const ptce_mv_ent_t &move,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0;

			TRACE_ENTRY();

			switch(move.first) {
				case MOVE_CAPTURE:
				case MOVE_CHECK:
				case MOVE_NORMAL:
				case MOVE_PROTECT:
					result = MOVE_HEURISTIC_VALUE(PIECE_BISHOP, move.first);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
						"type=%lu", move.first);
			}

			scores.insert(std::pair<ptce_mv_ent_t, size_t>(move, result));

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board::score_move_king(
			__in const ptce_mv_ent_t &move,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0;

			TRACE_ENTRY();

			switch(move.first) {
				case MOVE_CAPTURE:
				case MOVE_CASTLE:
				case MOVE_NORMAL:
				case MOVE_PROTECT:
					result = MOVE_HEURISTIC_VALUE(PIECE_KING, move.first);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
						"type=%lu", move.first);
			}

			scores.insert(std::pair<ptce_mv_ent_t, size_t>(move, result));

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board::score_move_knight(
			__in const ptce_mv_ent_t &move,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0;

			TRACE_ENTRY();

			switch(move.first) {
				case MOVE_CAPTURE:
				case MOVE_CHECK:
				case MOVE_NORMAL:
				case MOVE_PROTECT:
					result = MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, move.first);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
						"type=%lu", move.first);
			}

			scores.insert(std::pair<ptce_mv_ent_t, size_t>(move, result));

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board::score_move_pawn(
			__in const ptce_mv_ent_t &move,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0;

			TRACE_ENTRY();

			switch(move.first) {
				case MOVE_CAPTURE:
				case MOVE_CHECK:
				case MOVE_NORMAL:
				case MOVE_PROMOTE:
				case MOVE_PROTECT:
					result = MOVE_HEURISTIC_VALUE(PIECE_PAWN, move.first);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
						"type=%lu", move.first);
			}

			scores.insert(std::pair<ptce_mv_ent_t, size_t>(move, result));

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board::score_move_queen(
			__in const ptce_mv_ent_t &move,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0;

			TRACE_ENTRY();

			switch(move.first) {
				case MOVE_CAPTURE:
				case MOVE_CHECK:
				case MOVE_NORMAL:
				case MOVE_PROTECT:
					result = MOVE_HEURISTIC_VALUE(PIECE_QUEEN, move.first);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
						"type=%lu", move.first);
			}

			scores.insert(std::pair<ptce_mv_ent_t, size_t>(move, result));

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board::score_move_rook(
			__in const ptce_mv_ent_t &move,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0;

			TRACE_ENTRY();

			switch(move.first) {
				case MOVE_CAPTURE:
				case MOVE_CHECK:
				case MOVE_NORMAL:
				case MOVE_PROTECT:
					result = MOVE_HEURISTIC_VALUE(PIECE_ROOK, move.first);
					break;
				default:
					THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
						"type=%lu", move.first);
			}

			scores.insert(std::pair<ptce_mv_ent_t, size_t>(move, result));

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board::score_move_set(
			__in const ptce_piece_t &type,
			__in const std::set<ptce_mv_ent_t> &moves,
			__out std::set<std::pair<ptce_mv_ent_t, size_t>> &scores
			)
		{
			size_t result = 0, score;
			std::set<ptce_mv_ent_t>::const_iterator move_iter;

			TRACE_ENTRY();
		
			if(type > PIECE_TYPE_MAX) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
					"%lu (must be at most %lu)", type, PIECE_TYPE_MAX);
			}

			scores.clear();

			for(move_iter = moves.begin(); move_iter != moves.end(); ++move_iter) {

				switch(type) {
					case PIECE_KING:
						score = score_move_king(*move_iter, scores);
						break;
					case PIECE_QUEEN:
						score = score_move_queen(*move_iter, scores);
						break;
					case PIECE_ROOK:
						score = score_move_rook(*move_iter, scores);
						break;
					case PIECE_BISHOP:
						score = score_move_bishop(*move_iter, scores);
						break;
					case PIECE_KNIGHT:
						score = score_move_knight(*move_iter, scores);
						break;
					case PIECE_PAWN:
						score = score_move_pawn(*move_iter, scores);
						break;
					default:
						THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
							"type=%lu", type);
				}

				if(score > result) {
					result = score;
				}
			}

			TRACE_EXIT("Return Value: %lu");
			return result;
		}

		std::string 
		_ptce_board::serialize(
			__in_opt ptce_board_mv_t type
			)
		{
			size_t x = 0, y;
			ptce_piece piece;
			std::stringstream result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(type > BOARD_MOVE_MAX) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_INVALID_TYPE,
					"0x%x (must be at most %s (0x%x))", type, BOARD_MOVE_STRING(BOARD_MOVE_MAX),
					BOARD_MOVE_MAX);
			}

			result << BOARD_MOVE_STRING(type) << ":";

			for(; x < BOARD_WID; ++x) {

				for(y = 0; y < BOARD_WID; ++y) {
					piece = m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y)));
					result << x << y << piece.type() << piece.color();

					if((piece.type() == PIECE_KING)
							|| (piece.type() == PIECE_ROOK)
							|| (piece.type() == PIECE_PAWN)) {
						result << piece.moved();
					}

					result << " ";
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		size_t 
		_ptce_board::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = m_piece_list.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		ptce_board_st_t &
		_ptce_board::state(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %s (0x%x)", BOARD_STATE_STRING(m_state), m_state);
			return m_state;
		}

		std::string 
		_ptce_board::to_string(
			__in_opt bool verbose
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return board_as_string(*this, verbose);
		}

		ptce_board_mv_t 
		_ptce_board::unserialize(
			__in const std::string &serial
			)
		{
			bool moved;
			std::string token;
			ptce_piece_t type;
			ptce_piece_col_t color;
			ptce_board_mv_t result = BOARD_CHECKMATE;
			size_t x = 0, y, ch_iter = 0, cmd_iter = 0;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(serial.empty()) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_EMPTY_SERIALIZATION);
			}

			for(; ch_iter < serial.size(); ++ch_iter) {

				if(serial.at(ch_iter) == COMMAND_TOKEN_DELIM) {
					break;
				}

				token += serial.at(ch_iter);
			}

			std::transform(token.begin(), token.end(), token.begin(), ::tolower);

			for(; cmd_iter <= BOARD_MOVE_MAX; ++cmd_iter) {

				if(token == BOARD_MOVE_STRING(cmd_iter)) {
					break;
				}
			}

			if(cmd_iter > BOARD_MOVE_MAX) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_UNKNOWN_BOARD_COMMAND,
					"\'%s\'", token.c_str());
			}

			result = (ptce_board_mv_t) cmd_iter;

			if((ch_iter++ == serial.size()) || (ch_iter == serial.size())) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
					"Missing pieces: Offset=%lu", ch_iter);
			}

			m_piece_list.resize(BOARD_LEN);

			for(; x < BOARD_WID; ++x) {

				for(y = 0; y < BOARD_WID; ++y) {

					if((ch_iter + PIECE_TOKEN_LEN_MIN) >= serial.size()) {
						THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
							"Missing piece {%lu, %lu}", x, y);
					}

					token = std::string(1, serial.at(ch_iter++));
					if(std::atoi(token.c_str()) != x) {
						THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
							"Piece {%lu, %lu}: Mismatched x-coordinate: %s", x, y, token.c_str());
					}

					token = std::string(1, serial.at(ch_iter++));
					if(std::atoi(token.c_str()) != y) {
						THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
							"Piece {%lu, %lu}: Mismatched y-coordinate: %s", x, y, token.c_str());
					}

					token = std::string(1, serial.at(ch_iter++));
					type = (ptce_piece_t) std::atoi(token.c_str());
					token = std::string(1, serial.at(ch_iter++));
					color = (ptce_piece_col_t) std::atoi(token.c_str());

					if((type == PIECE_KING)
							|| (type == PIECE_ROOK)
							|| (type == PIECE_PAWN)) {

						if((ch_iter + PIECE_TOKEN_FLAG_LEN) >= serial.size()) {
							THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
								"Missing piece {%lu, %lu} flag", x, y);
						}

						token = std::string(1, serial.at(ch_iter++));
						moved = std::atoi(token.c_str()) ? true : false;
					} else {
						moved = false;
					}

					if(serial.at(ch_iter) != PIECE_TOKEN_SEP) {
						THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
							"Missing piece {%lu, %lu} seperator", x, y);
					}

					m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) = generate_piece(type, color, moved);
					++ch_iter;
				}
			}

			m_piece_captured = false;
			m_piece_moved = ptce_pos_t(0, 0);
			m_state = BOARD_INACTIVE;

			TRACE_EXIT("Return Value: %s (0x%x)", BOARD_MOVE_STRING(result), result);
			return result;
		}

		ptce_board_factory_ptr ptce_board_factory::m_instance = NULL;

		void 
		ptce_board_factory_destroy(void)
		{
			TRACE_ENTRY();

			if(ptce_board_factory::m_instance) {
				delete ptce_board_factory::m_instance;
				ptce_board_factory::m_instance = NULL;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board_factory::_ptce_board_factory(void) :
			m_initialized(false)
		{
			TRACE_ENTRY();

			std::atexit(ptce_board_factory_destroy);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board_factory::~_ptce_board_factory(void)
		{
			TRACE_ENTRY();

			if(m_initialized) {
				destroy();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_board_factory_ptr 
		_ptce_board_factory::acquire(void)
		{
			ptce_board_factory_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				m_instance = new ptce_board_factory();
				if(!m_instance) {
					THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0x%p", result);
			return result;
		}

		bool 
		_ptce_board_factory::contains(
			__in const ptce_uid &uid
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			result = (m_board_map.find(uid) != m_board_map.end());

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_board_factory::contains(
			__in const ptce_board &board
			)
		{
			return contains(board.m_uid);
		}

		size_t 
		_ptce_board_factory::decrement_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result = 0;
			std::map<ptce_uid, std::pair<ptce_board, size_t>>::iterator board_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			board_iter = find_board(uid);

			if(board_iter->second.second == PTCE_INIT_REF_DEF) {
				m_board_map.erase(board_iter);
			} else {
				result = --board_iter->second.second;
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board_factory::decrement_reference(
			__in const ptce_board &board
			)
		{
			return decrement_reference(board.m_uid);
		}

		void 
		_ptce_board_factory::destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			m_board_map.clear();
			m_initialized = false;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		std::map<ptce_uid, std::pair<ptce_board, size_t>>::iterator 
		_ptce_board_factory::find_board(
			__in const ptce_uid &uid
			)
		{
			std::map<ptce_uid, std::pair<ptce_board, size_t>>::iterator result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			result = m_board_map.find(uid);
			if(result == m_board_map.end()) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_UNKNOWN_BOARD,
					"%s", ptce_uid::id_as_string(uid).c_str());
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result;
		}

		ptce_board &
		_ptce_board_factory::generate(void)
		{
			ptce_board board;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			if(contains(board)) {
				THROW_PTCE_BOARD_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_ALREADY_EXISTS,
					"%s", board.id().to_string().c_str());
			}

			m_board_map.insert(std::pair<ptce_uid, std::pair<ptce_board, size_t>>(board.id(), 
					std::pair<ptce_board, size_t>(board, PTCE_INIT_REF_DEF)));

			TRACE_EXIT("Return Value: 0x%x", 0);
			return find_board(board.id())->second.first;			
		}

		size_t 
		_ptce_board_factory::increment_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			result = ++find_board(uid)->second.second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board_factory::increment_reference(
			__in const ptce_board &board
			)
		{
			return increment_reference(board.m_uid);
		}

		void 
		_ptce_board_factory::initialize(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_INITIALIZED);
			}

			m_board_map.clear();
			m_initialized = true;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_board_factory::is_allocated(void)
		{
			bool result;

			TRACE_ENTRY();

			result = (m_instance != NULL);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_board_factory::is_initialized(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_initialized);
			return m_initialized;
		}

		size_t 
		_ptce_board_factory::reference_count(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			result = find_board(uid)->second.second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_board_factory::reference_count(
			__in const ptce_board &board
			)
		{
			return reference_count(board.m_uid);
		}

		size_t 
		_ptce_board_factory::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_BOARD_EXCEPTION(PTCE_BOARD_EXCEPTION_UNINITIALIZED);
			}

			result = m_board_map.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string 
		_ptce_board_factory::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<ptce_uid, std::pair<ptce_board, size_t>>::iterator board_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << PTCE_BOARD_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance) 
					<< ", Initialized=" << m_initialized << ", Count=" << m_board_map.size();

			if(verbose) {

				for(board_iter = m_board_map.begin(); board_iter != m_board_map.end(); ++board_iter) {
					result << std::endl << " --- (" << board_iter->second.second << ") " 
							<< ptce_board::board_as_string(board_iter->second.first, verbose);
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
