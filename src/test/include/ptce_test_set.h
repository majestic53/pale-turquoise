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

#ifndef PTCE_TEST_SET_H_
#define PTCE_TEST_SET_H_

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		typedef enum _ptce_test_t {
			PTCE_TEST_FAILURE = 0,
			PTCE_TEST_INCONCLUSIVE,
			PTCE_TEST_SUCCESS,
		} ptce_test_t;

		#define PTCE_TEST_MAX PTCE_TEST_SUCCESS

		static const std::string PTCE_TEST_STR[] = {
			"FAILURE", "INCONCLUSIVE", "SUCCESS",
			};

		#define PTCE_TEST_STRING(_TYPE_) \
			((_TYPE_) > PTCE_TEST_MAX ? UNKNOWN : \
			PTCE_TEST_STR[_TYPE_].c_str())

		typedef ptce_test_t(*ptce_test_set_cb)(void);

		typedef std::pair<ptce_test_set_cb, ptce_test_t> ptce_test_set_inst_t;

		typedef class _ptce_test_set {

			public:

				_ptce_test_set(
					__in const std::string &name
					);

				_ptce_test_set(
					__in const _ptce_test_set &other
					);

				virtual ~_ptce_test_set(void);

				_ptce_test_set &operator=(
					__in const _ptce_test_set &other
					);

				void add(
					__in const std::string &name,
					__in ptce_test_set_cb test
					);

				bool contains(
					__in const std::string &name
					);

				std::string name(void);

				void remove(
					__in const std::string &name
					);

				void remove_all(void);

				void reset(
					__in const std::string &name
					);

				void reset_all(void);

				ptce_test_t run(
					__in const std::string &name
					);

				void run_all(
					__out size_t &failure,
					__out size_t &inconclusive,
					__out size_t &success
					);

				size_t size(void);

				ptce_test_set_inst_t test(
					__in const std::string &name
					);

				size_t test_result(
					__in ptce_test_t type
					);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				std::map<std::string, ptce_test_set_inst_t>::iterator find_test(
					__in const std::string &name
					);

				std::string m_name;

				std::map<std::string, ptce_test_set_inst_t> m_test;

			private:

				std::recursive_mutex m_lock;

		} ptce_test_set, *ptce_test_set_ptr;
	}
}

#endif // PTCE_TEST_SET_H_
