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

#ifndef PTCE_TEST_GAME_H_
#define PTCE_TEST_GAME_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define PTCE_TEST_GAME_TRACE_HEADER "(GAME)"

		enum {
			PTCE_TEST_GAME_ASSIGNMENT = 0,
			PTCE_TEST_GAME_CONSTRUCTOR,
			PTCE_TEST_GAME_BOARD,
			PTCE_TEST_GAME_GENERATE_MOVE,
			PTCE_TEST_GAME_INFORMATION,
			PTCE_TEST_GAME_MANAGER_ACQUIRE,
			PTCE_TEST_GAME_MANAGER_CONNECTIONS,
			PTCE_TEST_GAME_MANAGER_DESTROY,
			PTCE_TEST_GAME_MANAGER_INITIALIZE,
			PTCE_TEST_GAME_MANAGER_IS_ALLOCATED,
			PTCE_TEST_GAME_MANAGER_IS_INITIALIZED,
			PTCE_TEST_GAME_MANAGER_PORT,
			PTCE_TEST_GAME_MANAGER_SIZE,
			PTCE_TEST_GAME_SOCKET,
		};

		#define PTCE_TEST_GAME_MAX PTCE_TEST_GAME_SOCKET

		static const std::string PTCE_TEST_GAME_STR[] = {
			"PTCE_TEST_GAME_ASSIGNMENT",
			"PTCE_TEST_GAME_CONSTRUCTOR",
			"PTCE_TEST_GAME_BOARD",
			"PTCE_TEST_GAME_GENERATE_MOVE",
			"PTCE_TEST_GAME_INFORMATION",
			"PTCE_TEST_GAME_MANAGER_ACQUIRE",
			"PTCE_TEST_GAME_MANAGER_CONNECTIONS",
			"PTCE_TEST_GAME_MANAGER_DESTROY",
			"PTCE_TEST_GAME_MANAGER_INITIALIZE",
			"PTCE_TEST_GAME_MANAGER_IS_ALLOCATED",
			"PTCE_TEST_GAME_MANAGER_IS_INITIALIZED",
			"PTCE_TEST_GAME_MANAGER_PORT",
			"PTCE_TEST_GAME_MANAGER_SIZE",
			"PTCE_TEST_GAME_SOCKET",
			};

		#define PTCE_TEST_GAME_STRING(_TYPE_) \
			((_TYPE_) > PTCE_TEST_GAME_MAX ? UNKNOWN : \
			PTCE_TEST_GAME_STR[_TYPE_].c_str())

		extern ptce_test_t ptce_test_game_assignment(void);
		
		extern ptce_test_t ptce_test_game_constructor(void);

		extern ptce_test_t ptce_test_game_board(void);

		extern ptce_test_t ptce_test_game_generate_move(void);

		extern ptce_test_t ptce_test_game_information(void);

		extern ptce_test_t ptce_test_game_manager_acquire(void);

		extern ptce_test_t ptce_test_game_manager_connections(void);

		extern ptce_test_t ptce_test_game_manager_destroy(void);

		extern ptce_test_t ptce_test_game_manager_initialize(void);

		extern ptce_test_t ptce_test_game_manager_is_allocated(void);

		extern ptce_test_t ptce_test_game_manager_is_initialized(void);

		extern ptce_test_t ptce_test_game_manager_port(void);

		extern ptce_test_t ptce_test_game_manager_size(void);

		extern ptce_test_t ptce_test_game_socket(void);

		static const ptce_test_set_cb PTCE_TEST_GAME_CB[] = {
			ptce_test_game_assignment,
			ptce_test_game_constructor,
			ptce_test_game_board,
			ptce_test_game_generate_move,
			ptce_test_game_information,
			ptce_test_game_manager_acquire,
			ptce_test_game_manager_connections,
			ptce_test_game_manager_destroy,
			ptce_test_game_manager_initialize,
			ptce_test_game_manager_is_allocated,
			ptce_test_game_manager_is_initialized,
			ptce_test_game_manager_port,
			ptce_test_game_manager_size,
			ptce_test_game_socket,
			};

		#define PTCE_TEST_GAME_CALLBACK(_TYPE_) \
			((_TYPE_) > PTCE_TEST_GAME_MAX ? NULL : \
			PTCE_TEST_GAME_CB[_TYPE_])
	}
}

#endif // PTCE_TEST_GAME_H_
