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

#ifndef PTCE_GAME_H_
#define PTCE_GAME_H_

#include <random>
#include <netinet/in.h>

namespace PTCE_NS {

	using namespace PTCE_NS::PTCE_COMP_NS;

	namespace PTCE_NET_NS {

		#define GAME_CONNECTION_DEF 5
		#define GAME_PORT_DEF 2000

		typedef struct sockaddr_in sockaddr_t;

		void ptce_game_manager_destroy(void);

		typedef class _ptce_game_manager {

			public:

				~_ptce_game_manager(void);

				static _ptce_game_manager *acquire(void);

				uint8_t connections(void);

				static bool is_allocated(void);

				bool is_started(void);

				uint16_t port(void);

				size_t size(void);

				void start(
					__in_opt uint16_t port = GAME_PORT_DEF,
					__in_opt uint8_t connections = GAME_CONNECTION_DEF,
					__in_opt bool verbose = false,
					__in_opt bool show_board = false,
					__in_opt bool show_network = false
					);

				void stop(
					__in_opt bool verbose = false
					);

				std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend void ptce_game_manager_destroy(void);

				_ptce_game_manager(void);

				_ptce_game_manager(
					__in const _ptce_game_manager &other
					);

				_ptce_game_manager &operator=(
					__in const _ptce_game_manager &other
					);			

				void client_game_handler(
					__in const ptce_uid uid,
					__in const sockaddr_t info_serv,
					__in const sockaddr_t info_cli,
					__in const socklen_t length,
					__in int socket,
					__in_opt bool verbose = false,
					__in_opt bool show_board = false,
					__in_opt bool show_network = false
					);

				int client_read(
					__in const ptce_uid &uid,
					__in uint8_t *data,
					__in size_t length,
					__in char *addr_host,
					__in char *addr_port,
					__in int socket,
					__in_opt bool verbose = false,
					__in_opt bool show_network = false
					);

				bool client_write(
					__in const ptce_uid &uid,
					__in uint8_t *data,
					__in size_t length,
					__in char *addr_host,
					__in char *addr_port,
					__in int socket,
					__in_opt bool verbose = false,
					__in_opt bool show_network = false
					);

				ptce_board_mv_t generate_move(
					__in ptce_board &board,
					__in_opt ptce_piece_col_t enemy_color = PIECE_BLACK
					);

				uint8_t m_connections;

				std::uniform_int_distribution<uint32_t> m_distribution;

				std::map<ptce_uid, std::thread> m_game_map;

				std::default_random_engine m_generator;

				static _ptce_game_manager *m_instance;

				uint16_t m_port;

				bool m_started;

			private:

				std::recursive_mutex m_lock;

		} ptce_game_manager, *ptce_game_manager_ptr;
	}
}

#endif // PTCE_GAME_H_
