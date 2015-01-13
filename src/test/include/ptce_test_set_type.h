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

#ifndef PTCE_TEST_SET_TYPE_H_
#define PTCE_TEST_SET_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#ifndef NDEBUG
		#define PTCE_TEST_SET_HEADER "(TEST_SET)"
		#else
		#define PTCE_TEST_SET_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_TEST_TRACE_HEADER "(TEST_SET)"

		enum {
			PTCE_TEST_SET_EXCEPTION_INVALID_TEST = 0,
			PTCE_TEST_SET_EXCEPTION_INVALID_TEST_NAME,
			PTCE_TEST_SET_EXCEPTION_INVALID_TEST_TYPE,
			PTCE_TEST_SET_EXCEPTION_TEST_EXISTS,
			PTCE_TEST_SET_EXCEPTION_UNKNOWN_TEST,
			PTCE_TEST_SET_EXCEPTION_UNKNOWN_TEST_TYPE,
		};

		#define PTCE_TEST_SET_EXCEPTION_MAX PTCE_TEST_SET_EXCEPTION_UNKNOWN_TEST_TYPE

		static const std::string PTCE_TEST_SET_EXCEPTION_STR[] = {
			PTCE_TEST_SET_HEADER " Invalid test",
			PTCE_TEST_SET_HEADER " Invalid test name",
			PTCE_TEST_SET_HEADER " Invalid test type",
			PTCE_TEST_SET_HEADER " Test already exists",
			PTCE_TEST_SET_HEADER " Test does not exist",
			PTCE_TEST_SET_HEADER " Unknown test type",
			};

		#define PTCE_TEST_SET_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_TEST_SET_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_TEST_SET_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_TEST_SET_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_TEST_SET_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_test_set;
		typedef _ptce_test_set ptce_test_set, *ptce_test_set_ptr;
	}
}

#endif // PTCE_TEST_SET_TYPE_H_
