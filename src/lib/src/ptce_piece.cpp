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
			" ", "♚", "♛", "♜", "♝", "♞", "♟",
			// ---
			" ", "♔", "♕", "♖", "♗", "♘", "♙",
			};

		#define PIECE_SYMBOL_STRING(_TYPE_, _COLOR_) \
			((((_TYPE_) > PIECE_TYPE_MAX) || ((_COLOR_) > PIECE_COLOR_MAX)) ? UNKNOWN : \
			PIECE_SYMBOL_STR[((PIECE_TYPE_MAX + 1) * (_COLOR_)) + (_TYPE_)].c_str())

		_ptce_piece::_ptce_piece(
			__in_opt ptce_piece_t type,
			__in_opt ptce_piece_col_t color,
			__in_opt bool moved
			) :
				m_color(color),
				m_moved(moved),
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
				m_moved(other.m_moved),
				m_type(other.m_type)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_piece::~_ptce_piece(void)
		{
			TRACE_ENTRY();

			decrement_reference();

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
				m_moved = other.m_moved;
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
						&& (m_moved == other.m_moved)
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

		bool &
		_ptce_piece::moved(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_moved);
			return m_moved;
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
					<< " (0x" << VALUE_AS_HEX(ptce_piece_t, piece.m_type) << "), Color=" 
					<< PIECE_COLOR_STRING(piece.m_color) << " (0x" 
					<< VALUE_AS_HEX(ptce_piece_col_t, piece.m_color) << "), Moved=" 
					<< (piece.m_moved ? "TRUE" : "FALSE");

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

		ptce_piece_factory_ptr ptce_piece_factory::m_instance = NULL;

		void 
		ptce_piece_factory_destroy(void)
		{
			TRACE_ENTRY();

			if(ptce_piece_factory::m_instance) {
				delete ptce_piece_factory::m_instance;
				ptce_piece_factory::m_instance = NULL;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_piece_factory::_ptce_piece_factory(void) :
			m_initialized(false)
		{
			TRACE_ENTRY();

			std::atexit(ptce_piece_factory_destroy);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_piece_factory::~_ptce_piece_factory(void)
		{
			TRACE_ENTRY();

			if(m_initialized) {
				destroy();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_piece_factory_ptr 
		_ptce_piece_factory::acquire(void)
		{
			ptce_piece_factory_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				m_instance = new ptce_piece_factory();
				if(!m_instance) {
					THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0x%p", result);
			return result;
		}

		bool 
		_ptce_piece_factory::contains(
			__in const ptce_uid &uid
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			result = (m_piece_map.find(uid) != m_piece_map.end());

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool
		_ptce_piece_factory::contains(
			__in const ptce_piece &piece
			)
		{
			return contains(piece.m_uid);
		}

		size_t 
		_ptce_piece_factory::decrement_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result = 0;
			std::map<ptce_uid, std::pair<ptce_piece, size_t>>::iterator piece_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			piece_iter = find_piece(uid);

			if(piece_iter->second.second == PTCE_INIT_REF_DEF) {
				m_piece_map.erase(piece_iter);
			} else {
				result = --piece_iter->second.second;
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_piece_factory::decrement_reference(
			__in const ptce_piece &piece
			)
		{
			return decrement_reference(piece.m_uid);
		}

		void 
		_ptce_piece_factory::destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			m_piece_map.clear();
			m_initialized = false;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		std::map<ptce_uid, std::pair<ptce_piece, size_t>>::iterator 
		_ptce_piece_factory::find_piece(
			__in const ptce_uid &uid
			)
		{
			std::map<ptce_uid, std::pair<ptce_piece, size_t>>::iterator result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			result = m_piece_map.find(uid);
			if(result == m_piece_map.end()) {
				THROW_PTCE_PIECE_EXCEPTION_MESSAGE(PTCE_PIECE_EXCEPTION_UNKNOWN_PIECE,
					"%s", ptce_uid::id_as_string(uid).c_str());
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result;
		}

		ptce_piece &
		_ptce_piece_factory::generate(
			__in ptce_piece_t type,
			__in ptce_piece_col_t color,
			__in_opt bool moved
			)
		{
			ptce_piece piece;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			if(type > PIECE_TYPE_MAX) {
				THROW_PTCE_PIECE_EXCEPTION_MESSAGE(PTCE_PIECE_EXCEPTION_INVALID_TYPE,
					"%lu (must be at most %lu)", type, PIECE_TYPE_MAX);
			}

			if(color > PIECE_COLOR_MAX) {
				THROW_PTCE_PIECE_EXCEPTION_MESSAGE(PTCE_PIECE_EXCEPTION_INVALID_COLOR,
					"%lu (must be at most %lu)", color, PIECE_COLOR_MAX);
			}

			if(contains(piece.id())) {
				THROW_PTCE_PIECE_EXCEPTION_MESSAGE(PTCE_PIECE_EXCEPTION_ALREADY_EXISTS,
					"%s", piece.id().to_string().c_str());
			}

			piece = ptce_piece(type, color, moved);
			m_piece_map.insert(std::pair<ptce_uid, std::pair<ptce_piece, size_t>>(piece.id(), 
					std::pair<ptce_piece, size_t>(piece, PTCE_INIT_REF_DEF)));

			TRACE_EXIT("Return Value: 0x%x", 0);
			return find_piece(piece.id())->second.first;
		}

		size_t 
		_ptce_piece_factory::increment_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			result = ++find_piece(uid)->second.second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_piece_factory::increment_reference(
			__in const ptce_piece &piece
			)
		{
			return increment_reference(piece.m_uid);
		}

		void 
		_ptce_piece_factory::initialize(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_INITIALIZED);
			}

			m_piece_map.clear();
			m_initialized = true;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_piece_factory::is_allocated(void)
		{
			bool result;

			TRACE_ENTRY();

			result = (m_instance != NULL);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_piece_factory::is_initialized(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_initialized);
			return m_initialized;
		}

		size_t 
		_ptce_piece_factory::reference_count(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			result = find_piece(uid)->second.second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_piece_factory::reference_count(
			__in const ptce_piece &piece
			)
		{
			return reference_count(piece.m_uid);
		}

		size_t 
		_ptce_piece_factory::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_PIECE_EXCEPTION(PTCE_PIECE_EXCEPTION_UNINITIALIZED);
			}

			result = m_piece_map.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string 
		_ptce_piece_factory::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<ptce_uid, std::pair<ptce_piece, size_t>>::iterator piece_iter;
	
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << PTCE_PIECE_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance) 
					<< ", Initialized=" << m_initialized << ", Count=" << m_piece_map.size();

			if(verbose) {

				for(piece_iter = m_piece_map.begin(); piece_iter != m_piece_map.end(); ++piece_iter) {
					result << std::endl << " --- " << ptce_piece::piece_as_string(piece_iter->second.first)
						<< " (" << piece_iter->second.second << ")";
				}
			}
		
			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
