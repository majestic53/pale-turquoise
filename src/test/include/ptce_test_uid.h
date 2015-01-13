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

#ifndef PTCE_TEST_UID_H_
#define PTCE_TEST_UID_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define PTCE_TEST_UID_TRACE_HEADER "(UID)"

		enum {
			PTCE_TEST_UID_ASSIGNMENT = 0,
			PTCE_TEST_UID_BASE_ASSIGNMENT,
			PTCE_TEST_UID_BASE_CONSTRUCTOR,
			PTCE_TEST_UID_BASE_ID,
			PTCE_TEST_UID_CONSTRUCTOR,
			PTCE_TEST_UID_EQUALS,
			PTCE_TEST_UID_FACTORY_ACQUIRE,
			PTCE_TEST_UID_FACTORY_ADD,
			PTCE_TEST_UID_FACTORY_CONTAINS,
			PTCE_TEST_UID_FACTORY_DECREMENT_REFERENCE,
			PTCE_TEST_UID_FACTORY_DESTROY,
			PTCE_TEST_UID_FACTORY_GENERATE,
			PTCE_TEST_UID_FACTORY_INCREMENT_REFERENCE,
			PTCE_TEST_UID_FACTORY_INITIALIZE,
			PTCE_TEST_UID_FACTORY_IS_ALLOCATED,
			PTCE_TEST_UID_FACTORY_IS_INITIALIZED,
			PTCE_TEST_UID_FACTORY_REFERENCE_COUNT,
			PTCE_TEST_UID_FACTORY_SIZE,
			PTCE_TEST_UID_ID,
			PTCE_TEST_UID_NOT_EQUALS,
		};

		#define PTCE_TEST_UID_MAX PTCE_TEST_UID_NOT_EQUALS

		static const std::string PTCE_TEST_UID_STR[] = {
			"PTCE_TEST_UID_ASSIGNMENT",
			"PTCE_TEST_UID_BASE_ASSIGNMENT",
			"PTCE_TEST_UID_BASE_CONSTRUCTOR",
			"PTCE_TEST_UID_BASE_ID",
			"PTCE_TEST_UID_CONSTRUCTOR",
			"PTCE_TEST_UID_EQUALS",
			"PTCE_TEST_UID_FACTORY_ACQUIRE",
			"PTCE_TEST_UID_FACTORY_ADD",
			"PTCE_TEST_UID_FACTORY_CONTAINS",
			"PTCE_TEST_UID_FACTORY_DECREMENT_REFERENCE",
			"PTCE_TEST_UID_FACTORY_DESTROY",
			"PTCE_TEST_UID_FACTORY_GENERATE",
			"PTCE_TEST_UID_FACTORY_INCREMENT_REFERENCE",
			"PTCE_TEST_UID_FACTORY_INITIALIZE",
			"PTCE_TEST_UID_FACTORY_IS_ALLOCATED",
			"PTCE_TEST_UID_FACTORY_IS_INITIALIZED",
			"PTCE_TEST_UID_FACTORY_REFERENCE_COUNT",
			"PTCE_TEST_UID_FACTORY_SIZE",
			"PTCE_TEST_UID_ID",
			"PTCE_TEST_UID_NOT_EQUALS",
			};

		#define PTCE_TEST_UID_STRING(_TYPE_) \
			((_TYPE_) > PTCE_TEST_UID_MAX ? UNKNOWN : \
			PTCE_TEST_UID_STR[_TYPE_].c_str())

		extern ptce_test_t ptce_test_uid_assignment(void);

		extern ptce_test_t ptce_test_uid_base_assignment(void);

		extern ptce_test_t ptce_test_uid_base_constructor(void);

		extern ptce_test_t ptce_test_uid_base_id(void);

		extern ptce_test_t ptce_test_uid_constructor(void);

		extern ptce_test_t ptce_test_uid_equals(void);

		extern ptce_test_t ptce_test_uid_factory_acquire(void);

		extern ptce_test_t ptce_test_uid_factory_add(void);

		extern ptce_test_t ptce_test_uid_factory_contains(void);

		extern ptce_test_t ptce_test_uid_factory_decrement_reference(void);

		extern ptce_test_t ptce_test_uid_factory_destroy(void);

		extern ptce_test_t ptce_test_uid_factory_generate(void);

		extern ptce_test_t ptce_test_uid_factory_increment_reference(void);

		extern ptce_test_t ptce_test_uid_factory_initialize(void);

		extern ptce_test_t ptce_test_uid_factory_is_allocated(void);

		extern ptce_test_t ptce_test_uid_factory_is_initialized(void);

		extern ptce_test_t ptce_test_uid_factory_reference_count(void);

		extern ptce_test_t ptce_test_uid_factory_size(void);

		extern ptce_test_t ptce_test_uid_id(void);

		extern ptce_test_t ptce_test_uid_not_equals(void);

		static const ptce_test_set_cb PTCE_TEST_UID_CB[] = {
			ptce_test_uid_assignment,
			ptce_test_uid_base_assignment,
			ptce_test_uid_base_constructor,
			ptce_test_uid_base_id,
			ptce_test_uid_constructor,
			ptce_test_uid_equals,
			ptce_test_uid_factory_acquire,
			ptce_test_uid_factory_add,
			ptce_test_uid_factory_contains,
			ptce_test_uid_factory_decrement_reference,
			ptce_test_uid_factory_destroy,
			ptce_test_uid_factory_generate,
			ptce_test_uid_factory_increment_reference,
			ptce_test_uid_factory_initialize,
			ptce_test_uid_factory_is_allocated,
			ptce_test_uid_factory_is_initialized,
			ptce_test_uid_factory_reference_count,
			ptce_test_uid_factory_size,
			ptce_test_uid_id,
			ptce_test_uid_not_equals,
			};

		#define PTCE_TEST_UID_CALLBACK(_TYPE_) \
			((_TYPE_) > PTCE_TEST_UID_MAX ? NULL : \
			PTCE_TEST_UID_CB[_TYPE_])
	}
}

#endif // PTCE_TEST_UID_H_
