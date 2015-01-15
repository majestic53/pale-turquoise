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

#ifndef PTCE_PIECE_TYPE_H_
#define PTCE_PIECE_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		#ifndef NDEBUG
		#define PTCE_PIECE_HEADER "(PIECE)"
		#else
		#define PTCE_PIECE_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_PIECE_TRACE_HEADER "(PIECE)"

		enum {
			PTCE_PIECE_EXCEPTION_ACQUIRE_FAILED = 0,
			PTCE_PIECE_EXCEPTION_ALREADY_EXISTS,
			PTCE_PIECE_EXCEPTION_INITIALIZED,
			PTCE_PIECE_EXCEPTION_INVALID_COLOR,
			PTCE_PIECE_EXCEPTION_INVALID_TYPE,
			PTCE_PIECE_EXCEPTION_UNINITIALIZED,
			PTCE_PIECE_EXCEPTION_UNKNOWN_PIECE,
		};

		#define PTCE_PIECE_EXCEPTION_MAX PTCE_PIECE_EXCEPTION_UNKNOWN_PIECE

		static const std::string PTCE_PIECE_EXCEPTION_STR[] = {
			PTCE_PIECE_HEADER " Failed to acquire piece factory",
			PTCE_PIECE_HEADER " Piece already exists",
			PTCE_PIECE_HEADER " Piece factory is already initialized",
			PTCE_PIECE_HEADER " Invalid piece color",
			PTCE_PIECE_HEADER " Invalid piece type",
			PTCE_PIECE_HEADER " Piece factory is uninitialized",
			PTCE_PIECE_HEADER " Piece does not exist",
			};

		#define PTCE_PIECE_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_PIECE_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_PIECE_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_PIECE_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_PIECE_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_PIECE_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_PIECE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_piece;
		typedef _ptce_piece ptce_piece, *ptce_piece_ptr;

		class _ptce_piece_factory;
		typedef _ptce_piece_factory ptce_piece_factory, *ptce_piece_factory_ptr;
	}
}

#endif // PTCE_PIECE_TYPE_H_
