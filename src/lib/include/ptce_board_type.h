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

#ifndef PTCE_BOARD_TYPE_H_
#define PTCE_BOARD_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		#ifndef NDEBUG
		#define PTCE_BOARD_HEADER "(BOARD)"
		#else
		#define PTCE_BOARD_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_NODE_TRACE_HEADER "(BOARD)"

		enum {
			PTCE_BOARD_EXCEPTION_ACQUIRE_FAILED = 0,
			PTCE_BOARD_EXCEPTION_ALREADY_EXISTS,
			PTCE_BOARD_EXCEPTION_INITIALIZED,
			PTCE_BOARD_EXCEPTION_UNINITIALIZED,
			PTCE_BOARD_EXCEPTION_UNKNOWN_BOARD,
		};

		#define PTCE_BOARD_EXCEPTION_MAX PTCE_BOARD_EXCEPTION_UNKNOWN_BOARD

		static const std::string PTCE_BOARD_EXCEPTION_STR[] = {
			PTCE_BOARD_HEADER "Failed to acquire board factory",
			PTCE_BOARD_HEADER "Board already exists",
			PTCE_BOARD_HEADER "Board factory is already initalized",
			PTCE_BOARD_HEADER "Board factory is uninitialized",
			PTCE_BOARD_HEADER "Board does not exist",
			};

		#define PTCE_BOARD_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_BOARD_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_BOARD_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_BOARD_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_BOARD_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_BOARD_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_BOARD_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_board;
		typedef _ptce_board ptce_board, *ptce_board_ptr;

		class _ptce_board_factory;
		typedef _ptce_board_factory ptce_board_factory, *ptce_board_factory_ptr;
	}
}

#endif // PTCE_BOARD_TYPE_H_
