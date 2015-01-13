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

#ifndef PTCE_TEST_TYPE_H_
#define PTCE_TEST_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#ifndef NDEBUG
		#define PTCE_TEST_HEADER "(TEST)"
		#else
		#define PTCE_TEST_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_TEST_TRACE_HEADER "(TEST_SUITE)"

		enum {
			PTCE_TEST_EXCEPTION_ACQUIRE_FAILED = 0,
			PTCE_TEST_EXCEPTION_INITIALIZED,
			PTCE_TEST_EXCEPTION_INVALID_TEST_SET_NAME,
			PTCE_TEST_EXCEPTION_TEST_SET_EXISTS,
			PTCE_TEST_EXCEPTION_UNINITIALIZED,
			PTCE_TEST_EXCEPTION_UNKNOWN_TEST_SET,
		};

		#define PTCE_TEST_EXCEPTION_MAX PTCE_TEST_EXCEPTION_UNKNOWN_TEST_SET

		static const std::string PTCE_TEST_EXCEPTION_STR[] = {
			PTCE_TEST_HEADER " Failed to acquire instance",
			PTCE_TEST_HEADER " Test library is already initialized",
			PTCE_TEST_HEADER " Invalid test set name",
			PTCE_TEST_HEADER " Test set already exists",
			PTCE_TEST_HEADER " Test library is uninitialized",
			PTCE_TEST_HEADER " Test set does not exist", 
			};

		#define PTCE_TEST_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_TEST_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_TEST_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_TEST_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_TEST_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_TEST_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_TEST_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_test;
		typedef _ptce_test ptce_test, *ptce_test_ptr;
	}
}

#endif // PTCE_TEST_TYPE_H_
