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

#include <cstring>
#include <arpa/inet.h>
#include "../include/ptce.h"
#include "../include/ptce_game_type.h"

namespace PTCE_NS {

	namespace PTCE_NET_NS {

		_ptce_game::_ptce_game(
			__in const sockaddr_t &information,
			__in int socket
			) :
				m_information(information),
				m_socket(socket)
		{
			TRACE_ENTRY();

			m_board.clear();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_game::_ptce_game(
			__in const _ptce_game &other
			) :
				ptce_uid_base(other),
				m_board(other.m_board),
				m_information(other.m_information),
				m_socket(other.m_socket)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_game::~_ptce_game(void)
		{
			TRACE_ENTRY();

			m_board.clear();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_game &
		_ptce_game::operator=(
			__in const _ptce_game &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				ptce_uid_base::operator=(other);
				m_board = other.m_board;
				m_information = other.m_information;
				m_socket = other.m_socket;
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		ptce_board &
		_ptce_game::board(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_board;
		}

		std::string 
		_ptce_game::game_as_string(
			__in const _ptce_game &game,
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			char addr[INET_ADDRSTRLEN];

			TRACE_ENTRY();
			
			memset(addr, 0, sizeof(char) * INET_ADDRSTRLEN);
			inet_ntop(AF_INET, &(game.m_information.sin_addr), addr, INET_ADDRSTRLEN);
			result << ptce_uid::id_as_string(game.m_uid) << ": Client: " << addr << ", Socket: " 
					<< game.m_socket << std::endl << ptce_board::board_as_string(game.m_board, verbose);

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		ptce_board_mv_t 
		_ptce_game::generate_move(void)
		{
			ptce_board_mv_t result = BOARD_CONTINUE;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			// TODO: handle game move

			TRACE_EXIT("Return Value: %s (0x%x)", BOARD_TYPE_STRING(result), result);
			return result;
		}

		sockaddr_t 
		_ptce_game::information(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_information;
		}

		int 
		_ptce_game::socket(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%04x", m_socket);
			return m_socket;
		}

		std::string 
		_ptce_game::to_string(
			__in_opt bool verbose
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return game_as_string(*this, verbose);
		}

		ptce_game_manager_ptr ptce_game_manager::m_instance = NULL;

		void 
		ptce_game_manager_destroy(void)
		{
			TRACE_ENTRY();

			if(ptce_game_manager::m_instance) {
				delete ptce_game_manager::m_instance;
				ptce_game_manager::m_instance = NULL;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_game_manager::_ptce_game_manager(void) :
			m_connections(0),
			m_initialized(false),
			m_port(0)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_game_manager::~_ptce_game_manager(void)
		{
			TRACE_ENTRY();

			if(m_initialized) {
				destroy();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_game_manager_ptr 
		_ptce_game_manager::acquire(void)
		{
			ptce_game_manager_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				result = new ptce_game_manager;
				if(!result) {
					THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0x%p", result);
			return result;
		}

		uint8_t 
		_ptce_game_manager::connections(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %lu", m_connections);
			return m_connections;
		}

		void 
		_ptce_game_manager::destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_UNINITIALIZED);
			}

			// TODO: kill all threads and stop server

			m_port = 0;
			m_connections = 0;
			m_initialized = true;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_game_manager::initialize(
			__in_opt uint16_t port,
			__in_opt uint8_t connections
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_INITIALIZED);
			}

			m_port = port;
			m_connections = connections;

			// TODO: start server on port w/ connection count

			m_initialized = true;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_game_manager::is_allocated(void)
		{
			bool result;

			TRACE_ENTRY();

			result = (m_instance != NULL);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_game_manager::is_initialized(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_initialized);
			return m_initialized;
		}

		uint16_t 
		_ptce_game_manager::port(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_UNINITIALIZED);
			}

			TRACE_EXIT("Return Value: 0x%04x", m_port);
			return m_port;
		}

		size_t 
		_ptce_game_manager::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_UNINITIALIZED);
			}

			result = m_game_map.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string 
		_ptce_game_manager::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<ptce_uid, std::thread>::iterator game_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << PTCE_GAME_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance) 
					<< ", Initialized=" << m_initialized << ", Count=" << m_game_map.size();

			if(verbose) {

				for(game_iter = m_game_map.begin(); game_iter != m_game_map.end(); ++game_iter) {
					result << std::endl << " --- (" << ptce_uid::id_as_string(game_iter->first) << ") Thread=" 
							<< game_iter->second.get_id();
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}