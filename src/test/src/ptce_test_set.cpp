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
#include "../include/ptce_test_set_type.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define PTCE_TEST_RES_DEF PTCE_TEST_INCONCLUSIVE

		_ptce_test_set::_ptce_test_set(
			__in const std::string &name
			) :
				m_name(name)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_test_set::_ptce_test_set(
			__in const _ptce_test_set &other
			) :
				m_name(other.m_name),
				m_test(other.m_test)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_test_set::~_ptce_test_set(void)
		{
			TRACE_ENTRY();

			ptce_test_set::remove_all();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_test_set &
		_ptce_test_set::operator=(
			__in const _ptce_test_set &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				m_name = other.m_name;
				m_test = other.m_test;
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		void 
		_ptce_test_set::add(
			__in const std::string &name,
			__in ptce_test_set_cb test
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(contains(name)) {
				THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_TEST_EXISTS,
					"%s", name.c_str());
			}

			m_test.insert(std::pair<std::string, ptce_test_set_inst_t>(name, 
					ptce_test_set_inst_t(test, PTCE_TEST_RES_DEF)));

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_test_set::contains(
			__in const std::string &name
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(name.empty()) {
				THROW_PTCE_TEST_SET_EXCEPTION(PTCE_TEST_SET_EXCEPTION_INVALID_TEST_NAME);
			}

			result = (m_test.find(name) != m_test.end());

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		std::map<std::string, ptce_test_set_inst_t>::iterator 
		_ptce_test_set::find_test(
			__in const std::string &name
			)
		{
			std::map<std::string, ptce_test_set_inst_t>::iterator result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(name.empty()) {
				THROW_PTCE_TEST_SET_EXCEPTION(PTCE_TEST_SET_EXCEPTION_INVALID_TEST_NAME);
			}

			result = m_test.find(name);
			if(result == m_test.end()) {
				THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_UNKNOWN_TEST,
					"%s", name.c_str());
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result;
		}

		std::string 
		_ptce_test_set::name(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_name;
		}

		void 
		_ptce_test_set::remove(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_test.erase(find_test(name));

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test_set::remove_all(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_test.clear();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test_set::reset(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			find_test(name)->second.second = PTCE_TEST_RES_DEF;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		_ptce_test_set::reset_all(void)
		{
			std::map<std::string, ptce_test_set_inst_t>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			for(test_iter = m_test.begin(); test_iter != m_test.end(); ++test_iter) {
				test_iter->second.second = PTCE_TEST_RES_DEF;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_test_t 
		_ptce_test_set::run(
			__in const std::string &name
			)
		{
			ptce_test_t result;
			std::map<std::string, ptce_test_set_inst_t>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			test_iter = find_test(name);
			if(!test_iter->second.first) {
				THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_INVALID_TEST,
					"%s (addr=0x%p)", test_iter->first.c_str(), test_iter->second.first);
			}

			test_iter->second.second = test_iter->second.first();
			result = test_iter->second.second;

			TRACE_EXIT("Return Value: \'%s\' -- %s (0x%x)", test_iter->first.c_str(), 
					PTCE_TEST_STRING(result), result);
			return result;
		}

		void 
		_ptce_test_set::run_all(
			__out size_t &failure,
			__out size_t &inconclusive,
			__out size_t &success
			)
		{
			std::map<std::string, ptce_test_set_inst_t>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			failure = 0;
			inconclusive = 0;
			success = 0;

			for(test_iter = m_test.begin(); test_iter != m_test.end(); ++test_iter) {

				if(!test_iter->second.first) {
					THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_INVALID_TEST,
						"%s (addr=0x%p)", test_iter->first.c_str(), test_iter->second.first);
				}

				test_iter->second.second = test_iter->second.first();

				switch(test_iter->second.second) {
					case PTCE_TEST_FAILURE:
						++failure;
						break;
					case PTCE_TEST_INCONCLUSIVE:
						++inconclusive;
						break;
					case PTCE_TEST_SUCCESS:
						++success;
						break;
					default:
						THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_UNKNOWN_TEST_TYPE,
							"%lu (must be at most %lu)", test_iter->second.second, PTCE_TEST_MAX);
				}
			}

			TRACE_EXIT("Return Value: %s: %lu, %s: %lu, %s: %lu", PTCE_TEST_STRING(PTCE_TEST_FAILURE), 
					failure, PTCE_TEST_STRING(PTCE_TEST_INCONCLUSIVE), inconclusive, 
					PTCE_TEST_STRING(PTCE_TEST_SUCCESS), success);
		}

		size_t 
		_ptce_test_set::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = m_test.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		ptce_test_set_inst_t 
		_ptce_test_set::test(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return find_test(name)->second;
		}

		size_t 
		_ptce_test_set::test_result(
			__in ptce_test_t type
			)
		{
			size_t result = 0;
			std::map<std::string, ptce_test_set_inst_t>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(type > PTCE_TEST_MAX) {
				THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_INVALID_TEST_TYPE,
					"%lu (must be at most %lu)", type, PTCE_TEST_MAX);
			}

			for(test_iter = m_test.begin(); test_iter != m_test.end(); ++test_iter) {

				if(test_iter->second.second == type) {
					++result;
				}
			}

			TRACE_EXIT("Return Value: %s: %lu", PTCE_TEST_STRING(type), result);
			return result;
		}

		std::string 
		_ptce_test_set::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			size_t failure = 0, inconclusive = 0, success = 0;
			std::map<std::string, ptce_test_set_inst_t>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << PTCE_TEST_TRACE_HEADER << " " << m_name << "[" << m_test.size() << "]{";

			if(verbose) {

				for(test_iter = m_test.begin(); test_iter != m_test.end(); ++test_iter) {
					result << std::endl << " --- ";

					switch(test_iter->second.second) {
						case PTCE_TEST_FAILURE:
							result << "**" << PTCE_TEST_STRING(test_iter->second.second) << "** ";
							++failure;
							break;
						case PTCE_TEST_INCONCLUSIVE:
							result << "**" << PTCE_TEST_STRING(test_iter->second.second) << "** ";
							++inconclusive;
							break;
						case PTCE_TEST_SUCCESS:
							++success;
							break;
						default:
							THROW_PTCE_TEST_SET_EXCEPTION_MESSAGE(PTCE_TEST_SET_EXCEPTION_UNKNOWN_TEST_TYPE,
								"%lu (must be at most %lu)", test_iter->second.second, PTCE_TEST_MAX);
					}

					result << test_iter->first;
				}
			}

			result << std::endl << "} (" << failure << ", " << inconclusive << ", " << success << ")";

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
