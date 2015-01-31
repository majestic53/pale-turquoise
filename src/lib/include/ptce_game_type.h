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

#ifndef PTCE_GAME_TYPE_H_
#define PTCE_GAME_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_NET_NS {

		#ifndef NDEBUG
		#define PTCE_GAME_HEADER "(GAME)"
		#else
		#define PTCE_GAME_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_GAME_TRACE_HEADER "(GAME)"

		enum {
			PTCE_GAME_EXCEPTION_ACCEPT_FAILED = 0,
			PTCE_GAME_EXCEPTION_ACQUIRE_FAILED,
			PTCE_GAME_EXCEPTION_BIND_FAILED,
			PTCE_GAME_EXCEPTION_SOCKET_FAILED,
			PTCE_GAME_EXCEPTION_STARTED,
			PTCE_GAME_EXCEPTION_STOPPED,
		};

		#define PTCE_GAME_EXCEPTION_MAX PTCE_GAME_EXCEPTION_STOPPED

		static const std::string PTCE_GAME_EXCEPTION_STR[] = {
			PTCE_GAME_HEADER " Failed to accept client connection",
			PTCE_GAME_HEADER " Failed to acquire game manager",
			PTCE_GAME_HEADER " Failed to bind to port",
			PTCE_GAME_HEADER " Failed to create socket",
			PTCE_GAME_HEADER " Game manager is already started",
			PTCE_GAME_HEADER " Game manager is stopped",
			};

		#define PTCE_GAME_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_GAME_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_GAME_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_GAME_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_GAME_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_GAME_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_GAME_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_game;
		typedef _ptce_game ptce_game, *ptce_game_ptr;

		class _ptce_game_manager;
		typedef _ptce_game_manager ptce_game_manager, *ptce_game_manager_ptr;
	}
}

#endif // PTCE_GAME_TYPE_H_
