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

#ifndef PTCE_TEST_SINGLETON_H_
#define PTCE_TEST_SINGLETON_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define PTCE_TEST_SINGLETON_TRACE_HEADER "(PTCE)"

		enum {
			PTCE_TEST_SINGLETON_ACQUIRE = 0,
			PTCE_TEST_SINGLETON_ACQUIRE_BOARD_FACTORY,
			PTCE_TEST_SINGLETON_ACQUIRE_NODE_FACTORY,
			PTCE_TEST_SINGLETON_ACQUIRE_PIECE_FACTORY,
			PTCE_TEST_SINGLETON_ACQUIRE_UID_FACTORY,
			PTCE_TEST_SINGLETON_DESTROY,
			PTCE_TEST_SINGLETON_INITIALIZE,
			PTCE_TEST_SINGLETON_IS_ALLOCATED,
			PTCE_TEST_SINGLETON_IS_INITIALIZED,
			PTCE_TEST_SINGLETON_RELEASE_BOARD_FACTORY,
			PTCE_TEST_SINGLETON_RELEASE_NODE_FACTORY,
			PTCE_TEST_SINGLETON_RELEASE_PIECE_FACTORY,
			PTCE_TEST_SINGLETON_RELEASE_UID_FACTORY,
			PTCE_TEST_SINGLETON_VERSION,
		};

		#define PTCE_TEST_SINGLETON_MAX PTCE_TEST_SINGLETON_VERSION

		static const std::string PTCE_TEST_SINGLETON_STR[] = {
			"PTCE_TEST_SINGLETON_ACQUIRE",
			"PTCE_TEST_SINGLETON_ACQUIRE_BOARD_FACTORY",
			"PTCE_TEST_SINGLETON_ACQUIRE_NODE_FACTORY",
			"PTCE_TEST_SINGLETON_ACQUIRE_PIECE_FACTORY",
			"PTCE_TEST_SINGLETON_ACQUIRE_UID_FACTORY",
			"PTCE_TEST_SINGLETON_DESTROY",
			"PTCE_TEST_SINGLETON_INITIALIZE",
			"PTCE_TEST_SINGLETON_IS_ALLOCATED",
			"PTCE_TEST_SINGLETON_IS_INITIALIZED",
			"PTCE_TEST_SINGLETON_RELEASE_BOARD_FACTORY",
			"PTCE_TEST_SINGLETON_RELEASE_NODE_FACTORY",
			"PTCE_TEST_SINGLETON_RELEASE_PIECE_FACTORY",
			"PTCE_TEST_SINGLETON_RELEASE_UID_FACTORY",
			"PTCE_TEST_SINGLETON_VERSION",
			};

		#define PTCE_TEST_SINGLETON_STRING(_TYPE_) \
			((_TYPE_) > PTCE_TEST_SINGLETON_MAX ? UNKNOWN : \
			PTCE_TEST_SINGLETON_STR[_TYPE_].c_str())

		extern ptce_test_t ptce_test_singleton_acquire(void);

		extern ptce_test_t ptce_test_singleton_acquire_board_factory(void);

		extern ptce_test_t ptce_test_singleton_acquire_node_factory(void);

		extern ptce_test_t ptce_test_singleton_acquire_piece_factory(void);

		extern ptce_test_t ptce_test_singleton_acquire_uid_factory(void);

		extern ptce_test_t ptce_test_singleton_destroy(void);

		extern ptce_test_t ptce_test_singleton_initialize(void);

		extern ptce_test_t ptce_test_singleton_is_allocated(void);

		extern ptce_test_t ptce_test_singleton_is_initialized(void);

		extern ptce_test_t ptce_test_singleton_release_board_factory(void);

		extern ptce_test_t ptce_test_singleton_release_node_factory(void);

		extern ptce_test_t ptce_test_singleton_release_piece_factory(void);

		extern ptce_test_t ptce_test_singleton_release_uid_factory(void);

		extern ptce_test_t ptce_test_singleton_version(void);

		static const ptce_test_set_cb PTCE_TEST_SINGLETON_CB[] = {
			ptce_test_singleton_acquire,
			ptce_test_singleton_acquire_board_factory,
			ptce_test_singleton_acquire_node_factory,
			ptce_test_singleton_acquire_piece_factory,
			ptce_test_singleton_acquire_uid_factory,
			ptce_test_singleton_destroy,
			ptce_test_singleton_initialize,
			ptce_test_singleton_is_allocated,
			ptce_test_singleton_is_initialized,
			ptce_test_singleton_release_board_factory,
			ptce_test_singleton_release_node_factory,
			ptce_test_singleton_release_piece_factory,
			ptce_test_singleton_release_uid_factory,
			ptce_test_singleton_version,
			};

		#define PTCE_TEST_SINGLETON_CALLBACK(_TYPE_) \
			((_TYPE_) > PTCE_TEST_SINGLETON_MAX ? NULL : \
			PTCE_TEST_SINGLETON_CB[_TYPE_])
	}
}

#endif // PTCE_TEST_SINGLETON_H_
