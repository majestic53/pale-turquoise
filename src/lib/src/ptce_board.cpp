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

		#define BLACK_LOWER_ROW (BOARD_POS_MAX - 1)
		#define BLACK_UPPER_ROW BOARD_POS_MAX
		#define WHITE_LOWER_ROW 0
		#define WHITE_UPPER_ROW 1

		#define BOARD_COORD(_POS_) \
			(((BOARD_WID * BOARD_WID) - (BOARD_WID * (((_POS_).second) + 1))) + ((_POS_).first))

		static const ptce_piece_t PIECE_ODR[] = {
			PIECE_ROOK, PIECE_KNIGHT, PIECE_BISHOP, PIECE_KING, 
			PIECE_QUEEN, PIECE_BISHOP, PIECE_KNIGHT, PIECE_ROOK,
			};

		#define PIECE_ORDER(_POS_) \
			((_POS_) > BOARD_POS_MAX ? PIECE_EMPTY : PIECE_ODR[_POS_])

		_ptce_board::_ptce_board(void) :
			m_piece_captured(false),
			m_state(BOARD_INACTIVE)
		{
			TRACE_ENTRY();

			generate_initial_board();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_board::_ptce_board(
			__in const _ptce_board &other
			) :
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
		_ptce_board::generate_initial_board(void)
		{
			size_t x, y = 0;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_piece_list.resize(BOARD_LEN);

			for(; y < BOARD_WID; ++y) {

				for(x = 0; x < BOARD_WID; ++x) {

					switch(y) {
						case BLACK_LOWER_ROW:
							m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
								= generate_piece(PIECE_PAWN, PIECE_BLACK);
							break;
						case BLACK_UPPER_ROW:
						case WHITE_LOWER_ROW:
							m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) = generate_piece(PIECE_ORDER(x), 
								y == BLACK_UPPER_ROW ? PIECE_BLACK : PIECE_WHITE);
							break;
						case WHITE_UPPER_ROW:
							m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
								= generate_piece(PIECE_PAWN, PIECE_WHITE);
							break;
						default:
							m_piece_list.at(BOARD_COORD(ptce_pos_t(x, y))) 
								= generate_piece(PIECE_EMPTY, PIECE_WHITE);
							break;
					}
				}
			}

			m_piece_captured = false;
			m_piece_moved = ptce_pos_t(0, 0);
			m_state = BOARD_INACTIVE;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_piece &
		_ptce_board::generate_piece(
			__in ptce_piece_t type,
			__in ptce_piece_col_t color
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
			return fact_inst->generate(type, color);
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
	}
}
