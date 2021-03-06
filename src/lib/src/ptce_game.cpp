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
#include <ctime>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../include/ptce.h"
#include "../include/ptce_game_type.h"

namespace PTCE_NS {

	namespace PTCE_NET_NS {

		#define CLIENT_DATA_LEN_MAX 0x200
		#define CLIENT_MESSAGE "You are now playing against Pale Turquoise " VERSION_STR

		typedef struct sockaddr_in sockaddr_t;

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
			m_port(0),
			m_started(false)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_game_manager::~_ptce_game_manager(void)
		{
			TRACE_ENTRY();

			if(m_started) {
				stop();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_game_manager_ptr 
		_ptce_game_manager::acquire(void)
		{
			ptce_game_manager_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				m_instance = new ptce_game_manager();
				if(!m_instance) {
					THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0x%p", result);
			return result;
		}

		void 
		_ptce_game_manager::client_game_handler(
			__in const ptce_uid uid,
			__in const sockaddr_t info_serv,
			__in const sockaddr_t info_cli,
			__in const socklen_t length,
			__in int socket,
			__in_opt bool verbose,
			__in_opt bool show_board,
			__in_opt bool show_network
			)
		{
			int cli_data_len;
			std::stringstream message;
			uint8_t cli_data[CLIENT_DATA_LEN_MAX];
			ptce_board_mv_t move = BOARD_CONTINUE;
			ptce_board_factory_ptr board_fact = NULL;
			bool active_cli = true, addr_cli_known = false;
			std::map<ptce_uid, std::thread>::iterator game_iter;
			char addr_cli_host_buf[NI_MAXHOST], addr_cli_port_buf[NI_MAXSERV];

			TRACE_ENTRY();

			if(verbose) {
				memset(addr_cli_host_buf, 0, sizeof(char) * NI_MAXHOST);
				memset(addr_cli_port_buf, 0, sizeof(char) * NI_MAXSERV);
				std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) << " Client connected";

				if(!getnameinfo((struct sockaddr *) &info_cli, length, 
						addr_cli_host_buf, sizeof(char) * NI_MAXHOST, 
						addr_cli_port_buf, sizeof(char) * NI_MAXSERV, 
						NI_NUMERICHOST | NI_NUMERICSERV)) {
					addr_cli_known = true;
					std::cout << " (Host: " << addr_cli_host_buf << ", Port: " << addr_cli_port_buf 
							<< ")";
				}

				std::cout << std::endl;
			}

			try {
				board_fact = ptce::acquire()->acquire_board_factory();
				ptce_board &board = board_fact->generate();
				message << CLIENT_MESSAGE << " (Id: " << ptce_uid::id_as_string(uid) << ", Host: " << addr_cli_host_buf 
						<< ", Port: " << addr_cli_port_buf << ")" << std::endl;
				client_write(uid, (uint8_t *) message.str().c_str(), message.str().size(), addr_cli_host_buf, addr_cli_port_buf, 
						socket, verbose, show_network);

				while(active_cli) {

					if(show_board) {
						std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) << " " 
								<< board.to_string(true) << std::endl;
					}

					move = board.is_checkmated(PIECE_BLACK) ? BOARD_CHECKMATE : generate_move(board);

					if(show_board) {
						std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) << " " 
								<< board.to_string(true) << std::endl;
					}

					switch(move) {
						case BOARD_CONTINUE:
						case BOARD_CHECKMATE:
						case BOARD_DRAW:

							if(verbose) {
								std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
										<< " Sending " << BOARD_MOVE_STRING(move) << " to client (Host: " 
										<< addr_cli_host_buf << ", Port: " << addr_cli_port_buf << ")"
										<< std::endl;
							}
							break;
						default:
							THROW_PTCE_GAME_EXCEPTION_MESSAGE(PTCE_GAME_EXCEPTION_UNKNOWN_MOVE_TYPE,
								"id=%s, type=%lu", ptce_uid::id_as_string(uid).c_str(), move);
					}

					message.clear();
					message.str(std::string());
					message << board.serialize(move) << std::endl;
					client_write(uid, (uint8_t *) message.str().c_str(), message.str().size(), addr_cli_host_buf, addr_cli_port_buf, 
							socket, verbose, show_network);

					if(move != BOARD_CONTINUE) {
						break;
					}

					memset(cli_data, 0, sizeof(uint8_t) * CLIENT_DATA_LEN_MAX);
					cli_data_len = client_read(uid, cli_data, sizeof(uint8_t) * CLIENT_DATA_LEN_MAX, addr_cli_host_buf,
							addr_cli_port_buf, socket, verbose, show_network);

					if(cli_data_len > 1) {

						move = board.unserialize((char *) cli_data);
						switch(move) {
							case BOARD_CHECKMATE:
							case BOARD_DRAW:
							case BOARD_RESIGN:
							case BOARD_SAVE:
								active_cli = false;
								break;
							case BOARD_CONTINUE:
								break;
							default:
								THROW_PTCE_GAME_EXCEPTION_MESSAGE(PTCE_GAME_EXCEPTION_UNKNOWN_MOVE_TYPE,
									"id=%s, type=%lu", ptce_uid::id_as_string(uid).c_str(), move);
						}

						if(verbose) {
							std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
									<< " Received " << BOARD_MOVE_STRING(move) << " from client (Host: " 
									<< addr_cli_host_buf << ", Port: " << addr_cli_port_buf << ")" 
									<< std::endl;
						}
					} else {

						if(verbose) {
							std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
									<< " Received an empty game board from client (Host: " 
									<< addr_cli_host_buf << ", Port: " << addr_cli_port_buf << ")"
									<< std::endl;
						}

						break;
					}
				}

				board_fact->decrement_reference(board);
			} catch(std::runtime_error &exc) {

				if(verbose) {
					std::cerr << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
							<< " Client connection loop failure: " << exc.what() << std::endl;
				}
			}

			close(socket);

			if(verbose) {
				std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
						<< " Client disconnected";

				if(addr_cli_known) {
					std::cout << " (Host: " << addr_cli_host_buf << ", Port: " << addr_cli_port_buf 
							<< ")";
				}

				std::cout << std::endl;
			}

			if(m_started) {

				for(game_iter = m_game_map.begin(); game_iter != m_game_map.end(); ++game_iter) {

					if(game_iter->first == uid) {
						ptce_uid_base thread_id(game_iter->first);
						thread_id.decrement_reference();
						m_game_map.erase(game_iter);
						break;
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		int 
		_ptce_game_manager::client_read(
			__in const ptce_uid &uid,
			__in uint8_t *data,
			__in size_t length,
			__in char *addr_host,
			__in char *addr_port,
			__in int socket,
			__in_opt bool verbose,
			__in_opt bool show_network
			)
		{
			int result = 0;
			size_t iter = 0;
			std::string bin_str;

			TRACE_ENTRY();

			if((!data && length) || (data && !length) || !addr_host || !addr_port) {
				THROW_PTCE_GAME_EXCEPTION_MESSAGE(PTCE_GAME_EXCEPTION_INVALID_IO_PARAMETER,
					"Data: 0x%p, Length: %lu, Host addr: 0x%p, Port addr: 0x%p",
					data, length, addr_host, addr_port);
			}

			memset(data, 0, length);

			if(verbose) {
				std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
						<< " Server attempting to read data from client (Host: " 
						<< addr_host << ", Port: " << addr_port << ")... ";
			}

			result = read(socket, data, length);
			if(result < 0) {

				if(verbose) {
					std::cout << "Failure!" << std::endl << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
						<< " Client read failed (Host: " << addr_host << ", Port: " << addr_port << "): " 
						<< strerror(errno) << std::endl;
				}
			} else if(verbose){
				std::cout << "Success." << std::endl;
			}

			if(show_network && (result >= 0)) {
				std::cout << std::endl << "\tData length: " << std::setprecision(4) << (length / BYTES_PER_KBYTE) 
						<< " KB (" << length << " bytes)";

				for(iter = 0; iter < length; ++iter) {

					if(!(iter % BLOCK_LEN)) {

						if(iter && !bin_str.empty()) {
							std::cout << " | " << bin_str;
							bin_str.clear();
						}

						std::cout << std::endl << "\t0x" << VALUE_AS_HEX(uint16_t, iter) << " |";
					}

					std::cout << " " << VALUE_AS_HEX(uint8_t, data[iter]);
					bin_str += isprint((char) data[iter]) ? (char) data[iter] : '.';
				}

				if(!bin_str.empty()) {

					if(length % BLOCK_LEN) {

						for(iter = 0; iter < BLOCK_LEN - (length % BLOCK_LEN); ++iter) {
							std::cout << "   ";
						}
					}

					std::cout << " | " << bin_str;
					bin_str.clear();
				}

				std::cout << std::endl;
			}

			TRACE_EXIT("Return Value: %.02f KB (%lu bytes)", result / BYTES_PER_KBYTE, result);
			return result;
		}

		bool 
		_ptce_game_manager::client_write(
			__in const ptce_uid &uid,
			__in uint8_t *data,
			__in size_t length,
			__in char *addr_host,
			__in char *addr_port,
			__in int socket,
			__in_opt bool verbose,
			__in_opt bool show_network
			)
		{
			size_t iter;
			bool result = true;
			std::string bin_str;			

			TRACE_ENTRY();

			if((!data && length) || (data && !length) || !addr_host || !addr_port) {
				THROW_PTCE_GAME_EXCEPTION_MESSAGE(PTCE_GAME_EXCEPTION_INVALID_IO_PARAMETER,
					"Data: 0x%p, Length: %lu, Host addr: 0x%p, Port addr: 0x%p",
					data, length, addr_host, addr_port);
			}

			if(verbose) {
				std::cout << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
						<< " Server attempting to write data to client (Host: " 
						<< addr_host << ", Port: " << addr_port << ")";
			}

			if(show_network) {
				std::cout << std::endl << "\tData length: " << std::setprecision(4) << (length / BYTES_PER_KBYTE) 
						<< " KB (" << length << " bytes)";

				for(iter = 0; iter < length; ++iter) {

					if(!(iter % BLOCK_LEN)) {

						if(iter && !bin_str.empty()) {
							std::cout << " | " << bin_str;
							bin_str.clear();
						}

						std::cout << std::endl << "\t0x" << VALUE_AS_HEX(uint16_t, iter) << " |";
					}

					std::cout << " " << VALUE_AS_HEX(uint8_t, data[iter]);
					bin_str += isprint((char) data[iter]) ? (char) data[iter] : '.';
				}

				if(!bin_str.empty()) {

					if(length % BLOCK_LEN) {

						for(iter = 0; iter < BLOCK_LEN - (length % BLOCK_LEN); ++iter) {
							std::cout << "   ";
						}
					}

					std::cout << " | " << bin_str;
					bin_str.clear();
				}

				std::cout << std::endl;
			}

			if(verbose) {
				std::cout << "... ";
			}

			if(write(socket, data, length) < 0) {

				if(verbose) {
					std::cout << "Failure!" << std::endl << "[" << time_stamp() << "] " << ptce_uid::id_as_string(uid) 
						<< " Client write failed (Host: " << addr_host << ", Port: " << addr_port << "): " 
						<< strerror(errno) << std::endl;
				}

				result = false;
			} else if(verbose){
				std::cout << "Success." << std::endl;
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		uint8_t 
		_ptce_game_manager::connections(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_started) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_STOPPED);
			}

			TRACE_EXIT("Return Value: %lu", m_connections);
			return m_connections;
		}

		ptce_board_mv_t 
		_ptce_game_manager::generate_move(
			__in ptce_board &board,
			__in_opt ptce_piece_col_t enemy_color
			)
		{	
			int offset;
			ptce_piece curr_piece;
			bool enemy_checked = false;
			size_t max_score, x, y = 0;
			ptce_board_mv_t result = BOARD_CONTINUE;
			std::set<ptce_mv_ent_t>::iterator move_iter;
			std::set<ptce_mv_ent_t> final_move_set, move_set;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>>::iterator pos_iter;			
			std::set<std::pair<ptce_mv_ent_t, size_t>>::iterator score_iter;
			std::set<std::pair<ptce_mv_ent_t, size_t>> final_score_set, score_set;

			TRACE_ENTRY();

			for(; y < BOARD_WID; ++y) {

				for(x = 0; x < BOARD_WID; ++x) {

					curr_piece = board.piece(ptce_pos_t(x, y));
					if((curr_piece.type() != PIECE_EMPTY)
							&& (curr_piece.color() != enemy_color)) {
						move_set = board.generate_move_set(ptce_pos_t(x, y), enemy_color);
						max_score = ptce_board::score_move_set(board, curr_piece.type(), move_set, score_set);

						for(score_iter = score_set.begin(); score_iter != score_set.end(); ++score_iter) {

							if((score_iter->second == max_score)
									&& (score_iter->first.first != MOVE_INVALID) 
									&& (score_iter->first.first != MOVE_PROTECT)) {

								if(score_iter->first.first == MOVE_CHECK) {
									enemy_checked = true;
									goto check_found;
								}

								final_score_set.insert(std::pair<ptce_mv_ent_t, size_t>
										(score_iter->first, score_iter->second));
							}
						}
					}
				}
			}

		check_found:

			if(final_score_set.empty()) {
				result = BOARD_DRAW;
			} else if(enemy_checked) {
				result = BOARD_CHECKMATE;
			} else {
				max_score = 0;

				for(score_iter = final_score_set.begin();
						score_iter != final_score_set.end(); ++score_iter) {

					if(score_iter->second >= max_score) {
						final_move_set.insert(score_iter->first);
						max_score = score_iter->second;
					}
				}

				move_iter = final_move_set.begin();
				offset = m_distribution(m_generator) % final_move_set.size();

				std::cout << final_move_set.size() << ", " << offset << std::endl;

				while(offset--) {
					++move_iter;
				}

				for(pos_iter = move_iter->second.begin(); 
						pos_iter != move_iter->second.end(); ++pos_iter) {
					board.move(pos_iter->first, pos_iter->second);
				}
			}

			TRACE_EXIT("Return Value: %s (0x%x)", BOARD_MOVE_STRING(result), result);
			return result;
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
		_ptce_game_manager::is_started(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_started);
			return m_started;
		}

		uint16_t 
		_ptce_game_manager::port(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_started) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_STOPPED);
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

			if(!m_started) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_STOPPED);
			}

			result = m_game_map.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		void 
		_ptce_game_manager::start(
			__in_opt uint16_t port,
			__in_opt uint8_t connections,
			__in_opt bool verbose,
			__in_opt bool show_board,
			__in_opt bool show_network
			)
		{
			socklen_t len_cli;
			int sock_cli, sock_serv;
			sockaddr_t addr_cli, addr_serv;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_started) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_STARTED);
			}

			m_generator.seed(std::time(NULL));

			m_port = port;
			m_connections = connections;

			if(verbose) {
				std::cout << "[" << time_stamp() << "] ***SERVER STARTING***" << std::endl << "[" 
						<< time_stamp() << "] Opening socket... ";
			}

			sock_serv = socket(AF_INET, SOCK_STREAM, 0);
			if(sock_serv < 0) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_SOCKET_FAILED);
			}

			if(verbose) {
				std::cout << "Done." << std::endl;
			}

			memset(&addr_serv, 0, sizeof(sockaddr_t));
			addr_serv.sin_family = AF_INET;
			addr_serv.sin_addr.s_addr = INADDR_ANY;
			addr_serv.sin_port = htons(m_port);

			if(verbose) {
				std::cout << "[" << time_stamp() << "] Binding to port " << m_port << "... ";
			}

			if(bind(sock_serv, (struct sockaddr *) &addr_serv, sizeof(sockaddr_t)) < 0) {
				THROW_PTCE_GAME_EXCEPTION_MESSAGE(PTCE_GAME_EXCEPTION_BIND_FAILED,
					"%i", m_port);
			}

			if(verbose) {
				std::cout << "Done." << std::endl << "[" << time_stamp() << "] ***SERVER STARTED***" << std::endl;
			}

			m_started = true;
			listen(sock_serv, m_connections);

			if(verbose) {
				std::cout << "[" << time_stamp() << "] Listening for client connections (Max connections: " 
						<< (int) m_connections << ")..." << std::endl;
			}

			for(;;) {
				len_cli = sizeof(addr_cli);

				sock_cli = accept(sock_serv, (struct sockaddr *) &addr_cli, &len_cli);
				if(sock_cli < 0) {
					std::cerr << "[" << time_stamp() << "] " 
						<< PTCE_GAME_EXCEPTION_STRING(PTCE_GAME_EXCEPTION_ACCEPT_FAILED) << std::endl;
				}

				ptce_uid_base cli_thread_id;
				cli_thread_id.increment_reference();
				m_game_map.insert(std::pair<ptce_uid, std::thread>(cli_thread_id.id(), 
						std::thread(&ptce_game_manager::client_game_handler, 
						this, cli_thread_id.id(), addr_serv, addr_cli, len_cli, sock_cli, verbose, 
						show_board, show_network)));
				m_game_map.find(cli_thread_id.id())->second.detach();
			}

			if(verbose) {
				std::cout << "[" << time_stamp() << "] Closing socket... ";
			}

			close(sock_serv);

			if(verbose) {
				std::cout << "Done." << std::endl;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_game_manager::stop(
			__in_opt bool verbose
			)
		{
			std::map<ptce_uid, std::thread>::iterator game_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_started) {
				THROW_PTCE_GAME_EXCEPTION(PTCE_GAME_EXCEPTION_STOPPED);
			}

			if(verbose) {
				std::cout << "[" << time_stamp() << "] ***SERVER STOPPING***" << std::endl;
			}

			m_started = false;

			for(game_iter = m_game_map.begin(); game_iter != m_game_map.end(); ++game_iter) {

				if(game_iter->second.joinable()) {
					game_iter->second.join();
				}

				ptce_uid_base thread_id(game_iter->first);
				thread_id.decrement_reference();
			}

			m_game_map.clear();
			m_port = 0;
			m_connections = 0;

			if(verbose) {
				std::cout << "[" << time_stamp() << "] ***SERVER STOPPED***" << std::endl;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
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
					<< ", Started=" << m_started << ", Count=" << m_game_map.size();

			if(verbose) {

				for(game_iter = m_game_map.begin(); game_iter != m_game_map.end(); ++game_iter) {
					result << std::endl << " --- (" << ptce_uid::id_as_string(game_iter->first)
							<< ") Thread=" << game_iter->second.get_id();
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
