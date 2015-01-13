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

#include "../include/ptce_test.h"
#include "../include/ptce_test_type.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		ptce_test_ptr ptce_test::m_instance = NULL;

		void 
		ptce_test_destroy(void)
		{
			TRACE_ENTRY();

			if(ptce_test::m_instance) {
				delete ptce_test::m_instance;
				ptce_test::m_instance = NULL;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_test::_ptce_test(void) :
			m_initialized(false)
		{
			TRACE_ENTRY();

			std::atexit(ptce_test_destroy);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_test::~_ptce_test(void)
		{
			TRACE_ENTRY();

			if(m_initialized) {
				destroy();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_test_ptr 
		_ptce_test::acquire(void)
		{
			ptce_test_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				m_instance = new ptce_test();
				if(!m_instance) {
					THROW_PTCE_TEST_EXCEPTION(PTCE_TEST_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0x%p", result);
			return result;
		}

		void 
		_ptce_test::add(
			__in const std::string &name,
			__in const ptce_test_set &set
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(contains(name)) {
				THROW_PTCE_TEST_EXCEPTION_MESSAGE(PTCE_TEST_EXCEPTION_TEST_SET_EXISTS,
					"%s", name.c_str());
			}

			m_test_set.insert(std::pair<std::string, ptce_test_set>(name, set));

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_test::contains(
			__in const std::string &name
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(name.empty()) {
				THROW_PTCE_TEST_EXCEPTION(PTCE_TEST_EXCEPTION_INVALID_TEST_SET_NAME);
			}

			result = (m_test_set.find(name) != m_test_set.end());

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		void 
		_ptce_test::destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_TEST_EXCEPTION(PTCE_TEST_EXCEPTION_UNINITIALIZED);
			}

			m_test_set.clear();
			m_initialized = false;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		std::map<std::string, ptce_test_set>::iterator 
		_ptce_test::find_test_set(
			__in const std::string &name
			)
		{
			std::map<std::string, ptce_test_set>::iterator result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(name.empty()) {
				THROW_PTCE_TEST_EXCEPTION(PTCE_TEST_EXCEPTION_INVALID_TEST_SET_NAME);
			}

			result = m_test_set.find(name);
			if(result == m_test_set.end()) {
				THROW_PTCE_TEST_EXCEPTION_MESSAGE(PTCE_TEST_EXCEPTION_UNKNOWN_TEST_SET,
					"%s", name.c_str());
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result;
		}

		void 
		_ptce_test::initialize(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_PTCE_TEST_EXCEPTION(PTCE_TEST_EXCEPTION_INITIALIZED);
			}

			m_test_set.clear();
			m_initialized = true;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_test::is_initialized(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_initialized);
			return m_initialized;
		}

		void 
		_ptce_test::remove(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_test_set.erase(find_test_set(name));

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test::remove_all(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_test_set.clear();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test::reset(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			find_test_set(name)->second.reset_all();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test::reset_all(void)
		{
			std::map<std::string, ptce_test_set>::iterator test_set_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(test_set_iter = m_test_set.begin(); test_set_iter != m_test_set.end(); 
					++test_set_iter) {
				test_set_iter->second.reset_all();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test::run(
			__in const std::string &name,
			__out size_t &failure,
			__out size_t &inconclusive,
			__out size_t &success
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			find_test_set(name)->second.run_all(failure, inconclusive, success);

			TRACE_EXIT("Return Value: %s: %lu, %s: %lu, %s: %lu", PTCE_TEST_STRING(PTCE_TEST_FAILURE), 
					failure, PTCE_TEST_STRING(PTCE_TEST_INCONCLUSIVE), inconclusive, 
					PTCE_TEST_STRING(PTCE_TEST_SUCCESS), success);
		}

		void 
		_ptce_test::run_all(
			__out size_t &failure,
			__out size_t &inconclusive,
			__out size_t &success
			)
		{
			size_t set_failure, set_inconclusive, set_success;
			std::map<std::string, ptce_test_set>::iterator test_set_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			failure = 0;
			inconclusive = 0;
			success = 0;

			for(test_set_iter = m_test_set.begin(); test_set_iter != m_test_set.end(); 
					++test_set_iter) {
				set_failure = 0;
				set_inconclusive = 0;
				set_success = 0;
				test_set_iter->second.run_all(set_failure, set_inconclusive, 
						set_success);
				failure += set_failure;
				inconclusive += set_inconclusive;
				success += set_success;
			}

			TRACE_EXIT("Return Value: %s: %lu, %s: %lu, %s: %lu", PTCE_TEST_STRING(PTCE_TEST_FAILURE), 
					failure, PTCE_TEST_STRING(PTCE_TEST_INCONCLUSIVE), inconclusive, 
					PTCE_TEST_STRING(PTCE_TEST_SUCCESS), success);
		}

		size_t 
		_ptce_test::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = m_test_set.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		ptce_test_set 
		_ptce_test::test_set(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return find_test_set(name)->second;
		}

		size_t 
		_ptce_test::test_set_result(
			__in const std::string &name,
			__in ptce_test_t type
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = find_test_set(name)->second.test_result(type);

			TRACE_EXIT("Return Value: %s: %s (0x%x): %lu", name.c_str(), PTCE_TEST_STRING(type), 
				type, result);
			return result;
		}

		size_t 
		_ptce_test::test_total_result(
			__in ptce_test_t type
			)
		{
			size_t result = 0;
			std::map<std::string, ptce_test_set>::iterator test_set_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(test_set_iter = m_test_set.begin(); test_set_iter != m_test_set.end(); 
					++test_set_iter) {
				result += test_set_iter->second.test_result(type);
			}

			TRACE_EXIT("Return Value: %s (0x%x): %lu", PTCE_TEST_STRING(type), type, result);
			return result;
		}

		std::string 
		_ptce_test::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<std::string, ptce_test_set>::iterator test_set_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(verbose) {
				result << PTCE_TEST_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance) 
						<< ", Sets=" << m_test_set.size();
			}

			for(test_set_iter = m_test_set.begin(); test_set_iter != m_test_set.end(); 
					++test_set_iter) {
				result << std::endl << std::endl << test_set_iter->second.to_string(verbose);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
