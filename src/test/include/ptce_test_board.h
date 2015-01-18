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

#ifndef PTCE_TEST_BOARD_H_
#define PTCE_TEST_BOARD_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define PTCE_TEST_BOARD_TRACE_HEADER "(BOARD)"

		enum {
			PTCE_TEST_BOARD_ASSIGNMENT = 0,
			PTCE_TEST_BOARD_CONSTRUCTOR,
			PTCE_TEST_BOARD_CONTAINS,
			PTCE_TEST_BOARD_EQUALS,
			PTCE_TEST_BOARD_MOVE,
			PTCE_TEST_BOARD_NOT_EQUALS,
			PTCE_TEST_BOARD_PIECE,
			PTCE_TEST_BOARD_PIECE_CAPTURED,
			PTCE_TEST_BOARD_PIECE_COUNT,
			PTCE_TEST_BOARD_PIECE_MOVED,
			PTCE_TEST_BOARD_SIZE,
			PTCE_TEST_BOARD_STATE,
		};

		#define PTCE_TEST_BOARD_MAX PTCE_TEST_BOARD_STATE

		static const std::string PTCE_TEST_BOARD_STR[] = {
			"PTCE_TEST_BOARD_ASSIGNMENT",
			"PTCE_TEST_BOARD_CONSTRUCTOR",
			"PTCE_TEST_BOARD_CONTAINS",
			"PTCE_TEST_BOARD_EQUALS",
			"PTCE_TEST_BOARD_MOVE",
			"PTCE_TEST_BOARD_NOT_EQUALS",
			"PTCE_TEST_BOARD_PIECE",
			"PTCE_TEST_BOARD_PIECE_CAPTURED",
			"PTCE_TEST_BOARD_PIECE_COUNT",
			"PTCE_TEST_BOARD_PIECE_MOVED",
			"PTCE_TEST_BOARD_SIZE",
			"PTCE_TEST_BOARD_STATE",
			};

		#define PTCE_TEST_BOARD_STRING(_TYPE_) \
			((_TYPE_) > PTCE_TEST_BOARD_MAX ? UNKNOWN : \
			PTCE_TEST_BOARD_STR[_TYPE_].c_str())

		extern ptce_test_t ptce_test_board_assignment(void);

		extern ptce_test_t ptce_test_board_constructor(void);

		extern ptce_test_t ptce_test_board_contains(void);

		extern ptce_test_t ptce_test_board_equals(void);

		extern ptce_test_t ptce_test_board_move(void);

		extern ptce_test_t ptce_test_board_not_equals(void);

		extern ptce_test_t ptce_test_board_piece(void);

		extern ptce_test_t ptce_test_board_piece_captured(void);

		extern ptce_test_t ptce_test_board_piece_count(void);

		extern ptce_test_t ptce_test_board_piece_moved(void);

		extern ptce_test_t ptce_test_board_size(void);

		extern ptce_test_t ptce_test_board_state(void);

		static const ptce_test_set_cb PTCE_TEST_BOARD_CB[] = {
			ptce_test_board_assignment,
			ptce_test_board_constructor,
			ptce_test_board_contains,
			ptce_test_board_equals,
			ptce_test_board_move,
			ptce_test_board_not_equals,
			ptce_test_board_piece,
			ptce_test_board_piece_captured,
			ptce_test_board_piece_count,
			ptce_test_board_piece_moved,
			ptce_test_board_size,
			ptce_test_board_state,
			};

		#define PTCE_TEST_BOARD_CALLBACK(_TYPE_) \
			((_TYPE_) > PTCE_TEST_BOARD_MAX ? NULL : \
			PTCE_TEST_BOARD_CB[_TYPE_])
	}
}

#endif // PTCE_TEST_BOARD_H_