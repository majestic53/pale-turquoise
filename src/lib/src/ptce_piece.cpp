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
#include "../include/ptce_piece_type.h"

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		static const std::string PIECE_SYMBOL_STR[] = {
			" ", "♔", "♕", "♖", "♗", "♘", "♙",
			// ---
			" ", "♚", "♛", "♜", "♝", "♞", "♟",
			};

		#define PIECE_SYMBOL_STRING(_TYPE_, _COLOR_) \
			((((_TYPE_) > PIECE_TYPE_MAX) || ((_COLOR_) > PIECE_COLOR_MAX)) ? UNKNOWN : \
			PIECE_SYMBOL_STR[((PIECE_TYPE_MAX + 1) * (_COLOR_)) + (_TYPE_)].c_str())

		_ptce_piece::_ptce_piece(
			__in ptce_piece_t type,
			__in ptce_piece_col_t color
			) :
				m_color(color),
				m_type(type)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_piece::_ptce_piece(
			__in const _ptce_piece &other
			) :
				ptce_uid_base(other),
				m_color(other.m_color),
				m_type(other.m_type)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_piece::~_ptce_piece(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_piece &
		_ptce_piece::operator=(
			__in const _ptce_piece &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				ptce_uid_base::operator=(other);
				m_color = other.m_color;
				m_type = other.m_type;
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		bool 
		_ptce_piece::operator==(
			__in const _ptce_piece &other
			)
		{
			bool result = true;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				result = ((id() == other.m_uid) 
						&& (m_color == other.m_color) 
						&& (m_type == other.m_type));
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_piece::operator!=(
			__in const _ptce_piece &other
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = !(*this == other);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		ptce_piece_col_t &
		_ptce_piece::color(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %s (0x%x)", PIECE_COLOR_STRING(m_color), m_color);
			return m_color;
		}

		std::string 
		_ptce_piece::piece_as_string(
			__in const _ptce_piece &piece,
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			TRACE_ENTRY();

			result << ptce_uid::id_as_string(piece.m_uid) << " Type=" << PIECE_TYPE_STRING(piece.m_type) 
					<< " (0x" << VALUE_AS_HEX(ptce_piece_t, piece.m_type) << " ), Color=" 
					<< PIECE_COLOR_STRING(piece.m_color) << " (0x" 
					<< VALUE_AS_HEX(ptce_piece_col_t, piece.m_color) << ")";

			if(verbose) {
				result << ", Symbol=\'" << piece_as_symbol(piece) << "\'";
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		std::string 
		_ptce_piece::piece_as_symbol(
			__in const _ptce_piece &piece
			)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
			return PIECE_SYMBOL_STRING(piece.m_type, piece.m_color);
		}

		ptce_piece_t &
		_ptce_piece::type(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %s (0x%x)", PIECE_TYPE_STRING(m_type), m_type);
			return m_type;
		}

		std::string 
		_ptce_piece::to_string(
			__in_opt bool verbose
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return piece_as_string(*this, verbose);
		}
	}
}
