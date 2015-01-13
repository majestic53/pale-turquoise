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

#ifndef PTCE_TEST_NODE_H_
#define PTCE_TEST_NODE_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define PTCE_TEST_NODE_TRACE_HEADER "(NODE)"

		enum {
			PTCE_TEST_NODE_ASSIGNMENT = 0,
			PTCE_TEST_NODE_CONSTRUCTOR,
			PTCE_TEST_NODE_CHILDREN,
			PTCE_TEST_NODE_ENTRY,
			PTCE_TEST_NODE_EQUALS,
			PTCE_TEST_NODE_FACTORY_ACQUIRE,
			PTCE_TEST_NODE_FACTORY_CONTAINS,
			PTCE_TEST_NODE_FACTORY_DECREMENT_REFERENCE,
			PTCE_TEST_NODE_FACTORY_DESTROY,
			PTCE_TEST_NODE_FACTORY_GENERATE,
			PTCE_TEST_NODE_FACTORY_INCREMENT_REFERENCE,
			PTCE_TEST_NODE_FACTORY_INITIALIZE,
			PTCE_TEST_NODE_FACTORY_IS_ALLOCATED,
			PTCE_TEST_NODE_FACTORY_IS_INITIALIZED,
			PTCE_TEST_NODE_FACTORY_REFERENCE_COUNT,
			PTCE_TEST_NODE_FACTORY_SIZE,
			PTCE_TEST_NODE_NOT_EQUALS,
			PTCE_TEST_NODE_PARENT,
			PTCE_TEST_NODE_SIZE,
		};

		#define PTCE_TEST_NODE_MAX PTCE_TEST_NODE_SIZE

		static const std::string PTCE_TEST_NODE_STR[] = {
			"PTCE_TEST_NODE_ASSIGNMENT",
			"PTCE_TEST_NODE_CONSTRUCTOR",
			"PTCE_TEST_NODE_CHILDREN",
			"PTCE_TEST_NODE_ENTRY",
			"PTCE_TEST_NODE_EQUALS",
			"PTCE_TEST_NODE_FACTORY_ACQUIRE",
			"PTCE_TEST_NODE_FACTORY_CONTAINS",
			"PTCE_TEST_NODE_FACTORY_DECREMENT_REFERENCE",
			"PTCE_TEST_NODE_FACTORY_DESTROY",
			"PTCE_TEST_NODE_FACTORY_GENERATE",
			"PTCE_TEST_NODE_FACTORY_INCREMENT_REFERENCE",
			"PTCE_TEST_NODE_FACTORY_INITIALIZE",
			"PTCE_TEST_NODE_FACTORY_IS_ALLOCATED",
			"PTCE_TEST_NODE_FACTORY_IS_INITIALIZED",
			"PTCE_TEST_NODE_FACTORY_REFERENCE_COUNT",
			"PTCE_TEST_NODE_FACTORY_SIZE",
			"PTCE_TEST_NODE_NOT_EQUALS",
			"PTCE_TEST_NODE_PARENT",
			"PTCE_TEST_NODE_SIZE",
			};

		#define PTCE_TEST_NODE_STRING(_TYPE_) \
			((_TYPE_) > PTCE_TEST_NODE_MAX ? UNKNOWN : \
			PTCE_TEST_NODE_STR[_TYPE_].c_str())

		extern ptce_test_t ptce_test_node_assignment(void);

		extern ptce_test_t ptce_test_node_constructor(void);

		extern ptce_test_t ptce_test_node_children(void);

		extern ptce_test_t ptce_test_node_entry(void);

		extern ptce_test_t ptce_test_node_equals(void);

		extern ptce_test_t ptce_test_node_factory_acquire(void);

		extern ptce_test_t ptce_test_node_factory_contains(void);

		extern ptce_test_t ptce_test_node_factory_decrement_reference(void);

		extern ptce_test_t ptce_test_node_factory_destroy(void);

		extern ptce_test_t ptce_test_node_factory_generate(void);

		extern ptce_test_t ptce_test_node_factory_increment_reference(void);

		extern ptce_test_t ptce_test_node_factory_initialize(void);

		extern ptce_test_t ptce_test_node_factory_is_allocated(void);

		extern ptce_test_t ptce_test_node_factory_is_initialized(void);

		extern ptce_test_t ptce_test_node_factory_reference_count(void);

		extern ptce_test_t ptce_test_node_factory_size(void);

		extern ptce_test_t ptce_test_node_not_equals(void);

		extern ptce_test_t ptce_test_node_parent(void);

		extern ptce_test_t ptce_test_node_size(void);

		static const ptce_test_set_cb PTCE_TEST_NODE_CB[] = {
			ptce_test_node_assignment,
			ptce_test_node_constructor,
			ptce_test_node_children,
			ptce_test_node_entry,
			ptce_test_node_equals,
			ptce_test_node_factory_acquire,
			ptce_test_node_factory_contains,
			ptce_test_node_factory_decrement_reference,
			ptce_test_node_factory_destroy,
			ptce_test_node_factory_generate,
			ptce_test_node_factory_increment_reference,
			ptce_test_node_factory_initialize,
			ptce_test_node_factory_is_allocated,
			ptce_test_node_factory_is_initialized,
			ptce_test_node_factory_reference_count,
			ptce_test_node_factory_size,
			ptce_test_node_not_equals,
			ptce_test_node_parent,
			ptce_test_node_size,
			};

		#define PTCE_TEST_NODE_CALLBACK(_TYPE_) \
			((_TYPE_) > PTCE_TEST_NODE_MAX ? NULL : \
			PTCE_TEST_NODE_CB[_TYPE_])
	}
}

#endif // PTCE_TEST_NODE_H_
