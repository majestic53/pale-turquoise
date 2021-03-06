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

		#define PTCE_BOARD_TRACE_HEADER "(BOARD)"

		enum {
			PTCE_BOARD_EXCEPTION_ACQUIRE_FAILED = 0,
			PTCE_BOARD_EXCEPTION_ACQUIRE_PIECE_FACTORY_FAILED,
			PTCE_BOARD_EXCEPTION_ALREADY_EXISTS,
			PTCE_BOARD_EXCEPTION_EMPTY_SERIALIZATION,
			PTCE_BOARD_EXCEPTION_INITIALIZED,
			PTCE_BOARD_EXCEPTION_INVALID_PIECE_COLOR,
			PTCE_BOARD_EXCEPTION_INVALID_PIECE_TYPE,
			PTCE_BOARD_EXCEPTION_INVALID_POSITION,
			PTCE_BOARD_EXCEPTION_INVALID_STATE,
			PTCE_BOARD_EXCEPTION_INVALID_TYPE,
			PTCE_BOARD_EXCEPTION_KING_NOT_FOUND,
			PTCE_BOARD_EXCEPTION_MALFORMED_SERIALIZATION,
			PTCE_BOARD_EXCEPTION_PIECE_ALREADY_EXISTS,
			PTCE_BOARD_EXCEPTION_UNINITIALIZED,
			PTCE_BOARD_EXCEPTION_UNKNOWN_BOARD,
			PTCE_BOARD_EXCEPTION_UNKNOWN_BOARD_COMMAND,
			PTCE_BOARD_EXCEPTION_UNKNOWN_PIECE_TYPE,
		};

		#define PTCE_BOARD_EXCEPTION_MAX PTCE_BOARD_EXCEPTION_UNKNOWN_PIECE_TYPE

		static const std::string PTCE_BOARD_EXCEPTION_STR[] = {
			PTCE_BOARD_HEADER " Failed to acquire board factory",
			PTCE_BOARD_HEADER " Failed to acquire piece factory",
			PTCE_BOARD_HEADER " Board already exists",
			PTCE_BOARD_HEADER " Empty serialization",
			PTCE_BOARD_HEADER " Board factory is already initalized",
			PTCE_BOARD_HEADER " Invalid piece color",
			PTCE_BOARD_HEADER " Invalid piece type",
			PTCE_BOARD_HEADER " Invalid piece position",
			PTCE_BOARD_HEADER " Invalid board state",
			PTCE_BOARD_HEADER " Invalid board move type",
			PTCE_BOARD_HEADER " Enemy king was not found",
			PTCE_BOARD_HEADER " Malformed serialization",
			PTCE_BOARD_HEADER " Piece already exists",
			PTCE_BOARD_HEADER " Board factory is uninitialized",
			PTCE_BOARD_HEADER " Board does not exist",
			PTCE_BOARD_HEADER " Unknown board command",
			PTCE_BOARD_HEADER " Unknown piece type",
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
