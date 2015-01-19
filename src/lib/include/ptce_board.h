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

#ifndef PTCE_BOARD_H_
#define PTCE_BOARD_H_

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		typedef enum _ptce_board_st_t {
			BOARD_INACTIVE = 0,
			BOARD_ACTIVE,
		} ptce_board_st_t;

		#define BOARD_STATE_MAX BOARD_ACTIVE

		static const std::string BOARD_STATE_STR[] = {
			"INACTIVE", "ACTIVE",
			};

		#define BOARD_STATE_STRING(_TYPE_) \
			((_TYPE_) > BOARD_STATE_MAX ? UNKNOWN : \
			BOARD_STATE_STR[_TYPE_].c_str())

		#define BOARD_POS_MAX 7
		#define BOARD_WID (BOARD_POS_MAX + 1)
		#define BOARD_LEN (BOARD_WID * BOARD_WID)

		typedef std::pair<uint8_t, uint8_t> ptce_pos_t;

		typedef class _ptce_board :
				public ptce_uid_base {

			public:

				_ptce_board(void);

				_ptce_board(
					__in const _ptce_board &other
					);

				virtual ~_ptce_board(void);

				_ptce_board &operator=(
					__in const _ptce_board &other
					);

				bool operator==(
					__in const _ptce_board &other
					);

				bool operator!=(
					__in const _ptce_board &other
					);

				static std::string board_as_string(
					__in const _ptce_board &board,
					__in_opt bool verbose = false
					);

				bool contains(
					__in const ptce_pos_t &position
					);

				void move(
					__in const ptce_pos_t &old_position,
					__in const ptce_pos_t &new_position
					);

				ptce_piece &piece(
					__in const ptce_pos_t &position
					);

				bool piece_captured(void);

				size_t piece_count(
					__out size_t &white,
					__out size_t &black
					);

				std::vector<ptce_piece> &piece_list(void);

				ptce_piece &piece_moved(void);

				ptce_pos_t &piece_moved_coordinate(void);

				size_t size(void);

				ptce_board_st_t &state(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend class _ptce_board_factory;

				size_t decrement_piece_reference(
					__in const ptce_piece &piece
					);

				void generate_initial_board(void);

				ptce_piece &generate_piece(
					__in ptce_piece_t type,
					__in ptce_piece_col_t color
					);

				size_t increment_piece_reference(
					__in const ptce_piece &piece
					);

				bool m_piece_captured;

				std::vector<ptce_piece> m_piece_list;

				ptce_pos_t m_piece_moved;

				ptce_board_st_t m_state;

			private:

				std::recursive_mutex m_lock;

		} ptce_board, *ptce_board_ptr;

		void ptce_board_factory_destroy(void);

		typedef class _ptce_board_factory {

			public:

				~_ptce_board_factory(void);

				static _ptce_board_factory *acquire(void);

				bool contains(
					__in const ptce_uid &uid
					);

				bool contains(
					__in const ptce_board &board
					);

				size_t decrement_reference(
					__in const ptce_uid &uid
					);

				size_t decrement_reference(
					__in const ptce_board &board
					);

				void destroy(void);

				ptce_board &generate(void);

				size_t increment_reference(
					__in const ptce_uid &uid
					);

				size_t increment_reference(
					__in const ptce_board &board
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				size_t reference_count(
					__in const ptce_uid &uid
					);

				size_t reference_count(
					__in const ptce_board &board
					);

				size_t size(void);

				std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend void ptce_board_factory_destroy(void);

				_ptce_board_factory(void);

				_ptce_board_factory(
					__in const _ptce_board_factory &other
					);

				_ptce_board_factory &operator=(
					__in const _ptce_board_factory &other
					);

				std::map<ptce_uid, std::pair<ptce_board, size_t>>::iterator find_board(
					__in const ptce_uid &uid
					);

				std::map<ptce_uid, std::pair<ptce_board, size_t>> m_board_map;

				bool m_initialized;

				static _ptce_board_factory *m_instance;

			private:

				std::recursive_mutex m_lock;

		} ptce_board_factory, *ptce_board_factory_ptr;
	}
}

#endif // PTCE_BOARD_H_
