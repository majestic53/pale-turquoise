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

#include <ctime>
#include "../include/ptce.h"
#include "../include/ptce_uid_type.h"

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		bool 
		operator==(
			__in const _ptce_uid &left,
			__in const _ptce_uid &right
			)
		{			
			bool result;

			TRACE_ENTRY();

			result = (left.m_uid == right.m_uid);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		operator<(
			__in const _ptce_uid &left,
			__in const _ptce_uid &right
			)
		{			
			bool result;

			TRACE_ENTRY();

			result = (left.m_uid < right.m_uid);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		_ptce_uid::_ptce_uid(
			__in_opt uint64_t uid
			) :
				m_uid(uid)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid::_ptce_uid(
			__in const _ptce_uid &other
			) :
				m_uid(other.m_uid)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid::~_ptce_uid(void)
		{
			TRACE_ENTRY();

			m_uid = PTCE_UID_DEF;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid &
		_ptce_uid::operator=(
			__in const _ptce_uid &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				m_uid = other.m_uid;
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		bool 
		_ptce_uid::operator==(
			__in const _ptce_uid &other
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = (m_uid == other.m_uid);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_uid::operator!=(
			__in const _ptce_uid &other
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = !(*this == other);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		uint64_t &
		_ptce_uid::id(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_uid);
			return m_uid;
		}

		std::string  
		_ptce_uid::id_as_string(
			__in const _ptce_uid &uid,
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			TRACE_ENTRY();

			if(verbose) {
				result << PTCE_UID_TRACE_HEADER << " ";
			}

			result << "{" << VALUE_AS_HEX(uint64_t, uid.m_uid) << "}";

			TRACE_EXIT("Return Value: 0%x", 0);
			return result.str();
		}

		std::string 
		_ptce_uid::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(verbose) {
				result << PTCE_UID_TRACE_HEADER << " ";
			}

			result << id_as_string(*this);

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		ptce_uid_factory_ptr ptce_uid_factory::m_instance = NULL;

		void 
		ptce_uid_factory_destroy(void)
		{
			TRACE_ENTRY();

			if(ptce_uid_factory::m_instance) {
				delete ptce_uid_factory::m_instance;
				ptce_uid_factory::m_instance = NULL;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid_factory::_ptce_uid_factory(void) :
			m_initialized(false)
		{
			TRACE_ENTRY();

			std::atexit(ptce_uid_factory_destroy);

			TRACE_EXIT("Return Value: 0%x", 0);
		}

		_ptce_uid_factory::~_ptce_uid_factory(void)
		{
			TRACE_ENTRY();

			if(m_initialized) {
				destroy();
			}

			TRACE_EXIT("Return Value: 0%x", 0);
		}

		ptce_uid_factory_ptr 
		_ptce_uid_factory::acquire(void)
		{
			ptce_uid_factory_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				m_instance = new ptce_uid_factory();
				if(!m_instance) {
					THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0%p", result);
			return result;
		}

		size_t 
		_ptce_uid_factory::add(
			__in const ptce_uid &uid,
			__in_opt bool unique
			)
		{
			size_t result = PTCE_INIT_REF_DEF;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			if(!contains(result)) {

				if(unique) {
					THROW_PTCE_UID_EXCEPTION_MESSAGE(PTCE_UID_EXCEPTION_EXISTS,
							"%s", ptce_uid::id_as_string(uid).c_str());
				}

				m_uid_map.insert(std::pair<ptce_uid, size_t>(uid, PTCE_INIT_REF_DEF));
			} else {
				result = ++m_uid_map.find(result)->second;
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		bool 
		_ptce_uid_factory::contains(
			__in const ptce_uid &uid
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			result = (m_uid_map.find(uid) != m_uid_map.end());

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		size_t 
		_ptce_uid_factory::decrement_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result = 0;
			std::map<ptce_uid, size_t>::iterator uid_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			uid_iter = find_uid(uid);

			if(uid_iter->second == PTCE_INIT_REF_DEF) {
				m_uid_map.erase(uid_iter);
			} else {
				result = --uid_iter->second;
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		void 
		_ptce_uid_factory::destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			m_uid_map.clear();
			m_initialized = false;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		std::map<ptce_uid, size_t>::iterator 
		_ptce_uid_factory::find_uid(
			__in const ptce_uid &uid
			)
		{
			std::map<ptce_uid, size_t>::iterator result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			result = m_uid_map.find(uid);
			if(result == m_uid_map.end()) {
				THROW_PTCE_UID_EXCEPTION_MESSAGE(PTCE_UID_EXCEPTION_UNKNOWN_UID,
					"%s", ptce_uid::id_as_string(uid).c_str());
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result;
		}

		ptce_uid 
		_ptce_uid_factory::generate(
			__in bool unique
			)
		{
			ptce_uid result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			do {
				result.id() = ((uint64_t) m_distribution(m_generator) << 0x20) 
							| m_distribution(m_generator);

				if(!result.id()) {
					continue;
				}

				if(!unique) {
					break;
				}
			} while(contains(result));

			if(!contains(result)) {
				m_uid_map.insert(std::pair<ptce_uid, size_t>(result, PTCE_INIT_REF_DEF));
			} else {
				++m_uid_map.find(result)->second;
			}

			TRACE_EXIT("Return Value: %s", result.to_string().c_str());
			return m_uid_map.find(result)->first;
		}

		size_t 
		_ptce_uid_factory::increment_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result;
			std::map<ptce_uid, size_t>::iterator uid_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			result = ++find_uid(uid)->second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		void  
		_ptce_uid_factory::initialize(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_INITIALIZED);
			}

			m_uid_map.clear();
			m_initialized = true;
			m_generator.seed(std::time(NULL));
			add(UID_NULL);

			TRACE_EXIT("Return Value: 0%x", 0);
		}

		bool 
		_ptce_uid_factory::is_allocated(void)
		{
			bool result;

			TRACE_ENTRY();

			result = (m_instance != NULL);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool  
		_ptce_uid_factory::is_initialized(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0%x", m_initialized);
			return m_initialized;
		}

		size_t 
		_ptce_uid_factory::reference_count(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			result = find_uid(uid)->second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_uid_factory::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_UID_EXCEPTION(PTCE_UID_EXCEPTION_UNINITIALIZED);
			}

			result = m_uid_map.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string  
		_ptce_uid_factory::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<ptce_uid, size_t>::iterator uid_iter;
	
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << PTCE_UID_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance) 
					<< ", Initialized=" << m_initialized << ", Count=" << m_uid_map.size();

			if(verbose) {

				for(uid_iter = m_uid_map.begin(); uid_iter != m_uid_map.end(); ++uid_iter) {
					result << std::endl << " --- " << ptce_uid::id_as_string(uid_iter->first) 
							<< " (" << uid_iter->second << ")";
				}
			}
		
			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		_ptce_uid_base::_ptce_uid_base(void) :
				m_uid(generate_id(true))
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid_base::_ptce_uid_base(
			__in const ptce_uid uid
			) :
				m_uid(uid)
		{
			TRACE_ENTRY();

			increment_reference();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid_base::_ptce_uid_base(
			__in const _ptce_uid_base &other
			) :
				m_uid(other.m_uid)
		{
			TRACE_ENTRY();

			increment_reference();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid_base::~_ptce_uid_base(void)
		{
			TRACE_ENTRY();

			decrement_reference();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_uid_base &
		_ptce_uid_base::operator=(
			__in const _ptce_uid_base &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				decrement_reference();
				m_uid = other.m_uid;
				increment_reference();
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		size_t 
		_ptce_uid_base::decrement_reference(void)
		{
			size_t result = 0;
			ptce_ptr inst = NULL;
			ptce_uid_factory_ptr fact_inst = NULL;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(inst && inst->is_initialized()) {

				fact_inst = inst->acquire_uid_factory();
				if(fact_inst && fact_inst->contains(m_uid)) {
					result = fact_inst->decrement_reference(m_uid);
				}
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		ptce_uid 
		_ptce_uid_base::generate_id(
			__in bool unique
			)
		{
			ptce_uid result;
			ptce_ptr inst = NULL;

			TRACE_ENTRY();
			//SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(inst && inst->is_initialized()) {
				result = inst->acquire_uid_factory()->generate(unique);
			}

			TRACE_EXIT("Return Value: %s", result.to_string().c_str());
			return result;
		}

		ptce_uid &
		_ptce_uid_base::id(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %s", m_uid.to_string().c_str());
			return m_uid;
		}

		size_t 
		_ptce_uid_base::increment_reference(void)
		{
			size_t result = 0;
			ptce_ptr inst = NULL;
			ptce_uid_factory_ptr fact_inst = NULL;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(inst && inst->is_initialized()) {

				fact_inst = inst->acquire_uid_factory();
				if(fact_inst && fact_inst->contains(m_uid)) {
					result = fact_inst->increment_reference(m_uid);
				} else {
					result = fact_inst->add(m_uid);
				}
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_uid_base::reference_count(void)
		{
			size_t result = 0;
			ptce_ptr inst = NULL;
			ptce_uid_factory_ptr fact_inst = NULL;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			inst = ptce::acquire();
			if(inst && inst->is_initialized()) {

				fact_inst = inst->acquire_uid_factory();
				if(fact_inst && fact_inst->contains(m_uid)) {
					result = fact_inst->reference_count(m_uid);
				}
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string 
		_ptce_uid_base::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << m_uid.to_string(verbose) << " (ref. " << reference_count() << ")";

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
