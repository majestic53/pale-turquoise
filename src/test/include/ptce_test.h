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

#ifndef PTCE_TEST_H_
#define PTCE_TEST_H_

#include <map>
#include "../../lib/include/ptce.h"

#ifndef PTCE_TEST_NS
#define PTCE_TEST_NS ptce_test_ns
#endif // PTCE_TEST_NS

#include "ptce_test_set.h"

using namespace PTCE_NS::PTCE_TEST_NS;

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		void ptce_test_destroy(void);

		typedef class _ptce_test {

			public:

				~_ptce_test(void);

				static _ptce_test *acquire(void);

				void add(
					__in const std::string &name,
					__in const ptce_test_set &set
					);

				bool contains(
					__in const std::string &name
					);

				void destroy(void);

				void initialize(void);

				bool is_initialized(void);

				void remove(
					__in const std::string &name
					);

				void remove_all(void);

				void reset(
					__in const std::string &name
					);

				void reset_all(void);

				void run(
					__in const std::string &name,
					__out size_t &failure,
					__out size_t &inconclusive,
					__out size_t &success
					);

				void run_all(
					__out size_t &failure,
					__out size_t &inconclusive,
					__out size_t &success
					);

				size_t size(void);

				ptce_test_set test_set(
					__in const std::string &name
					);

				size_t test_set_result(
					__in const std::string &name,
					__in ptce_test_t type
					);

				size_t test_total_result(
					__in ptce_test_t type
					);

				std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend void ptce_test_destroy(void);

				std::map<std::string, ptce_test_set>::iterator find_test_set(
					__in const std::string &name
					);

				_ptce_test(void);

				_ptce_test(
					__in const _ptce_test &other
					);

				_ptce_test &operator=(
					__in const _ptce_test &other
					);

				bool m_initialized;

				static _ptce_test *m_instance;

				std::map<std::string, ptce_test_set> m_test_set;

			private:

				std::recursive_mutex m_lock;

		} ptce_test, *ptce_test_ptr;
	}
}

#endif // PTCE_TEST_H_
