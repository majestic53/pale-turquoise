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

#ifndef PTCE_PIECE_H_
#define PTCE_PIECE_H_

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		typedef enum _ptce_piece_t {
			PIECE_EMPTY = 0,
			PIECE_KING,
			PIECE_QUEEN,
			PIECE_ROOK,
			PIECE_BISHOP,
			PIECE_KNIGHT,
			PIECE_PAWN,	
		} ptce_piece_t;

		#define PIECE_TYPE_MAX PIECE_PAWN

		static const std::string PIECE_TYPE_STR[] = {
			"EMPTY", "KING", "QUEEN", "ROOK", "BISHOP", "KNIGHT", "PAWN",
			};

		#define PIECE_TYPE_STRING(_TYPE_) \
			((_TYPE_) > PIECE_TYPE_MAX ? UNKNOWN : \
			PIECE_TYPE_STR[_TYPE_].c_str())

		typedef enum _ptce_piece_col_t {
			PIECE_WHITE = 0,
			PIECE_BLACK,
		} ptce_piece_col_t;

		#define PIECE_COLOR_MAX PIECE_BLACK

		static const std::string PIECE_COLOR_STR[] = {
			"WHITE", "BLACK",
			};

		#define PIECE_COLOR_STRING(_TYPE_) \
			((_TYPE_) > PIECE_COLOR_MAX ? UNKNOWN : \
			PIECE_COLOR_STR[_TYPE_].c_str())

		typedef class _ptce_piece :
				public ptce_uid_base {

			public:

				_ptce_piece(
					__in ptce_piece_t type,
					__in ptce_piece_col_t color
					);

				_ptce_piece(
					__in const _ptce_piece &other
					);

				virtual ~_ptce_piece(void);

				_ptce_piece &operator=(
					__in const _ptce_piece &other
					);

				bool operator==(
					__in const _ptce_piece &other
					);

				bool operator!=(
					__in const _ptce_piece &other
					);

				ptce_piece_col_t &color(void);

				static std::string piece_as_string(
					__in const _ptce_piece &piece,
					__in_opt bool verbose = false
					);

				static std::string piece_as_symbol(
					__in const _ptce_piece &piece
					);

				ptce_piece_t &type(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				ptce_piece_col_t m_color;

				ptce_piece_t m_type;

			private:

				std::recursive_mutex m_lock;

		} ptce_piece, *ptce_piece_ptr;

		// TODO: implement factory
	}
}

#endif // PTCE_PIECE_H_
